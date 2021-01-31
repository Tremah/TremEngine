#include "trpch.h"
#include "event.h"

namespace Trem
{
  bool Event::inCategory(const EventCategory category) const
  {
    return categories() & category;
  }


}
