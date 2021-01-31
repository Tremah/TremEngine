#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include "event.h"
#include <trem/ui/input_codes.h>

/**
 *  \brief Keyboard Events
 *
 */
namespace Trem
{
  class KeyEvent : public Event
  {
    public:
      //param. constructors
      
      //public member variables

      //public member functions
      EVENT_CATEGORY(EventCategory::KeyboardEvent | EventCategory::InputEvent)
      KeyCode keycode() const;

    protected:
      //protected constructors
      KeyEvent(const KeyCode keyCode) : Event(), keyCode_{keyCode} {}

      //protected member variables
      KeyCode keyCode_;

      //protected member functions

    private:      
      //private member variables
      //private member functions      
  };

  class KeyPressedEvent : public KeyEvent
  {
    public:
      //param. constructors
      KeyPressedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

      //public member variables
      
      //public member functions
      EVENT_TYPE(KeyPressed)
      std::string toString() const override;

    protected:
      //protected member variables
      //protected member functions

    private:      
      //private member variables
      //private member functions      
  };

  class KeyReleasedEvent : public KeyEvent
  {
    public:
      //param. constructors
      KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

      //public member variables
      
      //public member functions
      EVENT_TYPE(KeyReleased)
      std::string toString() const override;

    protected:
      //protected member variables
      //protected member functions

    private:      
      //private member variables
      //private member functions      
  };

  class KeyRepeatedEvent : public KeyEvent
  {
    public:
      //param. constructors
      KeyRepeatedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

      //public member variables
      
      //public member functions
      EVENT_TYPE(KeyRepeated)
      std::string toString() const override;

    protected:
      //protected member variables
      //protected member functions

    private:      
      //private member variables

      //private member functions      
  };

  
}
