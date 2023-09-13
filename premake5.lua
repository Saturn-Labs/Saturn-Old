workspace "Saturn"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Saturn/vendor/GLFW/include"

include "Saturn/vendor/GLFW"

project "Saturn"
    location "Saturn"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "saturnpch.h"
    pchsource "Saturn/src/saturnpch.cpp"
    
    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.cc",
        "%{prj.name}/src/**.c"
    }

    includedirs
    {
        "Saturn/vendor/spdlog/include",
        "Saturn/src",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_WINDOWS",
            "ST_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "ST_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ST_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ST_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.cc",
        "%{prj.name}/src/**.c"
    }

    includedirs
    {
        "Saturn/vendor/spdlog/include",
        "Saturn/src"
    }

    links
    {
        "Saturn"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "ST_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ST_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ST_DIST"
        optimize "On"