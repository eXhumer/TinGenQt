#ifndef UTILS_H
#define UTILS_H

#include <QIODevice>
#include <QSettings>

extern const QSettings::Format jsonFormat;
bool jsonWriteFunc(QIODevice &device, const QSettings::SettingsMap &map);
bool jsonReadFunc(QIODevice &device, QSettings::SettingsMap &map);

#endif // UTILS_H
