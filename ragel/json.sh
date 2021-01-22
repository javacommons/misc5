    1  pacman -S git
    2  git clone https://github.com/javacommons/misc5
    3  cd misc5/racket/
    4  init-git.sh 
    5  exit
    6  inst-emacs.sh 
    7  emacs lesson.rkt &
    8  exit
    9  find /
   10  exit
   11  find .
   12  exit
   13  cat ~/.git-credentials 
   14  exit
   15  find .
   16  exit
   17  find /
   18  exit
   19  find /
   20  exit
   21  find /
   22  exit
   23  mv misc5/ misc5.old
   24  git clone https://github.com/javacommons/misc5
   25  rm -rf misc5.old/
   26  exit
   27  g++
   28  cd ..
   29  inst-gcc.sh 
   30  cd gauche/
   31  ls
   32  mk main
   33  ls
   34  mkdir build.tmp
   35  cd build.tmp/
   36  ls
   37  git clone https://github.com/shirok/Gauche
   38  cd Gauche/
   39  ls
   40  vi install-sh 
   41  vim install-sh 
   42  ls
   43  autoconfig
   44  pacman -Ss autoconfig
   45  pacman -Ss config
   46  pacman -Ss autoconf
   47  pacman -Fl autoconf
   48  pacman -Fy
   49  pacman -Fl autoconf
   50  ls
   51  pacman -S --noconfigm autoconf
   52  pacman -S --noconfirm autoconf
   53  autoconf
   54  ls -ltr
   55  ./configure
   56  exit
   57  cd misc
   58  exit
   59  inst-emacs.sh 
   60  inst-gcc.sh 
   61  inst-libs.sh 
   62  inst-emacs.sh 
   63  inst-gcc.sh 
   64  inst-libs.sh 
   65  exit
   66  inst-emacs.sh 
   67  inst-gcc.sh 
   68  inst-libs.sh 
   69  exit
   70  git pull
   71  inst-libs.sh 
   72  exit
   73  git pull
   74  cd ../strconv/
   75  git pull
   76  head strconv.h 
   77  cd ../misc5/
   78  ls
   79  code strconv.h 
   80  cd demo
   81  strconv.sh 
   82  strconv.sh 
   83  strconv-32bit.exe 
   84  strconv.sh 
   85  strconv-32bit.exe 
   86  inst-my
   87  cd ..
   88  inst-my-headers.sh 
   89  cd ../strconv/
   90  cp ../misc5/strconv.h .
   91  git diff
   92  git commit -m"void format(std::ostream& ostrm, const wchar_t *format, ...) に変更"
   93  git add .
   94  git commit -m"void format(std::ostream& ostrm, const wchar_t *format, ...) に変更"
   95  git push
   96  exit
   97  cd demo
   98  strconv-32bit.exe 
   99  strconv-32bit.exe 
  100  exit
  101  cd demo
  102  strconv-32bit.exe 
  103  git status
  104  cd ..
  105  git diff strconv.h 
  106  git diff demo/strconv.cpp 
  107  git add .
  108  git status
  109  git commit -m.
  110  git push
  111  git pull
  112  exit
  113  pacman -Ss graphviz
  114  ls inst-*
  115  cp inst-emacs.sh inst-ragel.sh
  116  code inst-ragel.sh 
  117  inst-ragel.sh 
  118  which graphviz
  119  which ragel
  120  ragel -v
  121  code ex1.rl
  122  ragel -Vp ex1.rl > ex1.dot
  123  ragel -Vp ex1.rl > ex1.dot
  124  ragel -Vp ex1.rl > ex1.dot
  125  ragel -R ex1.rl
  126  mv ex1.rl json.rl
  127  ragel -Z json.rl
  128  ls -ltr
  129  code json.go
  130  ragel -Vp json.rl > json.dot
  131  dot -Tpng json.dot > json.png
  132  start json.png
  133  mkdir ragel
  134  cd ragel
  135  mv ../json.* .
  136  ls
  137  vi .gitignore
  138  code .git ignore
  139  code .gitignore
  140  history > json.sh
