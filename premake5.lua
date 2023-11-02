workspace "PIEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "PIEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "PIEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "PIEngine/vendor/imgui"
IncludeDir["glm"] = "PIEngine/vendor/glm"

include "PIEngine/vendor/GLFW"
include "PIEngine/vendor/Glad"
include "PIEngine/vendor/imgui"

project "PIEngine"
	location "PIEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir("bin/" ..outputdir .. "/%{prj.name}")
	objdir("bin-int/" ..outputdir .. "/%{prj.name}")

	pchheader "pipch.h"
	pchsource "PIEngine/src/pipch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PI_PLATFORM_WINDOWS",
			"PI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "PI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PI_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" ..outputdir .. "/%{prj.name}")
	objdir("bin-int/" ..outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"PIEngine/vendor/spdlog/include",
		"PIEngine/src",
		"PIEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"PIEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PI_PLATFORM_WINDOWS",
		}


	filter "configurations:Debug"
		defines "PI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PI_DIST"
		runtime "Release"
		optimize "on"
	