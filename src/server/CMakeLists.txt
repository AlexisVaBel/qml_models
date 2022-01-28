set(SOURCES)
set(HEADERS)

set(SERVER_MODULES
        tcp
        )

foreach (X ${SERVER_MODULES})
    file(GLOB ${X}_SOURCES "${X}/*.cpp")
    file(GLOB ${X}_HEADERS "${X}/*.h")
    list(APPEND SOURCES ${${X}_SOURCES})
    list(APPEND HEADERS ${${X}_HEADERS})
    add_module("${CMAKE_CURRENT_SOURCE_DIR}/${X}")
endforeach ()

list(APPEND SOURCES "Server.cpp")
list(APPEND HEADERS "Server.h")

add_library(server STATIC ${SOURCES} ${HEADERS})

target_link_libraries(server PUBLIC Qt5::Core)
#translation
#target_link_libraries(server PUBLIC i18n)
