cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

project(simple_notes)

find_package(SQLite3 REQUIRED)

add_executable(SimpleNotes src/main.cpp src/database.h src/database.cpp)

target_link_libraries(SimpleNotes PRIVATE SQLite::SQLite3)
