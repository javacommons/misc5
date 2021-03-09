#! bash -uvx
rm -rf main01.exe ./nimcache
nim cpp -r --nimcache:./nimcache main01.nim
