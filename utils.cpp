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

#include "utils.h" // QIODevice, QSettings
#include <QJsonDocument> // QJsonDocument
#include <QJsonObject> // QJsonObject

const QSettings::Format jsonFormat = QSettings::registerFormat("json", jsonReadFunc, jsonWriteFunc);

bool jsonWriteFunc(QIODevice &device, const QSettings::SettingsMap &map)
{
    return device.write(QJsonDocument(QJsonObject::fromVariantMap(map)).toJson()) != -1;
}

bool jsonReadFunc(QIODevice &device, QSettings::SettingsMap &map)
{
    QJsonDocument json = QJsonDocument::fromJson(device.readAll());
    map = json.object().toVariantMap();
    return true;
}
