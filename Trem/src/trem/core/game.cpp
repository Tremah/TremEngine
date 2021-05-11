#include <trpch.h>
#include "game.h"

namespace Trem  
{
  //initialize static fields  
  bool Game::instantiated_ = false;

  Game::Game(const std::string& name) : name_{name}, running_{false}, paused_{false}, defaultWindowSize_{glm::uvec2{1600, 800}},
                                        camera_{}
  {
    TR_ASSERT(!instantiated_, "Game class already instantiated!")
    instantiated_ = true;

    window_ = CreateShared<Window>(defaultWindowSize_.x, defaultWindowSize_.y, name_);
  }

  void Game::start()
  {
    //Init services
    ServiceLocator::setLogger(Logger{});
    ServiceLocator::setDispatcher(Dispatcher{});

    ServiceLocator::logger().debug("Game starting...");

    //after window initialization, a window is visible
    window_->init();
    camera_.init(0.f, static_cast<float>(window_->width()), 0.f, static_cast<float>(window_->height()));
    renderer_.init();
    renderer_.activeShader()->uploadUniformMat4("uMvp", camera_.viewProjectionMatrix());
        
    //set message callbacks    
    ServiceLocator::dispatcher().connect<WindowClosedEvent, &Game::handleWindowClosedEvent>(*this);
    ServiceLocator::dispatcher().connect<WindowResizedEvent, &Game::handleWindowResizedEvent>(*this);
    ServiceLocator::dispatcher().connect<WindowMinimizedEvent, &Game::handleWindowMinimizedEvent>(*this);
    
    //init game layers
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
      previousTime = currentTime;
      currentTime = Timer::now();
      DeltaSeconds deltaTime = Timer::deltaSeconds(previousTime, currentTime);
      DeltaSeconds totalTime{0}; 

      if(!paused_)
      {         
        deltaAccumulator += deltaTime;  
        while(deltaAccumulator >= desiredDelta)
        { 
          for(Layer* layer : layerList_)
          { 
            layer->update(desiredDelta);
          }          

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
      }

      window_->update();
      ServiceLocator::dispatcher().dispatch();
    }    
  }

  void Game::pause()
  {   
    std::cout << "Game paused..."; 
    paused_ = true;
  }

  void Game::resume()
  {
    paused_ = false;
  }

  void Game::shutdown()
  {
    running_ = false;
  }

  void Game::handleWindowClosedEvent(WindowClosedEvent& wcEvent)
  {
    running_ = false;
  }

  void Game::handleWindowResizedEvent(WindowResizedEvent& wrsEvent)
  {
    resume();
  }

  void Game::handleWindowMinimizedEvent(WindowMinimizedEvent& wmEvent)
  {
    pause();
  }

  void Game::addLayer(Layer* layer)
  {
    layerList_.push_back(layer);
  }

  Dispatcher& Game::dispatcher()
  {
    return dispatcher_;
  }
}
