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
      /*
        only needed if one of them is declared explicitly
    
        logger(const logger&) = default;
        logger(logger&&) = default;
        logger& operator=(const logger&) = default;
        logger& operator=(logger&&) = default;
        ~logger() = default;
      */
      
      //param. constructors

      //public member variables

      //public member functions
      static void init();
      static ShaPtr<spdlog::logger>& logger();

    protected:
      //protected member variables

      //protected member functions

    private:
      //private member variables
      static ShaPtr<spdlog::logger> logger_;

      //private member functions
      
  };
}
