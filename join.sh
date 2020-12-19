#! bash -uvx
file=$1
rm -rf $file.tmp
cat $file.uue.* > $file.tmp
uudecode $file.tmp
rm -rf $file.tmp
