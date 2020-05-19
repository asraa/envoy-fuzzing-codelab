#include "test/fuzz/fuzz_runner.h"
#include "test/fuzzing_codelab/date_formatter.h"

namespace Envoy {
namespace Fuzz {

DEFINE_FUZZER(const uint8_t* buf, size_t len) {
  const std::string input(reinterpret_cast<const char*>(buf), len);
  const SystemTime time{std::chrono::seconds(0)};
  // Your code here to construct a DateFormatter. Check the unit test for a hint!
}

} // namespace Fuzz
} // namespace Envoy
