#include "trpch.h"
#include "game.h"

namespace Trem  
{
  //initialize static fields  
  bool Game::instantiated_ = false;

  Game::Game(const std::string& name) : name_{name}, msgHandler_{}
  {
    TR_ASSERT(!instantiated_, "Game class already instantiated!")
    instantiated_ = true;
    window_ = CreateShared<Window>(defaultWindowSize_.x, defaultWindowSize_.y, name_);
    camera_ = Camera{0.f, static_cast<float>(window_->width()), 0.f, static_cast<float>(window_->height())};
  }

  void Game::start()
  {

    //Init services
    ServiceLocator::setLogger(Logger{});
    ServiceLocator::logger().debug("Game starting...");

    window_->init();
    renderer_.init();
    renderer_.activeShader()->uploadUniformMat4("uMvp", camera_.viewProjectionMatrix());
        
    //set message callbacks    
    window_->setMsgCallback([this](auto&& msg) -> decltype(auto) { return this->handleMessage(std::forward<decltype(msg)>(msg)); });
    camera_.setMsgCallback([this](auto&& msg) -> decltype(auto) { return this->handleMessage(std::forward<decltype(msg)>(msg)); });

    //subscribe to message system
    msgHandler_.subscribe(MsgTypes::KeyPressed, [this](const auto& msg)          -> decltype(auto) { return this->window_->handleKeyEvent(msg); });
    msgHandler_.subscribe(MsgTypes::WindowResized, [this](const auto& msg)       -> decltype(auto) { return this->window_->handleWindowEvent(msg); });
    msgHandler_.subscribe(MsgTypes::WindowMinimized, [this](const auto& msg)     -> decltype(auto) { return this->window_->handleWindowEvent(msg); });
    msgHandler_.subscribe(MsgTypes::LMouseButtonPressed, [this](const auto& msg) -> decltype(auto) { return this->window_->handleMouseEvent(msg); });

    msgHandler_.subscribe(MsgTypes::KeyPressed, [this](const auto& msg)          -> decltype(auto) { return this->camera_.handleMessage(msg); });
    msgHandler_.subscribe(MsgTypes::KeyRepeated,[this](const auto& msg)          -> decltype(auto) { return this->camera_.handleMessage(msg); });
    msgHandler_.subscribe(MsgTypes::WindowResized, [this](const auto& msg)       -> decltype(auto) { return this->camera_.handleMessage(msg); });

    msgHandler_.subscribe(MsgTypes::WindowResized, [this](const auto& msg)       -> decltype(auto) { return this->handleGameMessages(msg); });
    msgHandler_.subscribe(MsgTypes::WindowClosed, [this](const auto& msg)        -> decltype(auto) { return this->handleGameMessages(msg); });
    msgHandler_.subscribe(MsgTypes::WindowMinimized, [this](const auto& msg)     -> decltype(auto) { return this->handleGameMessages(msg); });

   

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
    const double delta = (1000. / desiredFps);
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
      window_->update();
      msgHandler_.processQueue();
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

  void Game::handleMessage(UnqPtr<Message>&& msg)
  {
    msgHandler_.queue(std::move(msg));
  }

  bool Game::handleGameMessages(const UnqPtr<Message>& msg)
  {
    switch(msg->type())
    {
      case MsgTypes::WindowMinimized:
        pause(); 
        return true;
      case MsgTypes::WindowResized:
        resume();
        return true;
      case MsgTypes::WindowClosed:
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
