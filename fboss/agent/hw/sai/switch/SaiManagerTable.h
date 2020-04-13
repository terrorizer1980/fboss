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

#include "fboss/agent/hw/sai/api/Types.h"

#include <memory>
#include <optional>

namespace folly {
struct dynamic;
}

namespace facebook::fboss {

class ConcurrentIndices;
class SaiBridgeManager;
class SaiFdbManager;
class SaiHashManager;
class SaiHostifManager;
class SaiInSegEntryManager;
class SaiNeighborManager;
class SaiNextHopManager;
class SaiNextHopGroupManager;
class SaiPlatform;
class SaiPortManager;
class SaiQueueManager;
class SaiQosMapManager;
class SaiRouteManager;
class SaiRouterInterfaceManager;
class SaiSwitchManager;
class SaiSchedulerManager;
class SaiVirtualRouterManager;
class SaiVlanManager;

class SaiManagerTable {
 public:
  SaiManagerTable(
      SaiPlatform* platform,
      const std::optional<SwitchSaiId>& switchId);
  void createSaiTableManagers(
      SaiPlatform* platform,
      ConcurrentIndices* concurrentIndices);
  ~SaiManagerTable();

  SaiBridgeManager& bridgeManager();
  const SaiBridgeManager& bridgeManager() const;

  SaiFdbManager& fdbManager();
  const SaiFdbManager& fdbManager() const;

  SaiHashManager& hashManager();
  const SaiHashManager& hashManager() const;

  SaiHostifManager& hostifManager();
  const SaiHostifManager& hostifManager() const;

  SaiNeighborManager& neighborManager();
  const SaiNeighborManager& neighborManager() const;

  SaiNextHopManager& nextHopManager();
  const SaiNextHopManager& nextHopManager() const;

  SaiNextHopGroupManager& nextHopGroupManager();
  const SaiNextHopGroupManager& nextHopGroupManager() const;

  SaiPortManager& portManager();
  const SaiPortManager& portManager() const;

  SaiQueueManager& queueManager();
  const SaiQueueManager& queueManager() const;

  SaiQosMapManager& qosMapManager();
  const SaiQosMapManager& qosMapManager() const;

  SaiRouteManager& routeManager();
  const SaiRouteManager& routeManager() const;

  SaiRouterInterfaceManager& routerInterfaceManager();
  const SaiRouterInterfaceManager& routerInterfaceManager() const;

  SaiSchedulerManager& schedulerManager();
  const SaiSchedulerManager& schedulerManager() const;

  SaiSwitchManager& switchManager();
  const SaiSwitchManager& switchManager() const;

  SaiVirtualRouterManager& virtualRouterManager();
  const SaiVirtualRouterManager& virtualRouterManager() const;

  SaiVlanManager& vlanManager();
  const SaiVlanManager& vlanManager() const;

  SaiInSegEntryManager& inSegEntryManager();
  const SaiInSegEntryManager& inSegEntryManager() const;

 private:
  std::unique_ptr<SaiBridgeManager> bridgeManager_;
  std::unique_ptr<SaiFdbManager> fdbManager_;
  std::unique_ptr<SaiHashManager> hashManager_;
  std::unique_ptr<SaiHostifManager> hostifManager_;
  std::unique_ptr<SaiNeighborManager> neighborManager_;
  std::unique_ptr<SaiNextHopManager> nextHopManager_;
  std::unique_ptr<SaiNextHopGroupManager> nextHopGroupManager_;
  std::unique_ptr<SaiPortManager> portManager_;
  std::unique_ptr<SaiQueueManager> queueManager_;
  std::unique_ptr<SaiQosMapManager> qosMapManager_;
  std::unique_ptr<SaiRouteManager> routeManager_;
  std::unique_ptr<SaiRouterInterfaceManager> routerInterfaceManager_;
  std::unique_ptr<SaiSchedulerManager> schedulerManager_;
  std::unique_ptr<SaiSwitchManager> switchManager_;
  std::unique_ptr<SaiVirtualRouterManager> virtualRouterManager_;
  std::unique_ptr<SaiVlanManager> vlanManager_;
  std::unique_ptr<SaiInSegEntryManager> inSegEntryManager_;
};

} // namespace facebook::fboss
