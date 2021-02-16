#include "trpch.h"
#include "message.h"

namespace Trem
{  
  std::string MsgTypes::toString(const uint16_t type)
  {
    switch(type)
    {
      case NullMessage:         return "NullMessage";
      case GamePaused:          return "GamePaused";
      case GameResumed:         return "GameResumed";
      case GameClosed:          return "GameClosed";
      case KeyPressed:          return "KeyPressed";
      case KeyRepeated:         return "KeyRepeated";
      case KeyReleased:         return "KeyReleased";
      case MouseMoved:          return "MouseMoved";
      case LMouseButtonPressed: return "LMouseButtonPressed";
      case RMouseButtonPressed: return "RMouseButtonPressed";
      case WindowResized:       return "WindowResized";
      case WindowMinimized:     return "WindowMinimized";
      case WindowClosed:        return "WindowClosed";
      default:                  return "NullEvent";
    }
  }

  std::string MsgCategories::toString(Category type)
  {
    return "";
  }

  MsgType Message::type() const
  {
    return type_;
  }

  bool Message::inCategory(MsgCategory category)
  {
    return category_ & category;
  }

  std::string Message::toString() const
  {
    return "Message";
  }

  MsgCategory Message::category() const
  {
    return category_;
  }
}
