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

#ifndef UTILS_H
#define UTILS_H

#include <QIODevice> // QIODevice
#include <QSettings> // QSettings

extern const QSettings::Format jsonFormat;
bool jsonWriteFunc(QIODevice &device, const QSettings::SettingsMap &map);
bool jsonReadFunc(QIODevice &device, QSettings::SettingsMap &map);

#endif // UTILS_H
