workspace "Saturn"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Saturn/vendor/GLFW/include"
IncludeDir["Glad"] = "Saturn/vendor/Glad/include"
IncludeDir["ImGui"] = "Saturn/vendor/imgui"
IncludeDir["glm"] = "Saturn/vendor/glm"
IncludeDir["stb"] = "Saturn/vendor/stb"

group "Dependencies"
    include "Saturn/vendor/GLFW"
    include "Saturn/vendor/Glad"
    include "Saturn/vendor/imgui"
group ""

project "Saturn"
    location "Saturn"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "saturnpch.h"
    pchsource "Saturn/src/saturnpch.cpp"
    
    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb/stb_image.h",
        "%{prj.name}/vendor/stb/stb_image.cpp",
        "%{prj.name}/src/**.cc",
        "%{prj.name}/src/**.c"
    }

    includedirs
    {
        "Saturn/vendor/spdlog/include",
        "Saturn/src",
        "Saturn/vendor/GLFW/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}/backends",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "ST_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "ST_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "ST_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Saturn/src",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "Saturn"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "ST_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "ST_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "ST_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "ST_DIST"
        runtime "Release"
        optimize "On"