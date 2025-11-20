cmake_minimum_required(VERSION 3.16)

project(SmartIncubatorOF VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort)

set(SRC_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/aboutdialog.cpp
    src/historydialog.cpp
    src/datastorage.cpp
    src/serialcomm.cpp
    src/incubatorcontroller.cpp
)

set(HEADER_FILES
    headers/mainwindow.h
    headers/aboutdialog.h
    headers/historydialog.h
    headers/datastorage.h
    headers/serialcomm.h
    headers/incubatorcontroller.h
)

set(UI_FILES
    ui/mainwindow.ui
    ui/aboutdialog.ui
    ui/historydialog.ui
)

set(RESOURCE_FILES
    resources/resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smartincubator
        MANUAL_FINALIZATION
        ${SRC_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
        ${RESOURCE_FILES}
    )
else()
    add_executable(smartincubator
        ${SRC_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
        ${RESOURCE_FILES}
    )
endif()

target_link_libraries(smartincubator PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::SerialPort
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smartincubator)
endif()
