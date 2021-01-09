#ifndef GOOGLEOAUTH2FLOW_H
#define GOOGLEOAUTH2FLOW_H

#include <QOAuth2AuthorizationCodeFlow>

class GoogleOAuth2Flow : public QOAuth2AuthorizationCodeFlow
{
    Q_OBJECT

public:
    explicit GoogleOAuth2Flow(QNetworkAccessManager *networkAccessMgr = nullptr, QObject *parent = nullptr);
};

#endif // GOOGLEOAUTH2FLOW_H
