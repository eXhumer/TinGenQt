#include "googlefolderselectorwidget.h"
#include <QJsonDocument>
#include <QNetworkReply>
#include <QPushButton>
#include <QJsonObject>
#include <QBoxLayout>
#include <QJsonArray>
#include <QTreeView>

GoogleFolderSelectorWidget::GoogleFolderSelectorWidget(GoogleOAuth2Flow *googleFlow, QWidget *parent)
    : QWidget(parent), googleFlow(googleFlow)
{
    this->initUI();
    connect(googleFlow, &GoogleOAuth2Flow::granted, [this](){
        auto drivesRes = this->googleFlow->get(QUrl("https://www.googleapis.com/drive/v3/drives"), {{"pageSize", 100}});
        connect(drivesRes, &QNetworkReply::finished, [drivesRes](){
            auto drivesJsonDoc = QJsonDocument::fromJson(drivesRes->readAll());
            auto drivesArray = drivesJsonDoc["drives"].toArray();
            for(int i = 0; i < drivesArray.size(); i++)
            {
                auto driveJsonObj = drivesArray[i].toObject();
                qInfo() << driveJsonObj["id"].toString() << "-" << driveJsonObj["name"].toString();
            }
        });
    });
}

void GoogleFolderSelectorWidget::initUI()
{
    auto widgetLayout = new QVBoxLayout;
    this->setLayout(widgetLayout);
    auto treeView = new QTreeView;
    widgetLayout->addWidget(treeView);
    auto btnsLayout = new QHBoxLayout;
    btnsLayout->addStretch();
    auto acceptBtn = new QPushButton(tr("selector.accept"));
    auto rejecttBtn = new QPushButton(tr("selector.reject"));
    btnsLayout->addWidget(acceptBtn);
    btnsLayout->addWidget(rejecttBtn);
    btnsLayout->addStretch();
    widgetLayout->addLayout(btnsLayout);
}
