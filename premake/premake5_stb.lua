project "stb"
	kind "StaticLib"
	language "C++"
	architecture "x86_64"
  location ("../vendor/%{prj.name}/")
  
  targetdir ("..bin/bin/" .. outputdir .. "/%{prj.name}")
  objdir    ("..bin/bin-int/" .. outputdir .. "/%{prj.name}")
  debugdir ("../vendor/%{prj.name}/")
  
  files
  {
    "../vendor/%{prj.name}/%{prj.name}/**.h", 
    "../vendor/%{prj.name}/%{prj.name}/**.cpp"
  }
  
  includedirs { "../vendor/%{prj.name}/" }

  filter "system:windows"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"
  
  filter "configurations:Debug"
    defines "STB_DEBUG"
    symbols "On"
  
  filter "configurations:Release"
    defines "STB_RELEASE"
    symbols "On"