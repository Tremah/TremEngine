#pragma once

/**
 *  \brief Namespace for utility functions regarding time.
 */
namespace Trem::Util
{
  /**
    \brief Returns current time as std::chrono::system_clock::time_point.
    */
  std::chrono::system_clock::time_point now();

  /**
    \brief Returns delta between two time points in seconds.
    @param pTime1 First time point.
    @param pTime2 Second time point.
    */
  float deltaTime(std::chrono::system_clock::time_point pTime1, std::chrono::system_clock::time_point pTime2);
}