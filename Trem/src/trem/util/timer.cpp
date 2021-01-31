#include "trpch.h"
#include "timer.h"

namespace Trem
{  
  bool Timer::sessionActive_ = false;      
  TimePointType Timer::startTime_{};
  DeltaSeconds  Timer::totalTime_{};
  DeltaSeconds  Timer::frameTime_{};
  DeltaSeconds  Timer::lastFrameTime_{};

  void Timer::startSession()
  {
    sessionActive_ = true;
    startTime_ = now();
  }

  void Timer::stopSession()
  {
    sessionActive_ = false;
  }

  TimePointType Timer::now() 
  {
    return std::chrono::high_resolution_clock::now();
  }

  DeltaSeconds Timer::deltaSeconds(const TimePointType previous, const TimePointType current) 
  {
    DeltaSeconds rawDeltaTime = current - previous;
    return rawDeltaTime;
  }

  DeltaMillis Timer::deltaMillis(const TimePointType previous, const TimePointType current) 
  {
    DeltaMillis rawDeltaTime = current - previous;
    return rawDeltaTime;
  }
}
