#pragma once

//c++ includes

//external library includes

//game engine includes
#include <trem/event/event.h>

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class GameEvent : public Event
  {
    public:
      //Param. constructors
      //Public member variables
      //Public member functions
      EVENT_CATEGORY(EventCategory::GameEvent)

    protected:
      //Protected param. constructors
      GameEvent() : Event(){}
      
      //Protected member variables
      //Protected member functions

    private:
      //Private member variables
      //Private member functions      
  };
  
  class GamePausedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GamePausedEvent() : GameEvent() {}

      //Public member variables 
      //Public member functions
      EVENT_TYPE(GamePaused)
      std::string toString() const override;     

    protected:
      //Protected param. constructors
      //Protected member variables
      //Protected member functions

    private:
      //Private member variables
      //Private member functions 
  };
  
  class GameResumedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GameResumedEvent() : GameEvent() {}

      //Public member variables 

      //Public member functions
      EVENT_TYPE(GameResumed)
      std::string toString() const override;     

    protected:
      //Protected param. constructors
      //Protected member variables
      //Protected member functions

    private:
      //Private member variables
      //Private member functions 
  };
  
  class GameClosedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GameClosedEvent() : GameEvent() {}

      //Public member variables 
      //Public member functions
      EVENT_TYPE(GameClosed)
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
