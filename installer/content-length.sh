#! bash -uvx
curl -s -L -I https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz | gawk -v IGNORECASE=1 '/^Content-Length/ { print $2 }'
