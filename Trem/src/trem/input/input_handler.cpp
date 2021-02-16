#include "trpch.h"
#include "input_handler.h"

namespace Trem
{
  bool InputHandler::keyPressed(KeyCode key) const
  {
    int pressed = glfwGetKey(window_->nativeWindow(), key);
    return pressed == GLFW_PRESS || pressed == GLFW_REPEAT;
  }

  glm::dvec2 InputHandler::mouseCoordinates() const
  {
    glm::dvec2 mouseCoordinates{0};
    glfwGetCursorPos(window_->nativeWindow(), &mouseCoordinates.x, &mouseCoordinates.y);
    return mouseCoordinates;
  }

  bool InputHandler::mouseButtonPressed(MouseCode button) const
  {
    int pressed = glfwGetMouseButton(window_->nativeWindow(), button);    
    return pressed == GLFW_PRESS;
  }
}
