#include <string>
#include <vector>


#include "fmt/core.h"
#include "fmt/chrono.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

int main() {

  spdlog::info("Sample Info output.");
  spdlog::warn("Sample Warn output.");
  spdlog::error("Sample Error output.");

  auto filelog = spdlog::basic_logger_mt("sample-logger", "sample-log.txt");

  filelog.get()->info("Sample Info output.");
  filelog.get()->warn("Sample Warn output.");
  filelog.get()->error("Sample Error output.");

  // std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");

  fmt::print("Hello world\n");

  // using namespace std::literals::chrono_literals;
  // fmt::print("Default format: {} {}\n", 42s, 100ms);
  // fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
  std::vector<int> v = {1, 2, 3};
  // fmt::print("{}\n", v);

  return 0;
}