#pragma once

//c++ includes

//external library includes

//game engine includes
#include <trem/util/logger.h>

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
      
      //Member variables

      //Member functions      
      //Setter
      static void setLogger(Logger&& logger);

      //Getter
      static spdlog::logger& logger();


    protected:
      //Member variables

      //Member functions

    private:
      //Private constructor

      //Services
      static Logger logger_;
      
      //Member functions

      
  };
}
