﻿#include <trpch.h>
#include "mouse_events.h"

namespace Trem
{
  MouseCode MouseEvent::mouseCode() const
  {
    return mouseCode_;
  }

  std::string LMouseButtonPressedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }

  std::string RMouseButtonPressedEvent::toString() const
  {
    std::stringstream ss;
    return ss.str();
  }
}
