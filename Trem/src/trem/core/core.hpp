#pragma once
#include <iostream>
#include <memory>
#include <filesystem>


//-----------------------
//--- compiler macros ---
//-----------------------

#if TR_DEBUG == 1 
  
	#define LOG(msg) std::cout << msg << " (" << std::filesystem::path(__FILE__).filename().string() << ", line: " << __LINE__ << ")) " << std::endl;
	#define STR(msg) #msg
	#define TR_ASSERT(condition, msg) \
	  {\
		  if(!(condition)) \
		  {\
        std::string error = "failed assert ("; \
			  error.append(STR(condition)); \
        error.append(" ): "); \
			  error.append(msg); \
			  LOG(error); \
        __debugbreak(); \
		  }\
    }
#else
  #define LOG(msg){}
	#define STR(msg){}
	#define TR_ASSERT(condition, msg){}
#endif

#define BIT(shift) (1 << shift)

//----------------------------
//--- global functionality ---
//----------------------------

namespace Trem {
  //wrapper for unique pointer generation
	template<typename T>
	using UnqPtr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr UnqPtr<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	//wrapper for shared pointer generation
	template<typename T>
	using ShaPtr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr ShaPtr<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}