#include <trpch.h>
#include "service_locator.h"

namespace Trem
{
  ServiceLocator::ServiceLocator()
  {
    TR_ASSERT(!instantiated_, "Service locator already instantiated!")
    instantiated_ = true;
  }

  void ServiceLocator::setLogger(Logger&& logger)
  {
    logger_ = std::move(logger);
  }

  void ServiceLocator::setDispatcher(Dispatcher&& dispatcher)
  {
    dispatcher_ = std::move(dispatcher);
  }

  spdlog::logger& ServiceLocator::logger()
  {
    return logger_.logger();
  }
  Dispatcher& ServiceLocator::dispatcher()
  {
    return dispatcher_;
  }
}
