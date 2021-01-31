#pragma once

//c++ includes

//external library includes

//custom (own) library includes

//game engine includes

/**
 *  \brief Class to implement timing functionality.
 *
 */
namespace Trem
{
  //for type simplification
  using TimePointType = std::chrono::high_resolution_clock::time_point;
  using DeltaSeconds  = std::chrono::duration<double, std::ratio<1>>;
  using DeltaMillis   = std::chrono::duration<double, std::ratio<1, 1000>>;

  class Timer
  {

    public:
      //param. constructors

      //public member variables

      //public member functions
      static void startSession();
      static void stopSession();
      static TimePointType now();
      static DeltaSeconds deltaSeconds(TimePointType previous, TimePointType current);    
      static DeltaMillis  deltaMillis(TimePointType previous, TimePointType current);    

    protected:
      //protected member variables

      //protected member functions

    private:
      //private member variables
      static bool sessionActive_;      
      static TimePointType startTime_;
      static DeltaSeconds  totalTime_;
      static DeltaSeconds  frameTime_;
      static DeltaSeconds  lastFrameTime_;

      //private member functions
      
  };
}
