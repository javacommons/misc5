-- premake4.lua
solution "Hello Premake"

  configurations { "Release", "Debug" }

  project "fltk1"
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
      "fltk",
      "fltk_forms",
      "fltk_gl",
      "fltk_images",
      "gdi32",
      "ole32", "uuid", "comctl32",
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
