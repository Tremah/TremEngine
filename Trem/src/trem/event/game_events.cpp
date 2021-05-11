#include <trpch.h>
#include "game_events.h"

namespace Trem
{
  std::string GamePausedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }

  std::string GameResumedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }

  std::string GameClosedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }
}
