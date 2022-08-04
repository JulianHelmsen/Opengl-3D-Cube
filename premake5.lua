
workspace "3D-Cube"
	configurations { "Debug", "Release" }
	architecture "x86_64"

project "3D-Cube"
	kind "ConsoleApp"
	language "C++"
	location "3d-cube"
	targetdir "bin/%{cfg.buildcfg}"
	cppdialect "C++17"


	files {
		"3d-cube/src/**.cpp",
		"3d-cube/src/**.h",
		"3d-cube/src/**.hpp"
	}

	includedirs {
		"thirdparty/GLFW/include"
	}
	libdirs {
		"thirdparty/GLFW/lib-vc2022"
	}

	links {
		"glfw3.lib"
	}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"RELEASE", "NDEBUG" }
		optimize "On"
		staticruntime "Off"
