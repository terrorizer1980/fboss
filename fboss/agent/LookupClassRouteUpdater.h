/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include "fboss/agent/StateObserver.h"
#include "fboss/agent/state/StateDelta.h"

#include <folly/container/F14Map.h>
#include <folly/container/F14Set.h>

namespace facebook::fboss {

class LookupClassRouteUpdater : public AutoRegisterStateObserver {
 public:
  explicit LookupClassRouteUpdater(SwSwitch* sw)
      : AutoRegisterStateObserver(sw, "LookupClassRouteUpdater") {}
  ~LookupClassRouteUpdater() override {}

  void stateUpdated(const StateDelta& stateDelta) override;

 private:
  // Helper methods
  void reAddAllRoutes(const StateDelta& stateDelta);

  bool vlanHasOtherPortsWithClassIDs(
      const std::shared_ptr<SwitchState>& switchState,
      const std::shared_ptr<Vlan>& vlan,
      const std::shared_ptr<Port>& removedPort);

  void removeNextHopsForSubnet(
      const StateDelta& stateDelta,
      const folly::CIDRNetwork& subnet,
      const std::shared_ptr<Vlan>& vlan);

  // Methods for dealing with vlan2SubnetsCache_
  bool belongsToSubnetInCache(
      VlanID vlanID,
      const folly::IPAddress& ipToSearch);

  void updateSubnetsCache(
      const StateDelta& stateDelta,
      std::shared_ptr<Port> port,
      bool reAddAllRoutesEnabled);

  // Methods for handling port updates
  void processPortAdded(
      const StateDelta& stateDelta,
      const std::shared_ptr<Port>& addedPort,
      bool reAddAllRoutesEnabled);
  void processPortRemoved(
      const StateDelta& stateDelta,
      const std::shared_ptr<Port>& port);
  void processPortChanged(
      const StateDelta& stateDelta,
      const std::shared_ptr<Port>& oldPort,
      const std::shared_ptr<Port>& newPort);

  void processPortUpdates(const StateDelta& stateDelta);

  // Methods for handling neighbor updates
  template <typename AddedNeighborT>
  void processNeighborAdded(
      const StateDelta& stateDelta,
      VlanID vlan,
      const std::shared_ptr<AddedNeighborT>& addedNeighbor);
  template <typename removedNeighborT>
  void processNeighborRemoved(
      const StateDelta& stateDelta,
      VlanID vlan,
      const std::shared_ptr<removedNeighborT>& removedNeighbor);
  template <typename ChangedNeighborT>
  void processNeighborChanged(
      const StateDelta& stateDelta,
      VlanID vlan,
      const std::shared_ptr<ChangedNeighborT>& oldNeighbor,
      const std::shared_ptr<ChangedNeighborT>& newNeighbor);

  template <typename AddrT>
  void processNeighborUpdates(const StateDelta& stateDelta);

  // Methods for handling route updates
  template <typename RouteT>
  void processRouteAdded(
      const StateDelta& stateDelta,
      RouterID rid,
      const std::shared_ptr<RouteT>& addedRoute);
  template <typename RouteT>
  void processRouteRemoved(
      const StateDelta& stateDelta,
      RouterID rid,
      const std::shared_ptr<RouteT>& removedRoute);
  template <typename RouteT>
  void processRouteChanged(
      const StateDelta& stateDelta,
      RouterID rid,
      const std::shared_ptr<RouteT>& oldRoute,
      const std::shared_ptr<RouteT>& newRoute);

  template <typename AddrT>
  void processRouteUpdates(const StateDelta& stateDelta);

  using RidAndCidr = std::pair<RouterID, folly::CIDRNetwork>;
  using NextHopAndVlan = std::pair<folly::IPAddress, VlanID>;
  using WithAndWithoutClassIDPrefixes =
      std::pair<folly::F14FastSet<RidAndCidr>, folly::F14FastSet<RidAndCidr>>;

  /*
   * We need to maintain nexthop to route mapping so that when a nexthop is
   * resolved (gets classID), the same classID could be associated with
   * corresponding routes. However, we are only interested in nexthops that are
   * part of 'certain' subnets. vlan2SubnetsCache_ maintains that list of
   * subnets.
   *   - ports needing queue-per-host have non-empty lookupClasses list.
   *   - each port belongs to an interface.
   *   - each interface is part of certain subnet.
   *   - nexthop IP that would use such a port for egress, would belong to the
   *     interface subnet.
   * Thus, we discover and maintain a list of subnets for ports that have
   * non-emptry lookupClasses list.
   *
   * Today, the list of subnets we need to cache is very small. Thus,
   * folly::F14FastSet is good enough. In future, if we need to cache a large
   * number of subnets, we could use a Radix tree.
   */
  boost::container::flat_map<VlanID, folly::F14FastSet<folly::CIDRNetwork>>
      vlan2SubnetsCache_;

  /*
   * Route inherits classID of one of its reachable next hops.
   *
   * A route entry points to an egress object, which corresponds to a next hop.
   * If a route has multiple next hops:
   *  - route entry points to an ECMP egress object.
   *  - ECMP egress object points to a list of egress objects.
   *  - Each egress object in the list corresponds to one next hop.
   *
   * However, a classID could only be associated with a route entry, and not
   * with an egress object (hardware limitation). Thus, if a route has multiple
   * next hops, we must pick one of the next hops and inherit its classID for
   * the route.
   *
   * Only reachable next hops have classID. Thus, a Route inherits classID of
   * one of its *reachable* next hops. In the current implementation, we pick
   * any one reachable next hop and inherit its classID, in future this could
   * be modified to some other scheme.
   *
   * There are several cases to consider:
   * (1) When a route is resolved:
   *     (1.1) None of its next hops are reachable: No classID for route.
   *     (1.2) At least one next hop is reachable: Inherit its classID.
   * (2) When a route is deleted, clear local data structures.
   * (3) When route's nexthopset changes:
   *         Remove oldRoute and add newRoute.
   * (4) When a next hop's classID is updated:
   *     (4.1) next hop gets classID (neighbor becomes reachable):
   *           For every route that has this next hop, if the route does not
   *           already have a classID, route inherits this classID.
   *     (4.2) next hop loses classID (neighbor becomes unreachable):
   *           For every route that has this next hop, find another next hop
   *           that already has classID, route inherits that classID. If such a
   *           next hop does not exist, route loses classID.
   *
   * This is implemented by maintaining following data structures.
   * TODO(skhare) add note on how these data structures handle all cases.
   *
   * Note that this class computes classIDs for the routes, state update is
   * scheduled by the caller (LookupClassRouteUpdater).
   */

  /*
   * NextHop to prefixes map.
   *
   * In theory, same IP may exist in different Vlans, thus maintain IP + Vlan
   * to prefixes mapping.
   *
   * Today, the list of subnets we need to cache is very small. Thus,
   * folly::F14FastSet is good enough. In future, if we need to cache a large
   * number of subnets, we could use Radix tree.
   *
   * This maintains the list of prefixes that inherit classID from this
   * [nexthop, vlan] separately from the list of prefixes that don't.
   */
  folly::F14FastMap<NextHopAndVlan, WithAndWithoutClassIDPrefixes>
      nextHopAndVlanToPrefixes_;

  /*
   * Set of prefixes with classID (from any [nexthop + vlan]).
   */
  folly::F14FastSet<RidAndCidr> allPrefixesWithClassID_;
};

} // namespace facebook::fboss
