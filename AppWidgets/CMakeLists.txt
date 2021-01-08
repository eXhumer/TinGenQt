set(APPWIDGETS_SOURCES
    centralwidget.cpp
    centralwidget.h
    mainwindow.cpp
    mainwindow.h
)

add_library(AppWidgets
    ${APPWIDGETS_SOURCES}
)

target_link_libraries(AppWidgets
    PUBLIC Qt5::Widgets
)
