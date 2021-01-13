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

#include "AppWidgets/mainwindow.h"
#include "app_config.h"
#include "utils.h"
#include <QCommandLineParser>
#include <QStandardPaths>
#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VERSION);
    QString orgName("eXhumer");
    app.setOrganizationName(orgName);

    QDir configDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if(!configDir.exists())
        configDir.mkpath(".");

    QSettings::setDefaultFormat(jsonFormat);

    QTranslator appTranslator;
    if(appTranslator.load(QLocale(), PROJECT_NAME, ".", QString(), ".qm"))
        app.installTranslator(&appTranslator);

    MainWindow win;
    win.show();
    return app.exec();
}
