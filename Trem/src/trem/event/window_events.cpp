#include "trpch.h"
#include "window_events.h"

namespace Trem
{
  std::string WindowResizedEvent::toString() const
  {
    std::stringstream ss;
    ss << name() << std::endl;
    return ss.str();
  }

  std::string WindowClosedEvent::toString() const
  {
    std::stringstream ss;
    ss << name() << std::endl;
    return ss.str();
  }

  std::string WindowMinimizedEvent::toString() const
  {
    std::stringstream ss;
    ss << name() << std::endl;
    return ss.str();
  }
}
