#include "trpch.h"
#include "service_locator.h"

namespace Trem
{
  Logger ServiceLocator::logger_{};

  void ServiceLocator::setLogger(Logger&& logger)
  {
    logger_ = logger;
  }

  spdlog::logger& ServiceLocator::logger()
  {
    return logger_.logger();
  }
}
