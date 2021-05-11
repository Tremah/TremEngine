#pragma once

//c++ includes

//external library includes

//game engine includes

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class GameEvent 
  {
    public:      
      //Constructors and deconstructors 
      //Member variables
      //Member functions

    protected:
      //Protected param. constructors
      GameEvent(){}
      
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
      GamePausedEvent() : GameEvent() {}

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
  
  class GameResumedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GameResumedEvent() : GameEvent() {}

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
  
  class GameClosedEvent : public GameEvent
  {
    public:
      //Public param. constructors
      GameClosedEvent() : GameEvent() {}

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
