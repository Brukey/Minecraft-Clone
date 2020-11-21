workspace "Minecraft"
	architecture ("x86_64")
	systemversion "latest"
	configurations {"DEBUG", "RELEASE"}
	platforms {"WINDOWS"}


project "Engine"
	kind "StaticLib"
	location "Engine"
	cppdialect "C++17"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files {
		"Engine/src/**.cpp",
		"Engine/src/**.h"
	}	

	includedirs {
		"external libraries/stb",
		"external libraries/glm",
		"external libraries/GLEW/include",
		"external libraries/GLFW/include",
		"Engine/src/"
	}

	libdirs {
		"external libraries/GLEW/lib/Release/x64",
		"external libraries/GLFW/lib-vc2017"
	}
	links {
		"glfw3.lib",
		"Opengl32",
		"glew32s"
	}

	defines {"GLEW_STATIC", "ENGINE_BUILD"}
	
	filter "platforms:WINDOWS"
		defines {"WINDOWS"}

	filter "configurations:DEBUG"
		defines {"DEBUG"}
		symbols "On"
		runtime "Debug"

	filter "configurations:RELEASE"
		defines {"RELEASE", "NDEBUG"}
		optimize "On"
		runtime "Release"


project "Minecraft"
	kind "ConsoleApp"
	location "Minecraft"
	cppdialect "C++17"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files {
		"Minecraft/src/**.cpp",
		"Minecraft/src/**.h",
	}	

	includedirs {
		"external libraries/glm",
		"Engine/src/",
	}

	links {
		"Engine"
	}
	
	filter "platforms:WINDOWS"
		defines {"WINDOWS"}

	filter "configurations:DEBUG"
		defines {"DEBUG"}
		symbols "On"
		runtime "Debug"

	filter "configurations:RELEASE"
		defines {"RELEASE", "NDEBUG"}
		optimize "On"
		runtime "Release"

	
