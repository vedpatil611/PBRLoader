workspace "PBRLoader"
	architecture "x64"
	startproject "PBRLoader"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies/GLFW"
include "Dependencies/GLAD"
include "Dependencies/ImGui"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Dependencies/GLFW/include"
IncludeDirs["GLAD"] = "Dependencies/GLAD/include"
IncludeDirs["FreeImage"] = "Dependencies/FreeImage/include"
IncludeDirs["ImGui"] = "Dependencies/ImGui/src"

project "PBRLoader"
	location "PBRLoader"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	inlining "Auto"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"PBRLoader/src",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.FreeImage}",
		"%{IncludeDirs.ImGui}"
	}
	
	libdirs {
		"Dependencies/FreeImage/libs"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui"
	}

	files { 
		"%{prj.name}/shaders/**.glsl", 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"
