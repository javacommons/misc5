#! bash -uvx
file=$1
rm -rf $file.tmp
uuencode -m $file $file > $file.tmp
split -b 80m $file.tmp $file.uue.
rm -rf $file.tmp
