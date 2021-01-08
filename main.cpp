#include "AppWidgets/mainwindow.h"
#include "app_config.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VERSION);
    MainWindow win;
    win.show();
    return app.exec();
}
