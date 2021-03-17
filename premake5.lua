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
IncludeDirs["Assimp"] = "Dependencies/assimp/inlude"

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
		"%{IncludeDirs.Assimp}"
	}
	
	libdirs {
		"Dependencies/FreeImage/libs",
		"Dependencies/assimp/lib"
	}
	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"assimp-vc142-mt"
	}

	files { 
		"%{prj.name}/shaders/**.glsl", 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/utils/**.h",
		"%{prj.name}/src/utils/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		postbuildcommands {
			("{COPY} ../Dependencies/FreeImage/bin ../bin/" ..outputdir.. "/PBRLoader"),
			("{COPY} ../Dependencies/assimp/bin ../bin/" ..outputdir.. "/PBRLoader")
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"
