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

#include "googlefolderselectorwidget.h"
#include "googlefilesystemmodel.h"
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
        // get list of drives for user
        auto drivesRes = this->googleFlow->get(QUrl("https://www.googleapis.com/drive/v3/drives"), {{"pageSize", 100}});
        //
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
    auto rejectBtn = new QPushButton(tr("selector.reject"));
    btnsLayout->addWidget(acceptBtn);
    btnsLayout->addWidget(rejectBtn);
    btnsLayout->addStretch();
    widgetLayout->addLayout(btnsLayout);
    auto model = new GoogleFileSystemModel();
    treeView->setModel(model);
}
