project "Sycamore"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "src/**.h",
        "src/**.cpp"
    }

    includedirs{
        "vendor/spdlog/include"
    }

    filter "system:windows"
        systemversion "latest"

        filter "configurations:Debug"
            defines "SM_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "SM_RELEASE"
            optimize "On"