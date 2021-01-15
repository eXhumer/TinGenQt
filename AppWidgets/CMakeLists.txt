set(APPWIDGETS_SOURCES
    mainwindow.cpp
    mainwindow.h
    centralwidget.cpp
    centralwidget.h
    googleoauth2flow.cpp
    googleoauth2flow.h
    googlefolderselectoritem.cpp
    googlefolderselectoritem.h
    googlefolderselectorwidget.cpp
    googlefolderselectorwidget.h
    googlefolderselectormodel.cpp
    googlefolderselectormodel.h
)

add_library(AppWidgets
    ${APPWIDGETS_SOURCES}
)

target_link_libraries(AppWidgets
    PRIVATE
        Qt5::Widgets
        Qt5::Network
        Qt5::NetworkAuth
        jwt-cpp::jwt-cpp
)
