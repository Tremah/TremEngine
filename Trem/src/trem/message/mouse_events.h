#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include "message.h"
#include <trem/input/input_codes.h>

/**
 *  \brief Mouse Events
 *
 */
namespace Trem
{
  class MouseEvent : public Message
  {
    public:
      //Constructors and deconstructors 

      //Member variables

      //Member functions
      MouseCode mouseCode() const;

    protected:
      //Constructors and deconstructors
      MouseEvent(const MouseCode mouseCode, MsgType type) :
        Message(type, (MsgCategories::Event | MsgCategories::InputEvent | MsgCategories::MouseEvent)),
        mouseCode_{mouseCode} {}

      //Member variables
      MouseCode mouseCode_;

      //Member functions

    private:
      //Member variables
      //Member functions      
  };

  class LMouseButtonPressedEvent : public MouseEvent
  {
    public:
      //Constructors and deconstructors 
      LMouseButtonPressedEvent(const MouseCode mouseCode) : MouseEvent(mouseCode, MsgTypes::LMouseButtonPressed) {}

      //Member variables
      
      //Member functions
      static MsgType staticMsgType() { return MsgTypes::LMouseButtonPressed; }
      std::string toString() const override;

    protected:
      //Member variables
      //Member functions

    private:      
      //Member variables
      //Member functions      
  };  

  class RMouseButtonPressedEvent : public MouseEvent
  {
    public:
      //Constructors and deconstructors 
      RMouseButtonPressedEvent(const MouseCode mouseCode) : MouseEvent(mouseCode, MsgTypes::RMouseButtonPressed) {}

      //Member variables
      
      //Member functions
      static MsgType staticMsgType() { return MsgTypes::RMouseButtonPressed; }
      std::string toString() const override;

    protected:
      //Member variables
      //Member functions

    private:      
      //Member variables
      //Member functions      
  };
}
