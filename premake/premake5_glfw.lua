project "glfw"
	kind "StaticLib"
	language "C"
	architecture "x86_64"
  location ("../vendor/%{prj.name}/")

	targetdir ("..bin/bin/" .. outputdir .. "/%{prj.name}")
  objdir    ("..bin/bin-int/" .. outputdir .. "/%{prj.name}")
  debugdir ("../vendor/%{prj.name}/")
	
	includedirs { "../vendor/%{prj.name}/include/" }

	files
	{
		"../vendor/glfw/src/glfw_config.h",
		"../vendor/glfw/src/context.c",
		"../vendor/glfw/src/init.c",
		"../vendor/glfw/src/input.c",
		"../vendor/glfw/src/monitor.c",
		"../vendor/glfw/src/vulkan.c",
		"../vendor/glfw/src/window.c"
	}

	filter "system:windows"
    cppdialect "C++17"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"../vendor/glfw/src/win32_init.c",
			"../vendor/glfw/src/win32_joystick.c",
			"../vendor/glfw/src/win32_monitor.c",
			"../vendor/glfw/src/win32_time.c",
			"../vendor/glfw/src/win32_thread.c",
			"../vendor/glfw/src/win32_window.c",
			"../vendor/glfw/src/wgl_context.c",
			"../vendor/glfw/src/egl_context.c",
			"../vendor/glfw/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"