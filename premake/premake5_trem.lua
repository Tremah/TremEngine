project "Trem"
	kind "StaticLib"
	language "C++"
  location ("../%{prj.name}/")
  
  targetdir ("..bin/bin/" .. outputdir .. "/%{prj.name}")
  objdir    ("..bin/bin-int/" .. outputdir .. "/%{prj.name}")
  debugdir  ("../%{prj.name}/")
  
  pchheader "trpch.h"
  pchsource "../%{prj.name}/src/trpch.cpp"
  
  includedirs
  {
    "../%{prj.name}/src/",
    "../vendor/glad/include/",
    "../vendor/glfw/include/",
    "../vendor/glm",
    "../vendor/stb",
    "../vendor/json/include/",
    "../vendor/spdlog/include/"
  }
  
  files
  {
    "../%{prj.name}/src/**.h",
    "../%{prj.name}/src/**.hpp",
    "../%{prj.name}/src/**.cpp",  
    "../%{prj.name}/src/**.inl",  
  }  
  
  links { "glad", "glfw", "glm", "stb", "spdlog" }

  filter "system:windows"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"
  
  filter "configurations:Debug"
    defines "TR_DEBUG=1"
    symbols "On"
  
  filter "configurations:Release"
    defines "TR_RELEASE=1"
    symbols "On"