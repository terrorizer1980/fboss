/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "fboss/agent/hw/test/HwSwitchEnsemble.h"

#include "fboss/agent/AlpmUtils.h"
#include "fboss/agent/ApplyThriftConfig.h"
#include "fboss/agent/HwSwitch.h"
#include "fboss/agent/Platform.h"
#include "fboss/agent/hw/test/HwLinkStateToggler.h"
#include "fboss/agent/platforms/test_platforms/CreateTestPlatform.h"
#include "fboss/agent/state/SwitchState.h"

namespace facebook {
namespace fboss {

HwSwitchEnsemble::HwSwitchEnsemble(uint32_t featuresDesired)
    : featuresDesired_(featuresDesired) {}

HwSwitchEnsemble::~HwSwitchEnsemble() {}

std::shared_ptr<SwitchState> HwSwitchEnsemble::getProgrammedState() const {
  CHECK(programmedState_->isPublished());
  return programmedState_;
}

std::shared_ptr<SwitchState> HwSwitchEnsemble::applyNewState(
    std::shared_ptr<SwitchState> newState) {
  if (!newState) {
    return programmedState_;
  }
  newState->publish();
  StateDelta delta(programmedState_, newState);
  programmedState_ = hwSwitch_->stateChanged(delta);
  programmedState_->publish();
  return programmedState_;
}

void HwSwitchEnsemble::applyInitialConfigAndBringUpPorts(
    const cfg::SwitchConfig& initCfg) {
  CHECK(featuresDesired_ & HwSwitch::LINKSCAN_DESIRED)
      << "Link scan feature must be enabled for exercising "
      << "applyInitialConfigAndBringUpPorts";
  linkToggler_->applyInitialConfigAndBringUpPorts(
      getProgrammedState(), getPlatform(), initCfg);
  hwSwitch_->initialConfigApplied();
  initCfgState_ = getProgrammedState();
}

void HwSwitchEnsemble::linkStateChanged(PortID port, bool up) {
  linkToggler_->linkStateChanged(port, up);
}

void HwSwitchEnsemble::init() {
  platform_ = createTestPlatform();
  hwSwitch_ = createHwSwitch(platform_.get(), featuresDesired_);
  if (featuresDesired_ & HwSwitch::LINKSCAN_DESIRED) {
    linkToggler_ = createLinkToggler(getHwSwitch());
  }
  programmedState_ = hwSwitch_->init(this).switchState;
  // HwSwitch::init() returns an unpublished programmedState_.  SwSwitch is
  // normally responsible for publishing it.  Go ahead and call publish now.
  // This will catch errors if test cases accidentally try to modify this
  // programmedState_ without first cloning it.
  programmedState_->publish();
  // Handle ALPM state. ALPM requires that default routes be programmed
  // before any other routes. We handle that setup here. Similarly ALPM
  // requires that default routes be deleted last. That aspect is handled
  // in TearDown
  auto alpmState = setupAlpmState(programmedState_);
  if (alpmState) {
    applyNewState(alpmState);
  }
  hwSwitch_->switchRunStateChanged(SwitchRunState::INITIALIZED);
}

void HwSwitchEnsemble::revertToInitCfgState() {
  CHECK(initCfgState_);
  applyNewState(initCfgState_);
}
} // namespace fboss
} // namespace facebook
