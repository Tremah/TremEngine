#include "trpch.h"
#include "logger.h"

namespace Trem
{
  Logger::Logger()
  {
    logger_.set_level(spdlog::level::trace);
    auto consoleSink = CreateShared<spdlog::sinks::stdout_color_sink_st>(spdlog::color_mode::always);
    consoleSink->set_pattern("[%H:%M:%S] [%^%l%$] %v");
    logger_.sinks().push_back(consoleSink);
  }

  spdlog::logger& Logger::logger()
  {
    return logger_;
  }
}
