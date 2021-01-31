#pragma once

/**
 *  \brief Namespace for utility functions regarding date.
 */
namespace Trem::Util
{
  /**
    \brief Returns current date as a String representation in a given format.
    @param pDateFormat Format to be applied for string output.
    */
  std::string todayString(const std::string& pDateFormat);

  /**
    \brief Returns a date as a String representation in a given format.
    @param pTimePoint System clock time point for date calculation.
    @param pDateFormat Format to be applied for string output.
    */
  std::string dateString(std::chrono::system_clock::time_point pTimePoint, const std::string& pDateFormat);

  /**
    \brief Internal helper which returns a time_t as a formatted string.
    @param pTime Time to be converted to a string.
    @param pDateFormat Format to be applied for string output.
    */
  std::string timeToString(std::time_t pTime, const std::string& pDateFormat);
}

