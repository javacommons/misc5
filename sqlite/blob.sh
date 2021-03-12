#! bash -uvx
rm -f *.sqlite
g++ blob.cpp -lsqlite3 -o blob && ./blob.exe
sqlite3 blob.sqlite -batch -cmd ".dump users" ".exit"
