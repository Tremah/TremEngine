project "spdlog"
	kind "StaticLib"
	language "C++"
	architecture "x86_64"
  location ("../vendor/%{prj.name}/")	

	targetdir ("..bin/bin/" .. outputdir .. "/%{prj.name}")
  objdir    ("..bin/bin-int/" .. outputdir .. "/%{prj.name}")
  debugdir ("../vendor/%{prj.name}/")
	
	includedirs { "../vendor/%{prj.name}/include" }

	files
	{
		"../vendor/%{prj.name}/src/**"
	}

	filter "system:windows"
    cppdialect "C++17"
		systemversion "latest"
		staticruntime "On"    
    defines "SPDLOG_COMPILED_LIB"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"