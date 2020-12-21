#! bash -uvx
PACKAGE_PREFIX="${MINGW_PACKAGE_PREFIX:-mingw-w64-x86_64}"
echo $PACKAGE_PREFIX
pacman -S --needed --noconfirm \
    subversion \
	wget \
	$PACKAGE_PREFIX-python \
	$PACKAGE_PREFIX-boost \
	$PACKAGE_PREFIX-fltk \
	$PACKAGE_PREFIX-libarchive \
	$PACKAGE_PREFIX-postgresql \
	$PACKAGE_PREFIX-sqlite3 \
	$PACKAGE_PREFIX-zeromq
rm -rf nostd
mkdir nostd
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/any-lite/master/include/nonstd/any.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/byte-lite/master/include/nonstd/byte.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/expected-lite/master/include/nonstd/expected.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/observer-ptr-lite/master/include/nonstd/observer_ptr.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/optional-lite/master/include/nonstd/optional.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/ring-span-lite/master/include/nonstd/ring.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/ring-span-lite/master/include/nonstd/ring_span.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/span-lite/master/include/nonstd/span.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/status-value-lite/master/include/nonstd/status_value.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/status-value-lite/master/include/nonstd/status_value_cpp98.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/string-view-lite/master/include/nonstd/string_view.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/value-ptr-lite/master/include/nonstd/value_ptr.hpp)
(cd nostd && wget https://raw.githubusercontent.com/martinmoene/variant-lite/master/include/nonstd/variant.hpp)
rm -rf $MINGW_PREFIX/include/nostd
cp -rp nostd $MINGW_PREFIX/include/
