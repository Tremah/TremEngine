#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include "message.h"
#include <trem/input/input_codes.h>
#include <trem/core/service_locator.h>

/**
 *  \brief Keyboard Events
 *
 */
namespace Trem
{
  class KeyEvent : public Message
  {
    public:
      //Constructors and deconstructors 
      virtual ~KeyEvent() = default;
      
      //Member variables

      //Member functions
      KeyCode keycode() const;

    protected:
      //protected default constructors
      KeyEvent(const KeyEvent&) = default;
      KeyEvent(KeyEvent&&) = default;
      KeyEvent& operator=(const KeyEvent&) = default;
      KeyEvent& operator=(KeyEvent&&) = default; 

      //Constructors and deconstructors
      KeyEvent(const KeyCode keyCode, const MsgType type) : 
        Message(type, (MsgCategories::Event | MsgCategories::InputEvent | MsgCategories::KeyboardEvent)), 
        keyCode_{keyCode} {}

      //Member variables
      KeyCode keyCode_;

      //Member functions

    private:      
      //Member variables
      //Member functions      
  };

  class KeyPressedEvent : public KeyEvent
  {
    public:
      //Constructors and deconstructors 
      KeyPressedEvent(const KeyCode keyCode) : KeyEvent(keyCode, MsgTypes::KeyPressed) {}
      //~KeyPressedEvent() {ServiceLocator::logger().debug("KeyPressedEvent deleted");}

      //Member variables
      
      //Member functions
      /**
       * \brief Returns the message type of the class.
       * \return Class wide message type
       */
      static MsgType staticMsgType() { return MsgTypes::KeyPressed; }
      std::string toString() const override;

    protected:
      //Member variables
      //Member functions

    private:      
      //Member variables
      //Member functions      
  };

  class KeyReleasedEvent : public KeyEvent
  {
    public:
      //Constructors and deconstructors 
      KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode, MsgTypes::KeyReleased) {}

      //Member variables
      
      //Member functions
      static MsgType staticMsgType() { return MsgTypes::KeyReleased; }
      std::string toString() const override;

    protected:
      //Member variables
      //Member functions

    private:      
      //Member variables
      //Member functions      
  };

  class KeyRepeatedEvent : public KeyEvent
  {
    public:
      //Constructors and deconstructors 
      KeyRepeatedEvent(const KeyCode keyCode) : KeyEvent(keyCode, MsgTypes::KeyRepeated) {}

      //Member variables
      
      //Member functions
      static MsgType staticMsgType() { return MsgTypes::KeyRepeated; }
      std::string toString() const override;

    protected:
      //Member variables
      //Member functions

    private:      
      //Member variables

      //Member functions      
  };

  
}
