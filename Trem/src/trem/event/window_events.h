#pragma once

//c++ includes

//external library includes
#include "glm/vec2.hpp"

//game engine includes

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class WindowEvent 
  {
    public:
      //Public param. constructors

      //Member variables      

      //Member functions

    protected:
      //Protected param. constructors
      WindowEvent() {}

      //Member variables

      //Member functions

    private:
      //Member variables

      //Member functions      
  };
  
  class WindowResizedEvent : public WindowEvent
  {
    public:
      //Public param. constructors
      WindowResizedEvent(uint16_t width, uint16_t height) : WindowEvent(), windowSize_{width, height} {}

      //Member variables      
      glm::uvec2 windowSize_;

      //Member functions
      std::string toString() const;

    protected:
      //Protected param. constructors

      //Member variables

      //Member functions

    private:
      //Member variables

      //Member functions 
  };
  
  class WindowClosedEvent : public WindowEvent
  {
    public:
      //Public param. constructors
      WindowClosedEvent() : WindowEvent() {}

      //Member variables 

      //Member functions
      std::string toString() const;   

    protected:
      //Protected param. constructors

      //Member variables

      //Member functions

    private:
      //Member variables

      //Member functions 
  };
  
  class WindowMinimizedEvent : public WindowEvent
  {
    public:
      //Public param. constructors
      WindowMinimizedEvent() : WindowEvent() {}

      //Member variables 

      //Member functions
      std::string toString() const; 

    protected:
      //Protected param. constructors

      //Member variables

      //Member functions

    private:
      //Member variables

      //Member functions 
  };
}
