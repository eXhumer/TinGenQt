set(APPWIDGETS_SOURCES
    centralwidget.cpp
    centralwidget.h
    mainwindow.cpp
    mainwindow.h
    googleoauth2flow.cpp
    googleoauth2flow.h
)

add_library(AppWidgets
    ${APPWIDGETS_SOURCES}
)

target_link_libraries(AppWidgets
    PRIVATE
        Qt5::Widgets
        Qt5::Network
        Qt5::NetworkAuth
)
