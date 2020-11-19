#! bash -uvx
bash ../install-qt.sh
bash ../install-libs.sh
rm -rf .qmake* debug release Makefile* *_plugin_import.cpp ui_*.h
#qmake *.pro
$MSYSTEM_PREFIX/qt5-static/bin/qmake *.pro
mingw32-make -f Makefile.Release
for i in release/*.a; do
  if [ -f "$i" ]; then cp -p "$i" .; fi
done
for i in release/*.dll; do
  if [ -f "$i" ]; then cp -p "$i" .; fi
done
for i in release/*.exe; do
  if [ -f "$i" ]; then cp -p "$i" .; fi
done
