#! bash -uvx
raco exe --gui -o racket-7.9-64bit.exe racket-7.9-64bit.rkt
raco distribute inst.tmp/ racket-7.9-64bit.exe
