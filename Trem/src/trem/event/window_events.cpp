#include <trpch.h>
#include "window_events.h"

namespace Trem
{
  std::string WindowResizedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }

  std::string WindowClosedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }

  std::string WindowMinimizedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }
}
