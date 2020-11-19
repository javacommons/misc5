-- premake4.lua
solution "Hello Premake"

  configurations { "Release", "Debug" }

  project "arch"
    -- https://github.com/premake/premake-core/wiki/kind
    kind "SharedLib"
    -- kind "ConsoleApp"
    language "C++"
    files {
      "liba.cpp",
      "base64.hpp", "arch.hpp",
      "msgpack11.hpp", "msgpack11_dump.hpp", "vardecl.h",
      "base64.cpp", "arch.cpp", "msgpack11.cpp", "msgpack11_dump.cpp"
      }
    buildoptions { "-std=c++17" }
    includedirs {
      -- ".."
    }
    libdirs {
      -- ".."
    }
    links {
      "archive", "z", "bz2", "lzma", "iconv", "bcrypt", "expat", "lz4", "zstd"
    }
    linkoptions { "-static", "-Wl,-allow-multiple-definition" }
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }
      targetsuffix "-d"

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
