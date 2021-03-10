import "package:path/path.dart" show dirname;
import 'dart:io' show Platform;

main() {
  print(dirname(Platform.script.toString()));
  print(Platform.script.toFilePath());
  print(dirname(Platform.script.toFilePath()));
}
