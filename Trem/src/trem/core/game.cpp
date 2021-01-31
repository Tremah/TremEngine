#include "trpch.h"
#include "game.h"

namespace Trem  
{
  Game::Game(const std::string& name) : name_{name}, window_{defaultWindowSize_.x, defaultWindowSize_.y, name_}
  {
    camera_ = Camera{0.f, static_cast<float>(window_.width()), 0.f, static_cast<float>(window_.height())};
    //set event callbacks
    window_.setEventCallback([this](auto&&... args) -> decltype(auto) { return this->handleEvent(std::forward<decltype(args)>(args)...); });
    camera_.setEventCallback([this](auto&&... args) -> decltype(auto) { return this->handleEvent(std::forward<decltype(args)>(args)...); });
    //eventHandler_ = EventHandler{};
  }

  void Game::start()
  {
    std::cout << "Game starting..." << std::endl;
    Logger::init();    

    window_.init();
    renderer_.init();
    renderer_.activeShader()->uploadUniformMat4("uMvp", camera_.viewProjectionMatrix());

    for(auto& layer : layerList_)
    {
      layer->init(renderer_.textureManager());
    }

    running_ = true;
  }

  void Game::run()
  {
    auto previousTime = Timer::now();
    auto currentTime = previousTime;

    const auto desiredFps = 60;
    const double delta = (1000 / 60);
    const DeltaMillis desiredDelta{delta};
    DeltaSeconds deltaAccumulator{0};
    
    while(running_)
    {
      //timing
      glfwPollEvents();
      previousTime = currentTime;
      currentTime = Timer::now();
      DeltaSeconds deltaTime = Timer::deltaSeconds(previousTime, currentTime);
      DeltaSeconds totalTime{0};
      deltaAccumulator += deltaTime;   

      while(deltaAccumulator >= desiredDelta)
      { 
        TimePointType beforeUpdate = Timer::now();
        for(Layer* layer : layerList_)
        { 
          layer->update(desiredDelta);
        }          
        TimePointType afterUpdate = Timer::now();
        DeltaSeconds updateDuration = Timer::deltaSeconds(beforeUpdate, afterUpdate);
        //Logger::logger()->debug("update duration = {0}", updateDuration.count());

        deltaAccumulator -= desiredDelta;        
        totalTime += desiredDelta;
      }
      
      renderer_.beginScene();
      renderer_.activeShader()->uploadUniformMat4("uMvp", camera_.viewProjectionMatrix());
      
      for(Layer* layer : layerList_)
      {        
        layer->render(renderer_);
      }      
      renderer_.endScene();
      window_.swapBuffer();
    }    
  }

  void Game::pause()
  {   
    std::cout << "Game paused..."; 
    running_ = false;
    while(running_ == false)
    {
      glfwPollEvents();
    }
  }

  void Game::resume()
  {
    running_ = true;
    //run();
  }

  void Game::shutdown()
  {
    running_ = false;
  }

  void Game::handleEvent(Event& ev)
  {
    EventHandler eventHandler{ev};   
    //dispatch to camera
    eventHandler.dispatch<KeyPressedEvent>([this](auto&&... args)          -> decltype(auto) { return this->camera_.handleEvent(std::forward<decltype(args)>(args)...); });
    eventHandler.dispatch<KeyRepeatedEvent>([this](auto&&... args)         -> decltype(auto) { return this->camera_.handleEvent(std::forward<decltype(args)>(args)...); });
    eventHandler.dispatch<WindowResizedEvent>([this](auto&&... args)       -> decltype(auto) { return this->camera_.handleEvent(std::forward<decltype(args)>(args)...); });

    //dispatch to window
    eventHandler.dispatch<KeyPressedEvent>([this](auto&&... args)          -> decltype(auto) { return this->window_.handleKeyEvent(std::forward<decltype(args)>(args)...); });
    eventHandler.dispatch<LMouseButtonPressedEvent>([this](auto&&... args) -> decltype(auto) { return this->window_.handleMouseEvent(std::forward<decltype(args)>(args)...); });
    //eventHandler.dispatch<WindowResizedEvent>([this](auto&&... args)       -> decltype(auto) { return this->window_.handleWindowEvent(std::forward<decltype(args)>(args)...); });
    eventHandler.dispatch<WindowMinimizedEvent>([this](auto&&... args)     -> decltype(auto) { return this->window_.handleWindowEvent(std::forward<decltype(args)>(args)...); });

    //application level events, dispatch to internal functions
    eventHandler.dispatch<WindowResizedEvent>([this](auto&&... args)   -> decltype(auto) { return this->handleGameEvents(std::forward<decltype(args)>(args)...); });
    eventHandler.dispatch<WindowMinimizedEvent>([this](auto&&... args) -> decltype(auto) { return this->handleGameEvents(std::forward<decltype(args)>(args)...); });
    eventHandler.dispatch<WindowClosedEvent>([this](auto&&... args)    -> decltype(auto) { return this->handleGameEvents(std::forward<decltype(args)>(args)...); });
  }

  bool Game::handleGameEvents(Event& ev)
  {
    switch(ev.type())
    {
      case EventType::WindowMinimized:
        pause(); 
        return true;
      case EventType::WindowResized:
        resume();
        return true;
      case EventType::WindowClosed:
        running_ = false;
        return true;
      default:
        return false;
    }
  }

  void Game::addLayer(Layer* layer)
  {
    layerList_.push_back(layer);
  }
}
