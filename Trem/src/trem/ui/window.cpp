#include <trpch.h>
#include "Window.h"

namespace Trem
{
  //init global window count
  uint8_t Window::windowCount_ = 0;

  Window::~Window()
  {
    glfwDestroyWindow(window_);
  }

  Window::Window(const uint16_t width, const uint16_t height, const std::string& title)
  {
    windowData_.width_  = width;
    windowData_.height_ = height;
    windowData_.title_  = title;    
  }

  void Window::init()
  {
    if (windowCount_ == 0)
    {
      //init glfw
      int success = glfwInit();
      TR_ASSERT(success, "GLFW could not be initialized!");
    }

    //create window and context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    window_ = glfwCreateWindow(windowData_.width_, windowData_.height_, windowData_.title_.c_str(), nullptr, nullptr);
    TR_ASSERT(window_, "Window could not be initialized!");
    glfwMakeContextCurrent(window_);
    glfwSetWindowPos(window_, 300, 100);


    //load GLAD;
    int gladStatus = gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
    TR_ASSERT(gladStatus, "GLAD could not be initialized!")

    //create viewport
    glViewport(0, 0, windowData_.width_, windowData_.height_);

    //opengl debugging
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);    
    //set callbacks
    setGlfwCallbacks();


    //texture blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //disable vsync
    glfwSwapInterval(0);

    //supply GLFW with the windowData struct
    glfwSetWindowUserPointer(window_, &windowData_);    

    windowCount_++;

    //print opengl info
    Logger::logger()->debug("Graphics vendor: {0}", glGetString(GL_VENDOR));
    Logger::logger()->debug("Graphics card: {0}", glGetString(GL_RENDERER));
    Logger::logger()->debug("OpenGL version: {0}", glGetString(GL_VERSION));
  }

  GLFWwindow* Window::nativeWindow() const
  {
    return window_;
  }

  uint16_t Window::width() const
  {
    return windowData_.width_;
  }

  uint16_t Window::height() const
  {
    return windowData_.height_;
  }

  void Window::swapBuffer() const
  {
    glfwSwapBuffers(window_);
  }

  bool Window::keyPressed(const KeyCode key) const
  {
    auto state = glfwGetKey(window_, static_cast<int>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool Window::mouseButtonPressed(const MouseCode button) const
  {
    auto state = glfwGetMouseButton(window_, static_cast<int>(button));
    return state == GLFW_PRESS;    
  }

  void Window::setEventCallback(const EventCallback& callback)
  {
    windowData_.eventCallback_ = callback;
  }

  glm::vec2 Window::mousePosition() const
  {
    double x, y;
    glfwGetCursorPos(window_, &x, &y);
    return {static_cast<float>(x), static_cast<float>(y)};
  }

  float Window::mouseX() const
  {
    return mousePosition().x;
  }

  float Window::mouseY() const
  {
    return mousePosition().y;
  }

  bool Window::handleKeyEvent(Event& ev) const
  {
    if(ev.type() == EventType::KeyPressed || ev.type() == EventType::KeyReleased)
    {
      KeyEvent* keyEvent = static_cast<KeyEvent*>(&ev);
      if(keyEvent->keycode() == Key::Escape)
      {
        WindowClosedEvent windowClosedEvent{};
        windowData_.eventCallback_(windowClosedEvent);
        return true;
      }
    }
    return false;
  }

  bool Window::handleMouseEvent(Event& ev) const
  {
    Logger::logger()->debug("mouse coordinates on click: {0}, {1}", mouseX(), static_cast<float>(windowData_.height_) - mouseY());
    return false;
  }

  bool Window::handleWindowEvent(Event& ev) const
  {
    return false;
  }

  void Window::setGlfwCallbacks() const
  {
    //Key callback
    glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
      if(action == GLFW_PRESS)
      {
        KeyPressedEvent ev{static_cast<KeyCode>(key)};
        data->eventCallback_(ev);
      }
      else if(action == GLFW_REPEAT)
      {
        KeyRepeatedEvent ev{static_cast<KeyCode>(key)};
        data->eventCallback_(ev);
      }
      else if(action == GLFW_RELEASE)
      {
        KeyReleasedEvent ev{static_cast<KeyCode>(key)};
        data->eventCallback_(ev);
      }   
    });

    //Mouse callback
    glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods)
    {
      auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
      int buttonAction = action == GLFW_PRESS ? GLFW_PRESS : GLFW_RELEASE;
      if(button == Mouse::ButtonLeft)
      {
        LMouseButtonPressedEvent ev{Mouse::ButtonLeft};
        data->eventCallback_(ev);
      }   
      else if(button == Mouse::ButtonRight)
      {
        LMouseButtonPressedEvent ev{Mouse::ButtonRight};
        data->eventCallback_(ev);
      }   
    });

    //Framebuffer size callback
    glfwSetFramebufferSizeCallback(window_,[](GLFWwindow* window, int width, int height)
    {
      auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
      glViewport(0, 0, width, height);
      data->width_  = static_cast<uint16_t>(width);
      data->height_ = static_cast<uint16_t>(height);     

      if(data->width_ == 0 && data->height_ == 0)
      {
        //window minimized
        WindowMinimizedEvent ev{};
        data->eventCallback_(ev);     
      }
      else
      {
        //window resized
        WindowResizedEvent ev{data->width_, data->height_};
        data->eventCallback_(ev);
      }
    });

    glfwSetWindowCloseCallback(window_,[](GLFWwindow* window)
    {
      auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
      WindowClosedEvent ev{};
      data->eventCallback_(ev);     
    });

    //Error callback
    glfwSetErrorCallback([](const int error, const char* description)
    {
      std::string errorMessage;
      errorMessage.append("error:").append(std::to_string(error)).append(" message: ").append(description);
      LOG(errorMessage)
    
    });
    
    //OpenGL debug callback
    glDebugMessageCallback([](GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
    {
      if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
      std::cout << "Debug message (" << id << "): " << message << std::endl;

      switch (source)
      {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
      }
      std::cout << std::endl;

      switch (type)
      {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
      }
      std::cout << std::endl;

      switch (severity)
      {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
      }
      std::cout << std::endl;
      std::cout << "---------------" << std::endl;
      std::cout << std::endl;    
    }, nullptr);
  }

  void glDebugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
  {
    
  }
}
