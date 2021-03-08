#! bash -uvx
if [ ! -e flutter-desktop-embedding ]; then
  git clone https://github.com/google/flutter-desktop-embedding.git
fi
cd flutter-desktop-embedding/testbed/windows
flutter run

