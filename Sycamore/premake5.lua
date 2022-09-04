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

        "Math/src/**.h",
        "Math/src/**.cpp",
        "Math/SM_math.h",

        "src/Assets/Images/**.jpg",
        "src/Assets/Images/**.png",
        "src/Assets/Shaders/**.shader",

        "vendor/STBI_IMAGE/*.cpp",
        "vendor/STBI_IMAGE/*.h",

        "vendor/ImGui/include/imgui/**.h",
        "vendor/ImGui/lib/**.cpp",

        "vendor/yaml-cpp/src/**.h",
        "vendor/yaml-cpp/src/**.cpp",
        "vendor/yaml-cpp/include/**.h"
    }

    includedirs{
        "vendor/spdlog/include",
        "vendor/GLFW32/include",
        "vendor/GLEW/include",
        "vendor/ImGui/include",
        "vendor/yaml-cpp/include"
    }

    libdirs{
        "vendor/GLFW32/lib-vc2022",
        "vendor/GLEW/lib/Release/Win32"
    }

    defines{
        "GLEW_STATIC"
    }

    links {"glfw3.lib", "opengl32.lib", "glew32s.lib"}

    filter "system:windows"
        systemversion "latest"

        defines{
            "SM_WINDOWS"
        }



    filter "configurations:Debug"
        defines "SM_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SM_RELEASE"
        optimize "On"