workspace "MyOpenGL"
    startproject "Jonesin"
    outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    architecture "x64"
    configurations {"Debug", "Release"}
    filter "system:windows"
        buildoptions { "/utf-8" }
    filter {}

    IncludeDir = {}
    IncludeDir["Glad"]= "Jonesin/vendor/glad/include"
    IncludeDir["glm"]="Jonesin/vendor/glm"

project "Jonesin"
    location "Jonesin"
    language "C++"
    kind "ConsoleApp"
    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")
    
    pchheader "pch.h"
    pchsource "Jonesin/src/pch/pch.cpp"
    
    files{
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/glad/src/**.c",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h"
    }
    
    includedirs{
        "%{prj.name}/Dependencies/glfw-3.4.bin.WIN64/include",
        "%{prj.name}/vendor",
        "%{prj.name}/src",
        "%{prj.name}/src/Engine",
        "%{prj.name}/src/Engine/Renderer",
        "%{prj.name}/src/Engine/Renderer/OpenGL",
        "%{prj.name}/src/Engine/Event",
        "%{prj.name}/src/pch",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
    }
    
    libdirs{
        "%{prj.name}/Dependencies/glfw-3.4.bin.WIN64/lib-vc2022"
    }
    
    links{
        "opengl32.lib",
        "glfw3.lib"
    }

    filter "files:**/glad.c"
        enablepch "Off"
    filter {}

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"
        defines{
            "GLFW_INCLUDE_NONE"
        }
    filter {}
    
    filter "configurations:Debug"
        defines "JO_DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "JO_RELEASE"
        runtime "Release"
        optimize "On"
    filter{}

project "SandBox"
    kind "StaticLib"
    location "SandBox"
    language "C++"
    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")
    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs{
        "Jonesin/vendor",
        "Jonesin/src/Engine",
        "Jonesin/vendor/glm"
    }
    dependson { "Jonesin" }
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off" -- 保持两边一致
        systemversion "latest"
        defines{ "JO_PLATFORM_WINDOWS" }
    filter "configurations:Debug"
        defines "JO_DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "JO_RELEASE"
        runtime "Release"
        optimize "On"
    filter{}