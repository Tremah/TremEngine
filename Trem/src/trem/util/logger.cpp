#include "trpch.h"
#include "logger.h"

namespace Trem
{
  ShaPtr<spdlog::logger> Logger::logger_;

  void Logger::init()
  {
    logger_ = CreateShared<spdlog::logger>("Default Logger");
    logger_->set_level(spdlog::level::trace);
    auto consoleSink = CreateShared<spdlog::sinks::stdout_color_sink_st>(spdlog::color_mode::always);
    consoleSink->set_pattern("[%H:%M:%S] [%^%l%$] %v");
    logger_->sinks().push_back(consoleSink);
  }

  ShaPtr<spdlog::logger>& Logger::logger()
  {
    return logger_;
  }
}
