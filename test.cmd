set bash=..\.software\msys64\usr\bin\bash.exe
%bash% -l -c "echo `cygpath -w ~`"
for /f %%i in ('%bash% -l -c "echo `cygpath -w ~`"') do set myhome=%%i
echo %myhome%
