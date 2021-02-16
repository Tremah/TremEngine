#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes
#include <trem/core/layer.h>
#include <trem/core/window.h>
#include <trem/renderer/renderer.h>
#include <trem/renderer/camera.h>
#include <trem/message/message.h>
#include <trem/message/key_events.h>
#include <trem/message/mouse_events.h>
#include <trem/message/message_handler.h>
#include <trem/util/timer.h>
#include <trem/core/service_locator.h>

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
       * \brief Global message handler.
       * @param msg Message to be handled.
       */
      void handleMessage(UnqPtr<Message>&& msg);

      /**
       * \brief Global message handler.
       * @param msg Message to be handled.
       */
      bool handleGameMessages(const UnqPtr<Message>& msg);

      /**
       * \brief Add a game layer to the layer list.
       * @param layer Layer to be added.
       */
      void addLayer(Layer* layer);

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables

      std::string name_;
      bool running_ = false;
      bool minimized_ = false;
      ShaPtr<Window> window_;
      Renderer renderer_;
      Camera   camera_;
      MessageHandler msgHandler_;
      //EventHandler eventHandler;

      //singleton fields
      static bool instantiated_;

      //temp
      std::vector<Layer*> layerList_;
      static constexpr glm::uvec2 defaultWindowSize_{1600, 900};

      //Member functions
  };

  //to be defined in the client   
  UnqPtr<Game> createGame();
}
