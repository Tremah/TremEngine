#pragma once

//c++ includes

//external library includes

//game engine includes
#include <trem/message/message.h>

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class GameEvent : public Message
  {
    public:      
      //Constructors and deconstructors 
      //Member variables
      //Member functions

    protected:
      //Protected param. constructors
      GameEvent(MsgType type) : Message(type, (MsgCategories::Event | MsgCategories::GameEvent)){}
      
      //Member variables
      //Member functions

    private:
      //Member variables
      //Member functions      
  };
  
  class GamePausedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GamePausedEvent() : GameEvent(MsgTypes::GamePaused) {}

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
  
  class GameResumedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GameResumedEvent() : GameEvent(MsgTypes::GameResumed) {}

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
  
  class GameClosedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GameClosedEvent() : GameEvent(MsgTypes::GameClosed) {}

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
