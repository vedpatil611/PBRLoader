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
IncludeDirs["FreeType"] = "Dependencies/freetype/include"
IncludeDirs["ImGui"] = "Dependencies/ImGui/src"
IncludeDirs["Assimp"] = "Dependencies/assimp/inlude"
IncludeDirs["GLM"] = "Dependencies/GLM"

project "PBRLoader"
	location "PBRLoader"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	inlining "Auto"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	defines {
		"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	}
	includedirs {
		"PBRLoader/src",
		"PBRLoader/src/vendors",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.GLAD}",
		"%{IncludeDirs.FreeImage}",
		"%{IncludeDirs.FreeType}",
		"%{IncludeDirs.Assimp}",
		"%{IncludeDirs.GLM}",
		"%{IncludeDirs.ImGui}"
	}
	
	libdirs {
		"Dependencies/FreeImage/libs",
		"Dependencies/freetype/lib",
		"Dependencies/assimp/lib"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"FreeImage",
		"freetype"
	}

	files { 
		"%{prj.name}/shaders/**.glsl", 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/renderer/**.h",
		"%{prj.name}/src/renderer/**.cpp",
		"%{prj.name}/src/UI/**.h",
		"%{prj.name}/src/UI/**.cpp",
		"%{prj.name}/src/utils/**.h",
		"%{prj.name}/src/utils/**.cpp",
		"%{prj.name}/src/vendors/imgui-filebrowser/**.h"
	}

	filter "system:windows"
		links {
			"assimp-vc142-mt"
		}
		defines {
			"_CRT_SECURE_NO_WARNINGS"
		}
		postbuildcommands {
			("{COPY} ../Dependencies/FreeImage/bin ../bin/" ..outputdir.. "/PBRLoader"),
			("{COPY} ../Dependencies/assimp/bin ../bin/" ..outputdir.. "/PBRLoader")
		}

    filter "system:linux"
        links {
			"dl",
			"pthread",
            "assimp",
			"GL",
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"
