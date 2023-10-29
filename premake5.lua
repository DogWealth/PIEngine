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
	kind "SharedLib"
	language "C++"

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
		"Dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PI_PLATFORM_WINDOWS",
			"PI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations:Debug"
		defines "PI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PI_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"%{IncludeDir.glm}"
	}

	links
	{
		"PIEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PI_PLATFORM_WINDOWS",
		}


	filter "configurations:Debug"
		defines "PI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PI_DIST"
		runtime "Release"
		optimize "On"
	
