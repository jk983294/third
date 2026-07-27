cmake_minimum_required(VERSION 3.5)

project(third)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3 -Wall -Werror")
#set(CMAKE_CXX_FLAGS "-std=c++20 -g -Wall -Werror")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

include_directories(SYSTEM common/include)
include_directories(SYSTEM alglib/include)
include_directories(SYSTEM /opt/3rd/ortools/include/)

add_subdirectory(common)
add_subdirectory(example)
add_subdirectory(alglib)

install(DIRECTORY interface/ DESTINATION /opt/3rd/interface)
install(DIRECTORY Eigen/ DESTINATION /opt/3rd/Eigen/Eigen)
install(DIRECTORY gcem/ DESTINATION /opt/3rd/gcem)
install(DIRECTORY stats/ DESTINATION /opt/3rd/stats)
