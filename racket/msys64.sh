#! bash -uvx
raco exe --gui -o msys64-my-setup.exe msys64.rkt
raco distribute inst.tmp msys64-my-setup.exe
cp msys64.zip inst.tmp
cp .emacs inst.tmp
cp c-quick-2.el inst.tmp
