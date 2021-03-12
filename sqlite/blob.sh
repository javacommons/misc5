#! bash -uvx
g++ blob.cpp -lsqlite3 -o blob && ./blob.exe
sqlite3 blob.sqlite -batch -cmd ".dump" ".exit"
