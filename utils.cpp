#include "utils.h"
#include <QJsonDocument>
#include <QJsonObject>

const QSettings::Format jsonFormat = QSettings::registerFormat("json", jsonReadFunc, jsonWriteFunc);

bool jsonWriteFunc(QIODevice &device, const QSettings::SettingsMap &map)
{
    device.write(QJsonDocument(QJsonObject::fromVariantMap(map)).toJson());
    return true;
}

bool jsonReadFunc(QIODevice &device, QSettings::SettingsMap &map)
{
    QJsonDocument json = QJsonDocument::fromJson(device.readAll());
    map = json.object().toVariantMap();
    return true;
}
