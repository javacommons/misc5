#! bash -uv
g++ -std=c++17 -DwxOVERRIDE="override" -I /mingw32/include/wx-3.0 -I /mingw32/lib/wx/include/msw-unicode-3.0 wx01.cpp `wx-config --libs`
