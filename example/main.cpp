#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "metadata/meta.hpp"

int main() {
  // Setup spdlog logging library
  spdlog::init_thread_pool(8192, 2);
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto file_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("masscalc.log", true);

  auto masscalc_log = std::make_shared<spdlog::async_logger>(
      "masscalc", spdlog::sinks_init_list{console_sink, file_sink},
      spdlog::thread_pool(), spdlog::async_overflow_policy::block);

  masscalc_log->set_level(spdlog::level::trace);
  masscalc_log->set_pattern("%Y-%m-%d %T.%f %^%l%$ %5t [%-8n] %v");
  masscalc_log->flush_on(spdlog::level::debug);
  spdlog::set_default_logger(masscalc_log);

  // Start of program
  spdlog::trace("{} (c) 2022 Johannes Schneider, MIT license",
                metadata::APP_NAME);
  spdlog::trace("Version {} ({}), Git SHA {}", metadata::APP_VERSION_STR,
                metadata::BUILD_TYPE, metadata::BUILD_GIT);
  spdlog::trace("See {}", metadata::GITHUB_WEBSITE);
  return 0;
}
