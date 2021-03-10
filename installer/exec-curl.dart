import 'dart:cli';
import 'dart:io';

import "package:path/path.dart" show dirname;
import 'dart:io' show Platform;

String get_exe_path(String fname) {
  var dir = dirname(Platform.script.toFilePath());
  return dir + "\\" + fname;
}

int call_process(String exe, List<String> args) {
  final process = waitFor<Process>(
      Process.start(exe, args, mode: ProcessStartMode.inheritStdio));
  final exitCode = waitFor<int>(process.exitCode);
  print(exitCode);
  return exitCode;
}

int call_curl() {
  var curl32 = get_exe_path("curl32.exe");
  return call_process(curl32, [
    "--etag-compare",
    "test.etag",
    "--etag-save",
    "test.etag",
    "-o",
    "msys2-x86_64-latest.tar.xz",
    "https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz"
  ]);
}

void main() async {
  print(dirname(Platform.script.toString()));
  print(Platform.script.toFilePath());
  print(dirname(Platform.script.toFilePath()));

  call_curl();
  var busybox = get_exe_path("busybox.exe");
  final myDir = Directory('my-msys2.tmp');
  var isThere = await myDir.exists();
  print(isThere ? 'exists' : 'non-existent');
  if (isThere) return;
  var directory = await myDir.create(recursive: true);
  print(directory.path);
  call_process(busybox, [
    "tar",
    "-xf",
    "msys2-x86_64-latest.tar.xz",
    "-C",
    "my-msys2.tmp",
    "--strip-components",
    "1"
  ]);
}
