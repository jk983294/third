file(GLOB algSrcs "*.cpp" )
add_library(alg_lib SHARED ${algSrcs})
# alglib is third-party code; do not treat its warnings as errors
# (inherited from the project-wide -Werror).
target_compile_options(alg_lib PRIVATE -Wno-error)
set_property(TARGET alg_lib PROPERTY POSITION_INDEPENDENT_CODE ON)
install(TARGETS alg_lib LIBRARY DESTINATION /opt/3rd/alglib/lib/)