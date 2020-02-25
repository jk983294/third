file(GLOB algSrcs "*.cpp" )
add_library(alg_lib STATIC ${algSrcs})

install(TARGETS alg_lib ARCHIVE DESTINATION /opt/3rd/alglib/lib/)