#include <chrono>

#include "common/common/token_bucket_impl.h"
#include "common/protobuf/utility.h"

#include "test/common/common/token_bucket_fuzz.pb.validate.h"
#include "test/fuzz/fuzz_runner.h"
#include "test/test_common/simulated_time_system.h"
#include "test/test_common/utility.h"

namespace Envoy {

DEFINE_PROTO_FUZZER(const test::common::common::TokenBucketFuzzTestCase& input) {
  // Exit early if the protobuf input does not satisfy the constraints.
  try {
    TestUtility::validate(input);
  } catch (const ProtoValidationException& e) {
    ENVOY_LOG_MISC(debug, "ProtoValidationException: {}", e.what());
    return;
  }

  Event::SimulatedTimeSystem time_system;
  // The fill interval will always be greater than 50ms because of the validations in
  // token_bucket.proto.
  double fill_interval = DurationUtil::durationToSeconds(input.config().fill_interval());
  double fill_rate = input.config().tokens_per_fill().value() / fill_interval;
  ENVOY_LOG_MISC(info, "Creating token bucket with max {} and fill rate {}",
                 input.config().max_tokens(), fill_rate);
  // Your code here: create a TokenBucketImpl.

  // Now perform the action trace.
  for (const auto& action : input.actions()) {
    ENVOY_LOG_MISC(trace, "Action {}", action.DebugString());
    switch (action.action_selector_case()) {
    case test::common::common::Action::kConsume: {
      // The line below is provided for convenience. You may uncomment it and use it!
      // const auto& consume = action.consume();
      // Your code here.
      // Recommended: add a logging statement to trace how many tokens were consumed!
      break;
    }
    case test::common::common::Action::kNextToken: {
      // Your code here.
      break;
    }
    case test::common::common::Action::kReset: {
      // Your code here.
      break;
    }
    case test::common::common::Action::kAdvanceTime: {
      // Your code here.
      // Recommended: add a logging statement to trace how much time advanced!
      break;
    }
    default:
      // Nothing to do.
      break;
    }
  }
}

} // namespace Envoy
