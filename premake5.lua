workspace "Saturn"
    architecture "x64"
    startproject "Saturn-Editor"

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
IncludeDir["entt"] = "Saturn/vendor/entt/include"
IncludeDir["yaml"] = "Saturn/vendor/yaml/include"
IncludeDir["ImGuizmo"] = "Saturn/vendor/ImGuizmo"

group "Dependencies"
    include "Saturn/vendor/GLFW"
    include "Saturn/vendor/Glad"
    include "Saturn/vendor/imgui"
    include "Saturn/vendor/yaml"
group ""

project "Saturn"
    location "Saturn"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "SaturnPch.h"
    pchsource "Saturn/src/SaturnPch.cpp"
    
    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb/stb_image.h",
        "%{prj.name}/vendor/stb/stb_image.cpp",
        "%{prj.name}/src/**.cc",
        "%{prj.name}/src/**.c",
        "Saturn/vendor/ImGuizmo/ImGuizmo.h",
        "Saturn/vendor/ImGuizmo/ImGuizmo.cpp",
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
        "%{IncludeDir.stb}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml}",
        "%{IncludeDir.ImGuizmo}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "yaml-cpp",
        "opengl32.lib"
    }

    filter "files:Saturn/vendor/ImGuizmo/**.cpp"
        flags { "NoPCH" }

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
        "Saturn/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml}"
    }

    links
    {
        "Saturn",
        "yaml-cpp"
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


project "Saturn-Editor"
        location "Saturn-Editor"
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
            "Saturn/vendor",
            "%{IncludeDir.glm}",
            "%{IncludeDir.ImGui}",
            "%{IncludeDir.entt}",
            "%{IncludeDir.yaml}"
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