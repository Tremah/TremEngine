workspace "GameDev"
  location "../"
  architecture "x86_64"
  startproject "Sandbox"
  
  configurations
  {
    "Debug",
    "Release"
  }
  
outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"
  
include "premake5_trem.lua"
include "premake5_Sandbox.lua"
include "premake5_glad.lua"
include "premake5_glfw.lua"
include "premake5_glm.lua"
include "premake5_stb.lua"
include "premake5_spdlog.lua"
--include "premake5_json.lua"
--include "premake5_AlleyWay.lua"