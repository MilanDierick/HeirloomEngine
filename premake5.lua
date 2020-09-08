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

include "Heirloom/thirdparty/GLFW"

project "Heirloom"
	location "Heirloom"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HL_PLATFORM_WINDOWS",
			"HL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HL_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HL_DIST"
		optimize "On"