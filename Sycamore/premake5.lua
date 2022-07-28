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
        "src/**.cpp"
    }

    

    filter "system:windows"
        systemversion "latest"

        includedirs{
            "vendor/spdlog/include"
        }

        filter {"system:windows", "architecture:x86"}
            defines {
              "SM_WINDOWS"
           }

           --linker/input in vs
           --links the needed libraries
           links {"glfw3.lib", "opengl32.lib"}

           libdirs{
            "vendor/GLFW32/lib-vc2022"
           }

            includedirs{
            "vendor/GLFW32/include"
            }

        filter "configurations:Debug"
            defines "SM_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "SM_RELEASE"
            optimize "On"