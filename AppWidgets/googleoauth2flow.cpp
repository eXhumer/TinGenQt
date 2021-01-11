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
