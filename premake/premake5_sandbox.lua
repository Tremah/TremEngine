project "Sandbox"
	kind "ConsoleApp"
	language "C++"
  architecture "x86_64"
  location ("../%{prj.name}/")
  
  targetdir ("..bin/bin/" .. outputdir .. "/%{prj.name}")
  objdir    ("..bin/bin-int/" .. outputdir .. "/%{prj.name}")
  debugdir  ("../%{prj.name}/")
  
  includedirs
  {
    "../%{prj.name}/src/",
    "../Trem/src",
    "../vendor/glad/include/",
    "../vendor/glfw/include/",
    "../vendor/glm",
    "../vendor/stb",
    "../vendor/json/include/",
    "../vendor/spdlog/include/"
  }
  
  files
  {
    "../%{prj.name}/*.cpp",
    "../%{prj.name}/*.hpp",
    "../%{prj.name}/*.h",
    "../%{prj.name}/src/**.h",
    "../%{prj.name}/src/**.hpp",
    "../%{prj.name}/src/**.cpp",  
  }  
  
  links { "Trem", "glad", "glfw", "glm", "stb", "spdlog"}

  filter "system:windows"
    staticruntime "on"
		systemversion "latest"
    cppdialect "C++17"
  
  filter "configurations:Debug"
    defines "SB_DEBUG=1"
		runtime "Debug"
    symbols "On"
  
  filter "configurations:Release"
    defines "SB_RELEASE=1"
		runtime "Release"
    optimize "On"