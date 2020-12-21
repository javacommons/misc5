@echo off
setlocal enabledelayedexpansion
rem echo %cd%
set pwd=%cd%
set pwd=%pwd:\=/%
set MSYSTEM=MINGW32
"%~dp0usr\bin\bash.exe" -l -c "cd `cygpath %pwd%`; exec bash"
endlocal
