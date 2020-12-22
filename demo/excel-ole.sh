#! bash -uvx
g++ -o excel-ole.exe excel-ole.cpp -lole32 -l oleaut32 -luuid && ./excel-ole.exe
