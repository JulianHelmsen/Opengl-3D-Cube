
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
		"thirdparty/GLFW/include",
		"thirdparty/GLEW/include",
		"thirdparty/glm"
	}
	libdirs {
		"thirdparty/GLFW/lib-vc2022",
		"thirdparty/GLEW/lib/Release/x64"
	}

	links {
		"glfw3.lib",
		"Opengl32",
		"glew32s"
	}

	defines { "GLEW_STATIC" }

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"RELEASE", "NDEBUG" }
		optimize "On"
		staticruntime "Off"
