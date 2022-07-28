--how the solution file will be named
workspace "Sycamore"
    architecture "x86"
    configurations {"Debug", "Release"}

    --setting up the startup project (only in visual studio)
    startproject "Sycamore"

--cool macros for output file
outputdir = "%{cfg.system}/%{cfg.buildcfg}-%{cfg.architecture}"

    files{
        "Sycamore/EntryPoint.cpp",
        "Sycamore/Sycamore.h"
    }


--check for the premake5.lua file in the given path
--and executes the program
include "Sycamore"

