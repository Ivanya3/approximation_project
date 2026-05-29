cmake_minimum_required(VERSION 3.16)

project(test5 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    graf.cpp
    graf.h

    slidervv.cpp
    slidervv.h

    statswindow.cpp
    statswindow.h
    StatsWindow.ui

    resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(test5
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        csvimporter.h csvimporter.cpp
    )
else()
    if(ANDROID)
        add_library(test5 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(test5
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(test5 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(test5 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.test5)
endif()

set_target_properties(test5 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS test5
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(test5)
endif()
