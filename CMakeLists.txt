cmake_minimum_required(VERSION 3.5)

project(third)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# set(CMAKE_DEBUG_POSTFIX "-d")     # in debug mode, all lib suffix with -d

# boost lib
#find_package( Boost 1.58.0 COMPONENTS system program_options filesystem )
#include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

#SET(CXX_WARN_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast")
#SET(CXX_WARN_FLAGS "-Wall -Wshadow -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wpedantic -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -s -fno-strict-aliasing -fno-strict-overflow -Wno-maybe-uninitialized -Wno-unused-but-set-variable -Wno-unused-function -Wno-format-overflow -Wno-stringop-truncation -Wall -Werror")
#SET(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Werror -faligned-new")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

include_directories(SYSTEM common/include)
include_directories(SYSTEM alglib/include)

add_subdirectory(common)
add_subdirectory(example)
add_subdirectory(alglib)

install(DIRECTORY interface/ DESTINATION /opt/3rd/interface)
install(DIRECTORY Eigen/ DESTINATION /opt/3rd/Eigen/Eigen)
install(DIRECTORY gcem/ DESTINATION /opt/3rd/gcem)
install(DIRECTORY stats/ DESTINATION /opt/3rd/stats)
