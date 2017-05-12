cmake_minimum_required(VERSION 2.8)

project(vcf)
find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::DBus)
