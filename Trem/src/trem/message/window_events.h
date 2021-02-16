#pragma once

//c++ includes

//external library includes
#include "glm/vec2.hpp"

//game engine includes
#include <trem/message/message.h>

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class WindowEvent : public Message
  {
    public:
      //Public param. constructors

      //Member variables      

      //Member functions

    protected:
      //Protected param. constructors
      WindowEvent(MsgType type) : Message(type, (MsgCategories::Event | MsgCategories::WindowEvent)) {}

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
      WindowResizedEvent(uint16_t width, uint16_t height) : WindowEvent(MsgTypes::WindowResized), windowSize_{width, height} {}

      //Member variables      
      glm::uvec2 windowSize_;

      //Member functions
      static MsgType staticMsgType() { return MsgTypes::WindowResized; }
      std::string toString() const override;

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
      WindowClosedEvent() : WindowEvent(MsgTypes::WindowClosed) {}

      //Member variables 

      //Member functions
      static MsgType staticMsgType() { return MsgTypes::WindowClosed; }
      std::string toString() const override;   

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
      WindowMinimizedEvent() : WindowEvent(MsgTypes::WindowMinimized) {}

      //Member variables 

      //Member functions
      static MsgType staticMsgType() { return MsgTypes::WindowMinimized; }
      std::string toString() const override; 

    protected:
      //Protected param. constructors

      //Member variables

      //Member functions

    private:
      //Member variables

      //Member functions 
  };
}
