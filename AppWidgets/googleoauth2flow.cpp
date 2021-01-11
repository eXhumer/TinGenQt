/*
    TinGen - Index Generator for Tinfoil
    Copyright (C) 2021 eXhumer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "googleoauth2flow.h"
#include <QOAuthHttpServerReplyHandler>
#include <QJsonDocument>
#include <QFile>

GoogleOAuth2Flow::GoogleOAuth2Flow(QNetworkAccessManager *networkAccessMgr, QObject *parent):
    QOAuth2AuthorizationCodeFlow(networkAccessMgr, parent)
{
    QFile googleAppCreds(":/google/credentials.json");
    QJsonDocument googleAppCredsJsonDoc;

    if (googleAppCreds.open(QIODevice::ReadOnly)) {
        googleAppCredsJsonDoc = QJsonDocument::fromJson(googleAppCreds.readAll());
        googleAppCreds.close();
    }
    else {
        // TODO: ERRROR HANDLING
    }

    this->setAccessTokenUrl(QUrl(googleAppCredsJsonDoc["installed"]["token_uri"].toString()));
    this->setAuthorizationUrl(QUrl(googleAppCredsJsonDoc["installed"]["auth_uri"].toString()));
    this->setClientIdentifier(googleAppCredsJsonDoc["installed"]["client_id"].toString());
    this->setClientIdentifierSharedKey(googleAppCredsJsonDoc["installed"]["client_secret"].toString());
    this->setReplyHandler(new QOAuthHttpServerReplyHandler(QHostAddress("http://localhost"), 0, this));
}
