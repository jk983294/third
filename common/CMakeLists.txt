file(GLOB 3rdSrcs "src/*.cpp" )
add_library(common_3rd_lib STATIC ${3rdSrcs})

install(DIRECTORY include/ DESTINATION /opt/3rd/common/include)
install(TARGETS common_3rd_lib ARCHIVE DESTINATION /opt/3rd/common/lib/)