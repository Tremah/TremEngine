#include <trpch.h>
#include "date.h"

namespace Trem::Util::Date
{
  std::string todayString(const std::string& pDateFormat)
  {
    //retrieve current time as seconds since epoch start
    std::time_t time = std::time(nullptr);
    //transform stream to string
    std::string dateString = timeToString(time, pDateFormat);
    
    return dateString;
  }

  std::string dateString(const std::chrono::system_clock::time_point pTimePoint, const std::string& pDateFormat)
  {
    std::time_t time = std::chrono::system_clock::to_time_t(pTimePoint);
    std::string dateString = timeToString(time, pDateFormat);
    return dateString;
  }

  std::string timeToString(const std::time_t pTime, const std::string& pDateFormat)
  {
    tm localTime{};
    localtime_s(&localTime, &pTime);
    std::ostringstream oss;
    //apply format to local time and stream into output string stream
    oss << std::put_time(&localTime, pDateFormat.c_str());
    //transform stream to string
    std::string dateString = oss.str();
    return dateString;
  }
}

