workspace "PIEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PI_PLATFORM_WINDOWS",
			"PI_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations:Debug"
		defines "PI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PI_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PI_DIST"
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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PIEngine/vendor/spdlog/include",
		"PIEngine/src"
	}

	links
	{
		"PIEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PI_PLATFORM_WINDOWS",
		}


	filter "configurations:Debug"
		defines "PI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PI_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PI_DIST"
	
