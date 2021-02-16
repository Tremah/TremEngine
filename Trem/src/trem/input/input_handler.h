#pragma once

//c++ includes

//external library includes
#include <glm/vec2.hpp>

//game engine includes
#include <trem/core/window.h>
#include "input_codes.h"

/**
 *  \brief Class to handle user input.
 *
 */
namespace Trem
{
  class InputHandler
  {
    public:      
      //Constructors and deconstructors 
      InputHandler(ShaPtr<Window> window) : window_{std::move(window)}{}

      //Member variables

      //Member functions
      
      //Input polling
      bool keyPressed(KeyCode key) const;

      glm::dvec2 mouseCoordinates() const;
      bool mouseButtonPressed(MouseCode button) const;

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables
      ShaPtr<Window> window_;

      //Member functions
      
  };
}
