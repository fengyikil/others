cmake_minimum_required(VERSION 2.8)
project(c_call_lua)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#lua 头文件
include_directories(./lib/lua-5.3.4/src)
add_subdirectory(lib/lua-5.3.4)
#lua 拓展库
aux_source_directory(. LIB_SRC)

add_executable(t_c_lua ${LIB_SRC})
TARGET_LINK_LIBRARIES(t_c_lua liblua_static)
