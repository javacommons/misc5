#! bash -uvx
bash ../install-qt.sh
bash ../install-libs.sh
rm -rf .qmake* debug release Makefile* *_plugin_import.cpp ui_*.h
$MSYSTEM_PREFIX/qt5-static/bin/qmake *.pro
mingw32-make -f Makefile.Release all post
rm release/*.h
rm release/*.cpp
rm release/*.moc
rm release/*.o
#mkdir -p release/output
BoxedAppPackerConsole.exe temp01.bxproj | iconv -f cp932 -t utf-8
cp -p release/temp01.exe .

