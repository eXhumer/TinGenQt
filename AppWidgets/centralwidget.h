#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "googleoauth2flow.h"
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QWidget>
#include <QLabel>

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);

public slots:
    void authBtnClicked(bool clicked);

private:
    QLabel *appLabel;
    QGroupBox *googleAuthGroup;
    QNetworkAccessManager *networkAccessManager;
    GoogleOAuth2Flow *googleOAuthFlow;

};

#endif // CENTRALWIDGET_H
