/***************************************************************************
**
** TinGen - Index Generator for Tinfoil
** Copyright (C) 2021 eXhumer
**
** $QT_BEGIN_LICENSE:GPL3$
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License
** version 3. The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL3 included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License requirements will be met:
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
**
** $QT_END_LICENSE$
**
***************************************************************************/

#include "AppWidgets/mainwindow.h" // MainWindow
#include "app_config.h" // PROJECT_NAME / PROJECT_VERSION
#include "utils.h" // jsonFormat
#include <QStandardPaths> // QStandardPaths
#include <QApplication> // QApplication
#include <QTranslator> // QTranslator
#include <QSettings> // QSettings
#include <QDir> // QDir

const QString orgName("eXhumer");

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VERSION);
    app.setOrganizationName(orgName);

    // $HOME/orgName/PROJECT_NAME/
    QDir configDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if(!configDir.exists())
        configDir.mkpath(".");

    QSettings appSettings(configDir.path() + "/app_config.json", jsonFormat);

    QTranslator appTranslator;
    if(appTranslator.load(QLocale(), PROJECT_NAME, ".", QString(), ".qm"))
        app.installTranslator(&appTranslator);
    else if(appTranslator.load(QLocale(QLocale::English, QLocale::UnitedStates), PROJECT_NAME, ".", QString(), ".qm"))
        app.installTranslator(&appTranslator);

    MainWindow win(appSettings);
    win.show();
    return app.exec();
}
