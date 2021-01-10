#include "AppWidgets/mainwindow.h"
#include "app_config.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VERSION);
    QTranslator appTranslator;
    if(appTranslator.load(QLocale(), PROJECT_NAME, ".", QString(), ".qm"))
        app.installTranslator(&appTranslator);
    MainWindow win;
    win.show();
    return app.exec();
}
