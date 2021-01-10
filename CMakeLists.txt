cmake_minimum_required(VERSION 3.5)

project(TinGen
    LANGUAGES
        CXX
    VERSION
        0.0.1
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5
    COMPONENTS
        Widgets
        Network
        NetworkAuth
        LinguistTools
    REQUIRED
)

set(TS_FILES
    translations/${PROJECT_NAME}.en_US.ts
)

set(PROJECT_SOURCES
    main.cpp
    ${TS_FILES}
)

configure_file(app_config.h.in app_config.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(AppWidgets)
add_subdirectory(Qt-Secret)
add_subdirectory(jwt-cpp)

qt5_create_translation(QM_FILES
    ${CMAKE_SOURCE_DIR}
    ${TS_FILES}
)

add_executable(${PROJECT_NAME}
    ${QM_FILES}
    ${PROJECT_SOURCES}
    ${PROJECT_NAME}.qrc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt5::Widgets
        AppWidgets
        Qt-Secret
)
