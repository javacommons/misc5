@echo off
call :subroutine
set PATH=%~dp0mingw64\bin;%~dp0usr\local\bin;%~dp0usr\bin;%PATH%
set MINGW_CHOST=x86_64-w64-mingw32
set MINGW_PACKAGE_PREFIX=mingw-w64-x86_64
set MINGW_PREFIX=/mingw64
set MSYSTEM_CARCH=x86_64
set MSYSTEM_CHOST=x86_64-w64-mingw32
set MSYSTEM_PREFIX=/mingw64
set MSYSTEM=MINGW64
IF not exist %~dp0home\%USERNAME% mkdir %~dp0home\%USERNAME%
goto :eof

:subroutine
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
endlocal & set PATH=%NEWPATH%
exit /b
