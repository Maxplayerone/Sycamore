project "Sycamore"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++17"
    --this thingy doesn't do anything
    staticruntime "default"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "src/**.h",
        "src/**.cpp",
        "src/Assets/Images/**.jpg",
        "src/Assets/Images/**.png",
        "src/Assets/Shaders/**.shader",
        "vendor/ImGui/**.h",
        "vendor/ImGui/**.cpp",
        "vendor/STBI_IMAGE/*.cpp",
        "vendor/STBI_IMAGE/*.h"
    }

    

    filter "system:windows"
        systemversion "latest"

        includedirs{
            "vendor/spdlog/include",
            "vendor/GLM"
        }

        filter {"system:windows", "architecture:x86"}
            defines {
              "SM_WINDOWS",
              "GLEW_STATIC"
           }

           --linker/input in vs
           --links the needed libraries
           links {"glfw3.lib", "opengl32.lib", "glew32s.lib"}

           libdirs{
            "vendor/GLFW32/lib-vc2022",
            "vendor/GLEW/lib/Release/Win32"
           }

            includedirs{
            "vendor/GLFW32/include",
            "vendor/GLEW/include"
            }

        filter "configurations:Debug"
            defines "SM_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "SM_RELEASE"
            optimize "On"