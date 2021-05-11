#pragma once

#include <tuple>
#include <vector>
#include <memory>
#include <type_traits>

#include "signal.hpp"
#include "core.hpp"

//simple dispatcher class
//takes events by their type, constructs a signal (if not yet existent) and connects the respective callbacks
//events are made with their submitted arguments 
//can queue and publish events at a later time
//can trigger an event for instant dispatch

namespace Trem
{
  class Dispatcher
  {
    public:
      struct SignalPoolBase
      {
        SignalPoolBase(const SignalPoolBase&) = default;
        SignalPoolBase(SignalPoolBase&&) = default;
        SignalPoolBase& operator=(const SignalPoolBase&) = default;
        SignalPoolBase& operator=(SignalPoolBase&&) = default;
        virtual ~SignalPoolBase() = default;

        SignalPoolBase() = default;

        virtual void dispatch() = 0;
      };

      template <typename Event>
      struct SignalPool final : SignalPoolBase
      {
        SignalPool(const SignalPool&) = default;
        SignalPool(SignalPool&&) = default;
        SignalPool& operator=(const SignalPool&) = default;
        SignalPool& operator=(SignalPool&&) = default;
        ~SignalPool() = default;

        SignalPool() = default;

        using Signal_t = Signal<void(Event&)>;

        //dispatch events in the queue
        void dispatch() override
        {
          while (!(eventQueue_.empty()))
          {
            signal_.emit(eventQueue_.front());
            eventQueue_.pop();
          }
        }

        template <typename... Args>
        void trigger(Args&&... args)
        {
          Event ev{std::forward<Args>(args)...};
          signal_.emit(ev);
        }

        template <typename... Args>
        void enqueue(Args&&... args)
        {
          eventQueue_.emplace(std::forward<Args>(args)...);
        }

        Signal_t& signal()
        {
          return signal_;
        }

        Signal_t signal_;
        std::queue<Event> eventQueue_;
      };

      template <typename Event>
      using SignalPool_t = SignalPool<Event>;



      //free, static, lambda function
      template <typename Event, auto func>
      void connect()
      {
        guarantee<Event>().signal().connect<func>();
      }

      //member functions
      template <typename Event, auto func, typename C>
      void connect(C& instance)
      {
        guarantee<Event>().signal().connect<func>(instance);
      }

      //free, static, lambda function
      template <typename Event, auto func>
      void disconnect()
      {
        guarantee<Event>().signal().disconnect<func>();
      }

      //member functions
      template <typename Event, auto func, typename C>
      void disconnect(C& instance)
      {
        guarantee<Event>().signal().disconnect<func>(instance);
      }

      //all function of one instance
      template <typename Event, typename C>
      void disconnect(C& instance)
      {
        guarantee<Event>().signal().disconnect(instance);
      }

      //all callbacks
      template <typename Event>
      void disconnect()
      {
        guarantee<Event>().signal().disconnect();
      }

      //trigger event (construct on the fly)
      template <typename Event, typename... Args>
      void trigger(Args&&... args)
      {
        guarantee<Event>().trigger(std::forward<Args>(args)...);
      }

      void dispatch()
      {
        for (auto& signal : signals_)
        {
          if (signal)
          {
            signal->dispatch();
          }
        }
      }

      //dispatch queued events
      template <typename Event>
      void dispatch()
      {
        guarantee<Event>().dispatch();
      }

      //queue event
      template <typename Event, typename... Args>
      void enqueue(Args&&... args)
      {
        guarantee<Event>().enqueue(std::forward<Args>(args)...);
      }

    private:
      //guarantees that a pool exists
      //by creating a pool for an event if it does not yet exist
      template <typename Event>
      SignalPool<Event>& guarantee()
      {
        const auto index = IdSequence<Event>::value();
        if (!(index < signals_.size()))
        {
          signals_.resize(static_cast<std::size_t>(index) + 5u);
        }

        if (!(signals_.at(index)))
        {
          signals_.at(index) = std::make_unique<SignalPool_t<Event>>();
        }

        return static_cast<SignalPool_t<Event>&>(*(signals_.at(index).get()));
      }

      std::vector<std::unique_ptr<SignalPoolBase>> signals_;
  };
}
