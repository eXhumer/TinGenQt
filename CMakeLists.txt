cmake_minimum_required(VERSION 3.5)

project(TinGen LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES translations/TinGen.en_US.ts)

set(PROJECT_SOURCES
    main.cpp
    ${TS_FILES}
)

add_executable(TinGen
    ${PROJECT_SOURCES}
)

add_subdirectory(AppWidgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(TinGen PRIVATE Qt5::Widgets AppWidgets)
