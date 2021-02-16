#include "trpch.h"
#include "game_events.h"

namespace Trem
{
  std::string GamePausedEvent::toString() const
  {
    std::stringstream ss;
    ss << MsgTypes::toString(type_) << std::endl;
    return ss.str();
  }

  std::string GameResumedEvent::toString() const
  {
    std::stringstream ss;
    ss << MsgTypes::toString(type_)<< std::endl;
    return ss.str();
  }

  std::string GameClosedEvent::toString() const
  {
    std::stringstream ss;
    ss << MsgTypes::toString(type_) << std::endl;
    return ss.str();
  }
}
