-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "thirdparty/GLFW/include"
IncludeDir["glad"] = "thirdparty/glad/include"
IncludeDir["ImGui"] = "thirdparty/imgui"
IncludeDir["glm"] = "thirdparty/glm"

group "Dependencies"
	include "thirdparty/GLFW"
	include "thirdparty/glad"
	include "thirdparty/imgui"
group ""

project "Heirloom"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "hlpch.h"
	pchsource "src/hlpch.cpp"
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	files
	{
		"include/**.h",
		"src/**.h",
		"src/**.cpp"
	}
	
	includedirs
	{
		"src",
		"thirdparty/spdlog/include",
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