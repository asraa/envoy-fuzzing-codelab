#include "priority_set.h"

#include <chrono>
#include <functional>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace Envoy {
namespace Upstream {

using ::testing::_;
using ::testing::Invoke;
using ::testing::ReturnRef;

MockPrioritySet::MockPrioritySet() {
  getHostSet(0);
  ON_CALL(*this, hostSetsPerPriority()).WillByDefault(ReturnRef(host_sets_));
  ON_CALL(testing::Const(*this), hostSetsPerPriority()).WillByDefault(ReturnRef(host_sets_));
  ON_CALL(*this, addMemberUpdateCb(_))
      .WillByDefault(Invoke([this](PrioritySet::MemberUpdateCb cb) -> Common::CallbackHandle* {
        return member_update_cb_helper_.add(cb);
      }));
  ON_CALL(*this, addPriorityUpdateCb(_))
      .WillByDefault(Invoke([this](PrioritySet::PriorityUpdateCb cb) -> Common::CallbackHandle* {
        return priority_update_cb_helper_.add(cb);
      }));
}

MockPrioritySet::~MockPrioritySet() = default;

HostSet& MockPrioritySet::getHostSet(uint32_t priority) {
  if (host_sets_.size() < priority + 1) {
    for (size_t i = host_sets_.size(); i <= priority; ++i) {
      auto host_set = new ::testing::NiceMock<MockHostSet>(i);
      host_sets_.push_back(HostSetPtr{host_set});
      host_set->addMemberUpdateCb([this](uint32_t priority, const HostVector& hosts_added,
                                         const HostVector& hosts_removed) {
        runUpdateCallbacks(priority, hosts_added, hosts_removed);
      });
    }
  }
  return *host_sets_[priority];
}

void MockPrioritySet::runUpdateCallbacks(uint32_t priority, const HostVector& hosts_added,
                                         const HostVector& hosts_removed) {
  member_update_cb_helper_.runCallbacks(hosts_added, hosts_removed);
  priority_update_cb_helper_.runCallbacks(priority, hosts_added, hosts_removed);
}

} // namespace Upstream

} // namespace Envoy
