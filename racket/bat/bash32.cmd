@echo OFF
setlocal enabledelayedexpansion
set NEWPATH=
for %%A in ("%PATH:;=";"%") do (
  if /i "%%~A" neq "%~dp0mingw32\bin" (
    if /i "%%~A" neq "%~dp0mingw64\bin" (
      if /i "%%~A" neq "%~dp0usr\local\bin" (
        if /i "%%~A" neq "%~dp0usr\bin" (
          rem echo %%~A
          if "!NEWPATH!" equ "" (set NEWPATH=%%~A) else (set NEWPATH=!NEWPATH!;%%~A)
        )
      )
    )
  )
)
set PATH=%~dp0mingw32\bin;%~dp0usr\local\bin;%~dp0usr\bin;%NEWPATH%
set NEWPATH=
set HOME=%~dp0home\%USERNAME%
IF NOT EXIST %HOME% mkdir %HOME%
set MINGW_CHOST=i686-w64-mingw32
set MINGW_PACKAGE_PREFIX=mingw-w64-i686
set MINGW_PREFIX=/mingw32
set MSYSTEM_CARCH=i686
set MSYSTEM_CHOST=i686-w64-mingw32
set MSYSTEM_PREFIX=/mingw32
set MSYSTEM=MINGW32
%~dp0usr\bin\bash.exe
endlocal