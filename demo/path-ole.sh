#! bash -uvx
g++ -Wall -o path-ole.exe path-ole.cpp -lole32 -l oleaut32 -luuid && ./path-ole.exe
