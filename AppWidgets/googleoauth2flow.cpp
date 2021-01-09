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
