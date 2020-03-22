file(GLOB algSrcs "*.cpp" )
add_library(alg_lib SHARED ${algSrcs})
set_property(TARGET alg_lib PROPERTY POSITION_INDEPENDENT_CODE ON)
install(TARGETS alg_lib LIBRARY DESTINATION /opt/3rd/alglib/lib/)