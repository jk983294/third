FIND_LIBRARY(ORTOOL_LIB libortools.so HINTS /opt/3rd/ortools/lib/ REQUIRED)

file( GLOB APP_SOURCES "*.cpp")
foreach( sourcefile ${APP_SOURCES} )
    # executable name cut off .cpp
    string( REGEX REPLACE ".+/" "" executablename1 ${sourcefile} )
    string( REPLACE ".cpp" "" executablename ${executablename1} )

    message ("source files: " ${sourcefile} " executable: " ${executablename})
    add_executable( ${executablename} ${sourcefile} )
    target_link_libraries( ${executablename} ${ORTOOL_LIB} pthread rt )
endforeach( sourcefile ${APP_SOURCES} )



