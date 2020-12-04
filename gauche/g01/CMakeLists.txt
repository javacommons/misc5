cmake_minimum_required(VERSION 3.5)

project(g01 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

execute_process(COMMAND CMD /c gauche-config -I OUTPUT_VARIABLE G_INCLUDE)

#find_package(Qt5Core)
#find_package(QtNetwork)
find_package(Qt5 5.15 REQUIRED Core Network)

add_executable(g01
  main.cpp
)
target_link_libraries(g01 Qt5::Core Qt5::Network)
