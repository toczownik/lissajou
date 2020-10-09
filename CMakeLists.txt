cmake_minimum_required(VERSION 3.17)
project(lissajou)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

set(project_headers mainwindow.h)

set(project_sources mainwindow.cpp)

add_executable(lissajou main.cpp ${project_headers} ${project_sources})

target_link_libraries(lissajou Qt5::Widgets)