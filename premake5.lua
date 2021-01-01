workspace "HeirloomEngine"
	architecture "x64"
	startproject "Sandbox"

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
	IncludeDir["glm"] = "Heirloom/thirdparty/glm"
	
	group "Dependencies"
		include "Heirloom/thirdparty/GLFW"
		include "Heirloom/thirdparty/glad"
		include "Heirloom/thirdparty/imgui"	
	group ""

project "Heirloom"
	location "Heirloom"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hlpch.h"
	pchsource "Heirloom/src/hlpch.cpp"
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HL_PLATFORM_WINDOWS",
			"HL_BUILD_DLL",
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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

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
		"Heirloom/thirdparty",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Heirloom"
	}

	filter "system:windows"
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