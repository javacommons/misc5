-- premake4.lua
solution "Hello Premake"

  configurations { "Release", "Debug" }

  project "calc"
    -- https://github.com/premake/premake-core/wiki/kind
    kind "SharedLib"
    -- kind "ConsoleApp"
    -- kind "WindowedApp"
    language "C++"
    files { "**.h", "*.c", "**.hpp", "**.cpp" }
    includedirs {
      "./base64"
    }
    libdirs {
    }
    links {
      "opengl32", "glu32"
    }
    linkoptions { "-static" }
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }
      targetsuffix "-d"

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
