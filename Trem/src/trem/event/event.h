#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes

namespace Trem
{
  /**
    \brief Defines event types.
   */
  enum class EventType
  {
    Empty = 0,
    GamePaused, GameResumed, GameClosed, 
    KeyPressed, KeyRepeated, KeyReleased,
    MouseMoved, LMouseButtonPressed, RMouseButtonPressed,
    WindowResized, WindowMinimized, WindowClosed
  };

  /**
    \brief Defines event categories.
   */
  enum EventCategory
  {
    Empty         = 0,    
    GameEvent     = BIT(1),  
    InputEvent    = BIT(2),
    KeyboardEvent = BIT(3),
    MouseEvent    = BIT(4),
    WindowEvent   = BIT(5)
  };   

  //Macros to simplify inheritance 
  //every child class will call these macros to implement the necessary functionality

  #define EVENT_TYPE(eventType) static EventType staticType() { return EventType::eventType; } \
                                virtual EventType type() const override { return staticType(); }\
                                virtual std::string name() const override { return #eventType; }

  #define EVENT_CATEGORY(category) virtual uint32_t categories() const override { return category; }                         
  /**
   *  \brief Base class for events.<br>
   *         Each specific event will inherit its base properties from this class.
   */
  class Event
  {
    public:      
      virtual ~Event() = default;

      //param. constructors

      //public member variables
      bool handled_ = false;  /**< Was the event handled already. */

      //public member functions
      virtual EventType type()       const = 0;
      virtual std::string name()     const = 0;
      virtual uint32_t categories()  const = 0;     
      virtual std::string toString() const = 0;

      bool inCategory(EventCategory category) const;

    protected:
      //protected member variables
      //protected member functions

    private:      
      //private member variables
      //private member functions
  };
  
  //set global event callback type
  using EventCallback = std::function<void(Event&)>;
}
