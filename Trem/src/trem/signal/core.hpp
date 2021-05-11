#pragma once

#include <cstdint>

namespace Trem
{
  struct StaticIdSequence final
  {
    static uint32_t nextId()
    {
      static uint32_t value;
      return value++;
    }
  };

  template <typename T>
  struct IdSequence final
  {
    static uint32_t value()
    {
      static const uint32_t value = StaticIdSequence::nextId();
      return value;
    }
  };
}