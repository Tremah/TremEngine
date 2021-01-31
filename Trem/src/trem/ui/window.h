#pragma once

//c++ includes

//external library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

//custom (own) library includes

//game engine includes
#include <trem/ui/input_codes.h>
#include <trem/event/key_events.h>
#include <trem/event/mouse_events.h>
#include <trem/event/window_events.h>
#include <trem/event/game_events.h>

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
    //event callback not in class because it cant be called by the 
    //callback lambda when inside the class
    EventCallback eventCallback_{nullptr};
  };

  class Window
  {
    public:
      Window(const Window&) = default;
      Window(Window&&) = default;
      Window& operator=(const Window&) = default;
      Window& operator=(Window&&) = default;
      
      ~Window();
      //Param. constructors
      Window(){};
      Window(uint16_t width, uint16_t height, const std::string& title);

      //Public member variables

      //Public member functions
      void init();
      GLFWwindow* nativeWindow() const;
      uint16_t width()  const;
      uint16_t height() const;
      void swapBuffer() const;

      //Window input functions
      bool keyPressed(KeyCode key) const;
      bool mouseButtonPressed(MouseCode button) const;

      //Setter
      void setEventCallback(const EventCallback& callback);

      //Getter
      glm::vec2 mousePosition() const;
      float mouseX() const;
      float mouseY() const;   

      //Event handlers      
      bool handleKeyEvent(Event &ev) const;
      bool handleMouseEvent(Event &ev) const;
      bool handleWindowEvent(Event &ev) const;

    protected:
      //protected member variables

      //protected member functions

    private:
      //private member variables
      GLFWwindow* window_ = nullptr;
      static uint8_t windowCount_;

      WindowData windowData_{};

      //private member functions
      void setGlfwCallbacks() const;
      
  };
}
