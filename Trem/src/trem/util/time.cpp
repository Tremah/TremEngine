#include <trpch.h>
#include <trem/util/time.h>

namespace Trem::Util
{
  std::chrono::system_clock::time_point now()
  {
    auto now = std::chrono::system_clock::now();
    return now;
  }

  float deltaTime(std::chrono::system_clock::time_point pTime1,
                  std::chrono::system_clock::time_point pTime2)
  {
    std::chrono::duration<float, std::ratio<1>> rawDeltaTime = pTime2 - pTime1;
    float deltaTime = rawDeltaTime.count();

    return deltaTime;
  }
}
