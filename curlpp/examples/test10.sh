#! bash -uvx
# ./example10.exe https://jsonplaceholder.typicode.com/users tmp.tmp
#./example10.exe https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz msys2-x86_64-latest.tar.xz

#time wget https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz
#real    8m9.083s
#user    0m1.061s
#sys     0m1.015s

#time curl --etag-compare test.etag --etag-save test.etag -o msys2-x86_64-latest.tar.xz -v https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz
#real    2m35.734s
#user    0m0.000s
#sys     0m0.015s

#time /usr/bin/curl --etag-compare test.etag --etag-save test.etag -o msys2-x86_64-latest.tar.xz -v https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz
#real    1m21.789s
#user    0m1.328s
#sys     0m1.374s

#time tar -xf msys2-x86_64-latest.tar.xz --strip-components 1

#xz -dc C:\Users\javac\my-bin\msys2-x86_64-latest.tar.xz | tar -xf -

#xz -dc C:/Users/javac/my-bin/msys2-x86_64-latest.tar.xz | tar -xf -

#mkdir -p C:\Users\javac\tmp\my-msys2
#xz.exe -dc C:/Users/javac/my-bin/msys2-x86_64-latest.tar.xz | tar.exe -xf - -C C:/Users/javac/tmp/my-msys2 --strip-components 1
