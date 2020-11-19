-- premake4.lua
solution "exe1"
  -- configurations { "Debug", "Release" }
  -- configurations { "Release" }
  configurations { "Release", "Debug" }

   -- A project defines one build target
   project "exe1"
      -- https://github.com/premake/premake-core/wiki/kind
      kind "ConsoleApp"
      -- kind "WindowedApp"
      language "C++"
      files { "**.h", "*.c", "**.hpp", "**.cpp" }

      includedirs {
        -- "/usr/include/opengl"
      }
      libdirs {
        -- "/usr/lib/w32api"
      }
      links {
        "opengl32", "glu32"
      }

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
         targetsuffix "-d"

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
