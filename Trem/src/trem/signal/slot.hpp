#pragma once

#include "typelist.hpp"

namespace Trem
{
  template <typename>
  class Slot;

  template <typename Ret, typename... Args>
  class Slot<Ret(Args...)>
  {
  public:
    using Instance_t = void;
    using Call_t = Ret(Instance_t*, Args...);

    Slot(const Slot&) = default;
    Slot(Slot&&) = default;
    Slot& operator=(const Slot&) = default;
    Slot& operator=(Slot&&) = default;
    ~Slot() { close(); }

    Slot() : callback_{nullptr}, instance_{nullptr} {}

    template <auto Func>
    auto functionWrapper()
    {
      return [](Instance_t*, Args... args) -> Ret {
        //return static_cast<Ret>(std::invoke(Func, std::forward<Args>(args)...));
        return static_cast<Ret>(Func(std::forward<Args>(args)...));
      };
    }

    template <auto Func, typename Class>
    auto functionWrapper()
    {
      return [](Instance_t* instance, Args... args) -> Ret {
        Class* castInstance = static_cast<Class*>(instance);
        return static_cast<Ret>(std::invoke(Func, castInstance, std::forward<Args>(args)...));
        //(castInstance->*Func)(args...);
      };

    }

    template <auto func>
    void connect()
    {
      close();
      callback_ = functionWrapper<func>();
    }

    template <auto func, typename Class>
    void connect(Class& instance)
    {
      close();
      instance_ = &instance;
      callback_ = functionWrapper<func, Class>();
    }

    void close()
    {
      instance_ = nullptr;
      callback_ = nullptr;
    }

    Ret call(Args&&... args)
    {
      return callback_(instance_, std::forward<Args>(args)...);
    }

    bool operator==(const Slot& other) const
    {
      return callback_ == other.callback_ && instance_ == other.instance_;
    }

  private:
    Call_t* callback_;
    Instance_t* instance_;
  };
}

