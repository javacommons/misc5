import 'dart:async';
import 'dart:cli';
import 'dart:io';

void call_curl() {
  // Execute the script
  final process = waitFor<Process>(Process.start(
      "./curl64.exe",
      [
        "--etag-compare",
        "test.etag",
        "--etag-save",
        "test.etag",
        "-o",
        "msys2-x86_64-latest.tar.xz", //"users.json",
        "-v",
        "https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz" //"https://jsonplaceholder.typicode.com/users"
      ],
      mode: ProcessStartMode.inheritStdio));

  final exitCode = waitFor<int>(process.exitCode);
}

void main() {
  call_curl();
}
