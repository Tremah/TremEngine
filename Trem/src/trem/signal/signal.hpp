#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <queue>

#include "core.hpp"
#include "slot.hpp"
#include "typelist.hpp"

namespace Trem
{
  template<typename Signature> struct Signal;

  template<typename Ret, typename... SigArgs>
  class Signal<Ret(SigArgs...)>
  {
  public:
    using Slot_t = Slot<Ret(SigArgs...)>;
    using TypeList_t = tl::TypeList<SigArgs...>;


    Signal(const Signal&) = default;
    Signal(Signal&&) = default;
    Signal& operator=(const Signal&) = default;
    Signal& operator=(Signal&&) = default;
    ~Signal() { disconnect(); }

    Signal() = default;

    std::vector<Slot<Ret(SigArgs...)>> slots_;

    template <auto func>
    void connect()
    {
      Slot_t slot{};
      slot.connect<func>();
      slots_.push_back(std::move(slot));
    }

    //non-static member functions
    template<auto func, typename C>
    void connect(C& instance)
    {
      Slot_t slot{};
      slot.connect<func>(instance);
      slots_.push_back(std::move(slot));
    }

    template <auto func>
    void disconnect()
    {
      Slot_t slot{};
      slot.connect<func>();
      slots_.erase(std::remove(slots_.begin(), slots_.end(), slot), slots_.end());
    }

    template<auto func, typename C>
    void disconnect(C& instance)
    {
      Slot_t slot{};
      slot.connect<func>(instance);
      slots_.erase(std::remove(slots_.begin(), slots_.end(), slot), slots_.end());
    }

    template<typename C>
    void disconnect(C& instance)
    {
      /*connections_.erase(
        std::remove_if(
          connections_.begin(),
          connections_.end(),
          [&instance](Connection conn){ return conn.instance_ == &instance;}),
          connections_.end());*/
    }

    void disconnect()
    {
      slots_.clear();
    }

    template <typename... EmitArgs>
    void emit(EmitArgs... emitArgs)
    {
      for (auto& slot : slots_)
      {
        slot.call(emitArgs...);
      }
    }
  };
}