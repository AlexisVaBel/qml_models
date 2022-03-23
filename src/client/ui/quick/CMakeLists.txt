#stolen idea and code from QANAVA - thanks guys
set(quick_source_files
    Navigable.h
    )

set(quick_header_files
    Navigable.cpp
    )

source_group("Headers" FILES ${quick_header_files})
source_group("Sources" FILES ${quick_source_files})

set (quick_plugin_files
    ${CMAKE_CURRENT_SOURCE_DIR}/Plugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Plugin.h
)

# Configure Qt
set(CMAKE_AUTOMOC ON)
qt5_wrap_cpp(quick_source_files, quick_header_files)   # Creates .moc files from sources
set(CMAKE_AUTORCC ON)
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Debug>:QT_QML_DEBUG>)

# Configure QuickNodes library ###############################################

list(APPEND quick_resources QuickNodes_plugin.qrc)


#list(APPEND quick_resources GraphicalEffects${QT_VERSION_MAJOR}/QuickNodesGraphicalEffects.qrc)
add_library(QuickNodes STATIC ${quick_source_files} ${quick_header_files} ${quick_resources})

target_include_directories(QuickNodes
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
    )

target_compile_features(QuickNodes
    PUBLIC
        cxx_std_14
    )

install(FILES
    ${quick_header_files}
    DESTINATION include/quicknodes
    )

install(TARGETS QuickNodes
    EXPORT Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include/quicknodes
    )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
target_link_libraries(QuickNodes PUBLIC Qt5::Core Qt5::Qml Qt5::Gui Qt5::QuickControls2)


# Configure QuickNodes QML module plugin #####################################
set(PLUGIN_TARGET "quicknodeslugin")
add_library(${PLUGIN_TARGET} SHARED ${quick_plugin_files})
target_link_libraries(${PLUGIN_TARGET} QuickNodes)

# QML module deployment
set(URI QuickNodes)
string(REPLACE "." "/" TARGETPATH ${URI})
if (NOT DEFINED QT_QMAKE_EXECUTABLE)
    get_target_property (QT_QMAKE_EXECUTABLE Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
    if (NOT QT_QMAKE_EXECUTABLE)
        message(FATAL_ERROR "Cannot find qmake")
    endif()
endif()
execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_QML OUTPUT_VARIABLE QT_INSTALL_QML_RAW)
string(STRIP ${QT_INSTALL_QML_RAW} QT_INSTALL_QML)
set(DESTDIR "${QT_INSTALL_QML}/${TARGETPATH}")
install(TARGETS ${PLUGIN_TARGET} DESTINATION ${DESTDIR})

# Install qmldir file
if(QUICK_NODE_BUILD_STATIC_QRC)
    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/qmldir_static
        DESTINATION ${DESTDIR}
        RENAME qmldir
        )
else()
    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/qmldir_plugin
        DESTINATION ${DESTDIR}
        RENAME qmldir
        )
endif(QUICK_NODE_BUILD_STATIC_QRC)


# Install source QML files to ease debugging
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/	# sic! Need leading slash, otherwise it will install into subdir src
    DESTINATION ${DESTDIR}
    FILES_MATCHING PATTERN "*.qml"
    )

