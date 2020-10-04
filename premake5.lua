workspace "HeirloomEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "Heirloom/thirdparty/GLFW/include"
	IncludeDir["glad"] = "Heirloom/thirdparty/glad/include"
	IncludeDir["ImGui"] = "Heirloom/thirdparty/imgui"
	
	include "Heirloom/thirdparty/GLFW"
	include "Heirloom/thirdparty/glad"
	include "Heirloom/thirdparty/imgui"

	--startproject "Sandbox"

project "Heirloom"
	location "Heirloom"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hlpch.h"
	pchsource "Heirloom/src/hlpch.cpp"

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HL_PLATFORM_WINDOWS",
			"HL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines
		{
			"HL_DEBUG"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"HL_RELEASE"
		}
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HL_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Heirloom/thirdparty/spdlog/include",
		"Heirloom/include",
		"Heirloom/src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"Heirloom"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines
		{
			"HL_DEBUG"
		}
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines
		{
			"HL_RELEASE"
		}
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "HL_DIST"
		runtime "Release"
		optimize "On"