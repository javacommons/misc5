-- premake4.lua
solution "Hello Premake"

  configurations { "Release", "Debug" }

  project "exe1"
    -- https://github.com/premake/premake-core/wiki/kind
    kind "ConsoleApp"
    -- kind "WindowedApp"
    language "C++"
    files { "**.h", "*.c", "**.hpp", "**.cpp" }
    includedirs {
      "./base64",
      ".."
    }
    libdirs {
      ".."
    }
    links {
      "calc", "opengl32", "glu32"
    }
    linkoptions { "-static -Wl,-allow-multiple-definition" }
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }
      targetsuffix "-d"

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
