#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include "event.h"
#include <trem/ui/input_codes.h>

/**
 *  \brief Mouse Events
 *
 */
namespace Trem
{
  class MouseEvent : public Event
  {
    public:
      //param. constructors

      //public member variables

      //public member functions
      EVENT_CATEGORY(EventCategory::MouseEvent | EventCategory::InputEvent)
      MouseCode mouseCode() const;

    protected:
      //protected constructors
      MouseEvent(const MouseCode mouseCode) : Event(), mouseCode_{mouseCode} {}

      //protected member variables
      MouseCode mouseCode_;

      //protected member functions

    private:
      //private member variables
      //private member functions      
  };

  class LMouseButtonPressedEvent : public MouseEvent
  {
    public:
      //param. constructors
      LMouseButtonPressedEvent(const MouseCode mouseCode) : MouseEvent(mouseCode) {}

      //public member variables
      
      //public member functions
      EVENT_TYPE(LMouseButtonPressed)
      std::string toString() const override;

    protected:
      //protected member variables
      //protected member functions

    private:      
      //private member variables
      //private member functions      
  };
  

  class RMouseButtonPressedEvent : public MouseEvent
  {
    public:
      //param. constructors
      RMouseButtonPressedEvent(const MouseCode mouseCode) : MouseEvent(mouseCode) {}

      //public member variables
      
      //public member functions
      EVENT_TYPE(RMouseButtonPressed)
      std::string toString() const override;

    protected:
      //protected member variables
      //protected member functions

    private:      
      //private member variables
      //private member functions      
  };
}
