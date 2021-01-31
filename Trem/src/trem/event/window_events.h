#pragma once

//c++ includes

//external library includes
#include "glm/vec2.hpp"

//game engine includes
#include <trem/event/event.h>

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class WindowEvent : public Event
  {
    public:
      //Public param. constructors

      //Public member variables      

      //Public member functions
      EVENT_CATEGORY(EventCategory::WindowEvent)

    protected:
      //Protected param. constructors
      WindowEvent() : Event() {}

      //Protected member variables

      //Protected member functions

    private:
      //Private member variables

      //Private member functions      
  };
  
  class WindowResizedEvent : public WindowEvent
  {
    public:
      //Public param. constructors
      WindowResizedEvent(uint16_t width, uint16_t height) : WindowEvent(), windowSize_{width, height} {}

      //Public member variables      
      glm::uvec2 windowSize_;

      //Public member functions
      EVENT_TYPE(WindowResized)
      std::string toString() const override;     

    protected:
      //Protected param. constructors

      //Protected member variables

      //Protected member functions

    private:
      //Private member variables

      //Private member functions 
  };
  
  class WindowClosedEvent : public WindowEvent
  {
    public:
      //Public param. constructors
      WindowClosedEvent() : WindowEvent() {}

      //Public member variables 

      //Public member functions
      EVENT_TYPE(WindowClosed)
      std::string toString() const override;     

    protected:
      //Protected param. constructors

      //Protected member variables

      //Protected member functions

    private:
      //Private member variables

      //Private member functions 
  };
  
  class WindowMinimizedEvent : public WindowEvent
  {
    public:
      //Public param. constructors
      WindowMinimizedEvent() : WindowEvent() {}

      //Public member variables 

      //Public member functions
      EVENT_TYPE(WindowMinimized)
      std::string toString() const override;     

    protected:
      //Protected param. constructors

      //Protected member variables

      //Protected member functions

    private:
      //Private member variables

      //Private member functions 
  };
}
