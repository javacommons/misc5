import 'dart:cli';
import 'dart:io';

import "package:path/path.dart" show dirname;
import 'dart:io' show Platform;

void call_curl() {
  print(dirname(Platform.script.toString()));
  print(Platform.script.toFilePath());
  print(dirname(Platform.script.toFilePath()));

  // Execute the script
  final process = waitFor<Process>(Process.start(
      dirname(Platform.script.toFilePath()) + "\\curl64.exe",
      [
        "--etag-compare",
        "test.etag",
        "--etag-save",
        "test.etag",
        "-o",
        "msys2-x86_64-latest.tar.xz", //"users.json",
        //"-v",
        "https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz" //"https://jsonplaceholder.typicode.com/users"
      ],
      mode: ProcessStartMode.inheritStdio));

  final exitCode = waitFor<int>(process.exitCode);
  print(exitCode);
}

void main() {
  call_curl();
}
