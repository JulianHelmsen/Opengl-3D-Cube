
workspace "3D-Cube"
	configurations { "Debug", "Release" }

project "3D-Cube"
	kind "ConsoleApp"
	language "C++"
	location "3d-cube"
	targetdir "bin/%{cfg.buildcfg}"


	files {
		"3d-cube/src/**.cpp",
		"3d-cube/src/**.h",
		"3d-cube/src/**.hpp"
	}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"RELEASE", "NDEBUG" }
		optimize "On"
		staticruntime "Off"
