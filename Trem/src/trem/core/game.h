#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include <trem/core/layer.h>
#include <trem/core/window.h>
#include <trem/renderer/renderer.h>
#include <trem/renderer/camera.h>
#include <trem/event/key_events.h>
#include <trem/event/mouse_events.h>
#include <trem/util/timer.h>
#include <trem/core/service_locator.h>
#include <trem/signal/signal.hpp>
#include <trem/signal/dispatcher.hpp>

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
      //Constructors and deconstructors     
      Game(const std::string& name);

      //Member variables

      //Member functions
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
       *        Called after the game was halted through a message and needs to be restarted.
       */
      void resume();
      
      /**
       * \brief Shutdown the game.<br>
       */
      void shutdown();

      /**
       * \brief Add a game layer to the layer list.
       * @param layer Layer to be added.
       */
      void addLayer(Layer* layer);

      /**
       * \brief Return the dispatcher
       * @param layer Layer to be added.
       */
      Dispatcher& dispatcher();

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables

      std::string name_;
      bool running_;
      bool paused_;
      ShaPtr<Window> window_;
      Renderer renderer_;
      Camera   camera_;
      Dispatcher dispatcher_;

      //singleton fields
      static bool instantiated_;

      //temp
      std::vector<Layer*> layerList_;
      glm::uvec2 defaultWindowSize_;
      //Member functions

      void handleWindowClosedEvent(WindowClosedEvent& wcEvent);
      void handleWindowResizedEvent(WindowResizedEvent& wrsEvent);
      void handleWindowMinimizedEvent(WindowMinimizedEvent& wmEvent);
  };

  //to be defined in the client   
  UnqPtr<Game> createGame();
}
