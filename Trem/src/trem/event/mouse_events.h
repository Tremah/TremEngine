#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include <trem/input/input_codes.h>

/**
 *  \brief Mouse Events
 *
 */
namespace Trem
{
  class MouseEvent
  {
    public:
      //Constructors and deconstructors 

      //Member variables

      //Member functions
      MouseCode mouseCode() const;

    protected:
      //Constructors and deconstructors
      MouseEvent(const MouseCode mouseCode) : mouseCode_{mouseCode} {}

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
      LMouseButtonPressedEvent(const MouseCode mouseCode) : MouseEvent(mouseCode) {}

      //Member variables
      
      //Member functions
      std::string toString() const;

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
      RMouseButtonPressedEvent(const MouseCode mouseCode) : MouseEvent(mouseCode) {}

      //Member variables
      
      //Member functions
      std::string toString() const;

    protected:
      //Member variables
      //Member functions

    private:      
      //Member variables
      //Member functions      
  };
}
