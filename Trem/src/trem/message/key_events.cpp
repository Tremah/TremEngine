#include "trpch.h"
#include "key_events.h"

namespace Trem
{
  KeyCode KeyEvent::keycode() const
  {
    return keyCode_;
  }

  std::string KeyPressedEvent::toString() const
  {
    std::stringstream ss;
    ss << MsgTypes::toString(type_) << ": " << keyCode_ << std::endl;
    return ss.str();
  }

  std::string KeyReleasedEvent::toString() const
  {
    std::stringstream ss;
    ss << MsgTypes::toString(type_) << ": " << keyCode_ << std::endl;
    return ss.str();
  }

  std::string KeyRepeatedEvent::toString() const
  {
    std::stringstream ss;
    ss << MsgTypes::toString(type_) << ": " << keyCode_ << std::endl;
    return ss.str();
  }
}
