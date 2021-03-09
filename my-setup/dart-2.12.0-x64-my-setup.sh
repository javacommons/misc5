#! bash -uvx
rm -rf dart-2.12.0-x64-my-setup.tmp dart-2.12.0-x64-my-setup.exe
raco exe --gui -o dart-2.12.0-x64-my-setup.exe dart-2.12.0-x64-my-setup.rkt
raco distribute dart-2.12.0-x64-my-setup.tmp dart-2.12.0-x64-my-setup.exe
cp dart-2.12.0-x64.zip dart-2.12.0-x64-my-setup.tmp
