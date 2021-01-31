project "glm"
	kind "StaticLib"
	language "C++"
	architecture "x86_64"
  location ("../vendor/%{prj.name}/")	

	targetdir ("..bin/bin/" .. outputdir .. "/%{prj.name}")
  objdir    ("..bin/bin-int/" .. outputdir .. "/%{prj.name}")
  debugdir ("../vendor/%{prj.name}/")
	
	includedirs { "../vendor/%{prj.name}" }

	files
	{
		"../vendor/%{prj.name}/%{prj.name}/**"
	}

	filter "system:windows"
    cppdialect "C++17"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_GLM_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"