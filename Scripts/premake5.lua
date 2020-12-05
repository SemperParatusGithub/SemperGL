 workspace "SemperGL"
	architecture "x64"

	startproject "SampleApp"

	configurations { "Debug", "Release", "Distribute" }
	flags { "MultiProcessorCompile" }

 outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 group "Dependencies"
	include "SemperGL/vendor/GLFW"
	include "SemperGL/vendor/Glad"
	include "SemperGL/vendor/imgui"
 group ""

project "SemperGL"

	location "SemperGL"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
 		"SemperGL/src/**.h",
		"SemperGL/src/**.cpp",
		"SemperGL/vendor/stb_image/**.h",
		"SemperGL/vendor/stb_image/**.cpp",
		"SemperGL/vendor/glm/glm/**.hpp",
		"SemperGL/vendor/glm/glm/**.inl"
	}
	includedirs { 
		"SemperGL/src",
		"SemperGL/vendor/GLFW/include",
		"SemperGL/vendor/Glad/include",
		"SemperGL/vendor/imgui",
		"SemperGL/vendor/glm",
		"SemperGL/vendor/stb_image"
	}

	links { "GLFW", "Glad", "ImGui", "opengl32.lib" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

	filter "configurations:Distribute"
		optimize "On"
		defines { "SGL_DISTRIBUTE" }

 group "Projects"
project "SampleApp"
	location "Projects/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
 		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"SemperGL/src",
		"SemperGL/include",
		"SemperGL/vendor/GLFW/include",
		"SemperGL/vendor/Glad/include",
		"SemperGL/vendor/imgui",
		"SemperGL/vendor/glm",
		"SemperGL/vendor/stb_image"
	}

	links { "SemperGL", "GLFW", "Glad", "ImGui", "opengl32.lib" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines { "SGL_DEBUG" }

	filter "configurations:Release"
		optimize "On"
		defines { "SGL_RELEASE" }

	filter "configurations:Distribute"
		optimize "On"
		defines { "SGL_DISTRIBUTE" }

project "Snake"
	location "Projects/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
 		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"SemperGL/src",
		"SemperGL/include",
		"SemperGL/vendor/GLFW/include",
		"SemperGL/vendor/Glad/include",
		"SemperGL/vendor/imgui",
		"SemperGL/vendor/glm",
		"SemperGL/vendor/stb_image"
	}

	links { "SemperGL", "GLFW", "Glad", "ImGui", "opengl32.lib" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines { "SGL_DEBUG" }

	filter "configurations:Release"
		optimize "On"
		defines { "SGL_RELEASE" }

	filter "configurations:Distribute"
		optimize "On"
		defines { "SGL_DISTRIBUTE" }

project "ShipGame"
	location "Projects/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
 		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"SemperGL/src",
		"SemperGL/include",
		"SemperGL/vendor/GLFW/include",
		"SemperGL/vendor/Glad/include",
		"SemperGL/vendor/imgui",
		"SemperGL/vendor/glm",
		"SemperGL/vendor/stb_image"
	}

	links { "SemperGL", "GLFW", "Glad", "ImGui", "opengl32.lib" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines { "SGL_DEBUG" }

	filter "configurations:Release"
		optimize "On"
		defines { "SGL_RELEASE" }

	filter "configurations:Distribute"
		optimize "On"
		defines { "SGL_DISTRIBUTE" }

project "Particles"
	location "Projects/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
 		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"SemperGL/src",
		"SemperGL/include",
		"SemperGL/vendor/GLFW/include",
		"SemperGL/vendor/Glad/include",
		"SemperGL/vendor/imgui",
		"SemperGL/vendor/glm",
		"SemperGL/vendor/stb_image"
	}

	links { "SemperGL", "GLFW", "Glad", "ImGui", "opengl32.lib" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines { "SGL_DEBUG" }

	filter "configurations:Release"
		optimize "On"
		defines { "SGL_RELEASE" }

	filter "configurations:Distribute"
		optimize "On"
		defines { "SGL_DISTRIBUTE" }
	
project "Mandelbrot"
	location "Projects/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
 		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.cpp"
	}
	includedirs { 
		"SemperGL/src",
		"SemperGL/include",
		"SemperGL/vendor/GLFW/include",
		"SemperGL/vendor/Glad/include",
		"SemperGL/vendor/imgui",
		"SemperGL/vendor/glm",
		"SemperGL/vendor/stb_image"
	}

	links { "SemperGL", "GLFW", "Glad", "ImGui", "opengl32.lib" }
	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
		defines { "SGL_DEBUG" }

	filter "configurations:Release"
		optimize "On"
		defines { "SGL_RELEASE" }

	filter "configurations:Distribute"
		optimize "On"
		defines { "SGL_DISTRIBUTE" }
 group ""