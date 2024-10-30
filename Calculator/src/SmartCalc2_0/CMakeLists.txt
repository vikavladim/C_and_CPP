cmake_minimum_required(VERSION 3.5)

project(SmartCalc VERSION 2.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -g")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cc")

include_directories(
    ${CMAKE_SOURCE_DIR}/controller
    ${CMAKE_SOURCE_DIR}/view
    ${CMAKE_SOURCE_DIR}/view/expressions_tab
    ${CMAKE_SOURCE_DIR}/view/credit_tab
    ${CMAKE_SOURCE_DIR}/view/deposit_tab
    ${CMAKE_SOURCE_DIR}/model/credit
    ${CMAKE_SOURCE_DIR}/model/deposit
    ${CMAKE_SOURCE_DIR}/model/expressions
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_SOURCE_DIR}/external/googletest
    ${CMAKE_SOURCE_DIR}
)

set(CMAKE_AUTOUIC_SEARCH_PATHS view)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}Charts REQUIRED)


set(FORMS
    ${CMAKE_SOURCE_DIR}/view/mainwindowview.ui
    ${CMAKE_SOURCE_DIR}/resource.qrc
)

set(PROJECT_SOURCES
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc2_0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalc2_0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartCalc2_0 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalc2_0
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalc2_0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(SmartCalc2_0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc2_0)
endif()


add_library(calculation STATIC 
    ${CMAKE_SOURCE_DIR}/model/expressions/calculate.cc
    ${CMAKE_SOURCE_DIR}/model/expressions/token.cc
    ${CMAKE_SOURCE_DIR}/model/expressions/polish_notation.cc
    ${CMAKE_SOURCE_DIR}/model/expressions/parser.cc
)

# file(GLOB EXPRESSION_FILES "${CMAKE_SOURCE_DIR}/model/expressions/*.cc")
# add_library(calculation STATIC ${EXPRESSION_FILES})

enable_testing()

add_subdirectory(external)
add_executable(test_app
   ../test.cc)
   
target_link_libraries(test_app calculation gtest_main gmock_main)
