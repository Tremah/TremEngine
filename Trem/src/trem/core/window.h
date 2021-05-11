#pragma once

//c++ includes

//external library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//custom (own) library includes

//game engine includes
#include <trem/input/input_codes.h>
#include <trem/event/key_events.h>
#include <trem/event/mouse_events.h>
#include <trem/event/window_events.h>
#include <trem/event/game_events.h>
#include <trem/core/service_locator.h>

/**
 *  \brief Parent class for any object within the game
 *
 */
namespace Trem
{
  //opengl, glfw callbacks
  static void glDebugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
  static void glfwErrorCallback(int error, const char* description);
  static void glfwFramebufferSizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight);
  static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

  /**
   *  \brief Struct to hold information about the window.
   *
   */
  struct WindowData
  {
    uint16_t width_;
    uint16_t height_;
    std::string title_; /**< window title*/
  };

  class Window
  {
    public:
      //Constructors and deconstructors 
      Window(const Window&) = default;
      Window(Window&&) = default;
      Window& operator=(const Window&) = default;
      Window& operator=(Window&&) = default;      
      ~Window();

      Window(){};
      Window(uint16_t width, uint16_t height, const std::string& title);

      //Member variables
      //Member functions
      void init();
      void update() const;

      //Window input functions
      bool keyPressed(KeyCode key) const;
      bool mouseButtonPressed(MouseCode button) const;

      //Setter

      //Getter
      glm::vec2 mousePosition() const;
      float mouseX() const;
      float mouseY() const; 
      uint16_t width()  const;
      uint16_t height() const;  
      GLFWwindow* nativeWindow() const;

      //Event handlers      
      bool handleKeyEvent(KeyPressedEvent& kpEvent) const;
      bool handleMouseEvent(LMouseButtonPressedEvent& lmbpEvent) const;

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables
      GLFWwindow* window_ = nullptr;
      static uint8_t windowCount_;
      WindowData windowData_{};

      //Member functions
      void swapBuffer() const;
      void setGlfwCallbacks() const;
      
  };
}
