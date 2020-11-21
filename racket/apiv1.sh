#! bash -uvx
if [ "${MSYSTEM_CARCH}" = "i686" ]; then
  arch=x32
else
  arch=x64
fi
rm -rf obj Makefile
premake4 --file=apiv1.premake4 --platform=$arch gmake
make
