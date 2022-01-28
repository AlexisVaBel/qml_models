file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

#set(CORE_MODULES somedirs)
foreach(X ${CORE_MODULES})
    file(GLOB ${X}_SOURCES "${X}/*.cpp")
    file(GLOB ${X}_HEADERS "${X}/*.h")
    list(APPEND SOURCES ${${X}_SOURCES})
    list(APPEND HEADERS ${${X}_HEADERS})
    add_module("${CMAKE_CURRENT_SOURCE_DIR}/${X}")
endforeach()

add_library(core STATIC ${SOURCES} ${HEADERS})
target_link_libraries(core PUBLIC Qt5::Core)
