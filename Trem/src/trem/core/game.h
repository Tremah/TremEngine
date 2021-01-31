#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include <trem/core/layer.h>
#include <trem/ui/window.h>
#include <trem/renderer/renderer.h>
#include <trem/renderer/camera.h>
#include <trem/event/event.h>
#include <trem/event/key_events.h>
#include <trem/event/mouse_events.h>
#include <trem/event/event_handler.hpp>
#include <trem/util/timer.h>

/**
 *  \brief Foundation class for a game.<br>
 *  Every game has to be a child of this class and will automatically start and run the game loop.<br>
 *  The game can then define game layers to be iterated over in each loop to call their update methods.
 *
 */
namespace Trem
{  
  class Game
  {
    public:   
      //param. constructors      
      Game(const std::string& name);

      //public member variables

      //public member functions
      /**
       * \brief Initializes the game window, renderer state variables and logger.<br>
       *        Calls init functions of the game layers.
       */
      void start();

      /**
       * \brief Runs the game loop.
       */
      void run();

      /**
       * \brief Pauses the game.
       */
      void pause();

      /**
       * \brief Restarts the game loop.<br>
       *        Called after the game was halted through an event and needs to be restarted.
       */
      void resume();
      
      /**
       * \brief Shutdown the game.<br>
       */
      void shutdown();

      /**
       * \brief Global event handler.
       * @param ev Event to be handled.
       */
      void handleEvent(Event& ev);

      /**
       * \brief Global event handler.
       * @param ev Event to be handled.
       */
      bool handleGameEvents(Event& ev);

      /**
       * \brief Add a game layer to the layer list.
       * @param layer Layer to be added.
       */
      void addLayer(Layer* layer);

    protected:
      //protected member variables

      //protected member functions

    private:
      //private member variables
      static constexpr glm::uvec2 defaultWindowSize_{1600, 900};

      std::string name_;
      bool running_ = false;
      bool minimized_ = false;
      Window window_;
      Renderer renderer_;
      Camera   camera_;
      //EventHandler eventHandler;

      std::vector<Layer*> layerList_;

      //private member functions
  };

  //to be defined in the client   
  UnqPtr<Game> createGame();
}
