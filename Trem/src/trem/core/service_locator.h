#pragma once

//c++ includes

//external library includes

//game engine includes
#include <trem/util/logger.h>
#include <trem/signal/dispatcher.hpp>

/**
 *  \brief Global access point for game wide functionality.<br>
 *         Currently provides logging and input handling.
 */
namespace Trem
{
  class ServiceLocator
  {
    public:      
      //Constructors and deconstructors 
      ServiceLocator();
      
      //Member variables

      //Member functions      
      //Setter
      static void setLogger(Logger&& logger);
      static void setDispatcher(Dispatcher&& logger);

      //Getter
      static spdlog::logger& logger();
      static Dispatcher& dispatcher();


    protected:
      //Member variables

      //Member functions

    private:
      //Private constructor

      //Member variables
      inline static bool instantiated_ = false;

      //Services
      inline static Logger logger_;
      inline static Dispatcher dispatcher_;
      
      //Member functions

      
  };
}
