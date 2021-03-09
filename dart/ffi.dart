import 'dart:ffi'; // For FFI

final DynamicLibrary nativeAddLib = DynamicLibrary.open("libnative_add.dll");

final int Function(int x, int y) nativeAdd = nativeAddLib
    .lookup<NativeFunction<Int32 Function(Int32, Int32)>>("native_add")
    .asFunction();

void main() {
  print(nativeAdd(11, 22));
}
