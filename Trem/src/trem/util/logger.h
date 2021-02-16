#pragma once

//c++ includes

//external library includes
#pragma warning(push, 0)
  #include <spdlog/spdlog.h>
  #include "spdlog/sinks/stdout_color_sinks.h"
  #include <spdlog/fmt/ostr.h>
#pragma warning(pop)

//custom (own) library includes

//game engine includes

/**
 *  \brief Brief Description
 *
 */
namespace Trem
{
  class Logger
  {
    public:
      //Constructors and deconstructors
      Logger(); 

      //Member variables
      spdlog::logger& logger();

      //Member functions

    protected:
      //Member variables

      //Member functions

    private:
      //Member variables
      spdlog::logger logger_ = spdlog::logger("Default Logger");

      //Member functions
      
  };
}
