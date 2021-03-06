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

#include "../utils.h"
#include "../app_config.h"
#include "centralwidget.h"
#include "googlefolderselectorwidget.h"
#include <QDesktopServices>
#include <jwt-cpp/jwt.h>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QApplication>
#include <QMessageBox>
#include <QJsonObject>
#include <QBoxLayout>
#include <QTreeView>
#include <QUrlQuery>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    this->networkAccessManager = new QNetworkAccessManager(this);
    this->googleOAuthFlow = new GoogleOAuth2Flow(this->networkAccessManager, this);
    auto googleFSWidget = new GoogleFolderSelectorWidget(this->googleOAuthFlow);
    this->googleOAuthFlow->setScope("https://www.googleapis.com/auth/drive profile");
    this->initGUI();

    connect(this->authNewUserBtn, &QPushButton::clicked, this->googleOAuthFlow, &GoogleOAuth2Flow::grant);
    connect(this->revokeUserBtn, &QPushButton::clicked, this, &CentralWidget::revokeUserToken);
    connect(this->googleOAuthFlow, &GoogleOAuth2Flow::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(this->googleOAuthFlow, &GoogleOAuth2Flow::granted, this, &CentralWidget::onOAuthGrant);
    connect(this->successMsgCheckBox, &QCheckBox::clicked, this->successMsgLineEdit, &QLineEdit::setEnabled);
    connect(this->encryptIndexCheckBox, &QCheckBox::clicked, this->encPubKeyPathSelectBtn, &QPushButton::setEnabled);
    connect(this->selectFoldersBtn, &QPushButton::clicked, googleFSWidget, &GoogleFolderSelectorWidget::show);
}

void CentralWidget::initGUI()
{
    auto centralLayout = new QVBoxLayout;
    this->setLayout(centralLayout);

    this->appLabel = new QLabel(QCoreApplication::applicationName());
    centralLayout->addWidget(this->appLabel, 0, Qt::AlignHCenter);

    this->googleAuthGroup = new QGroupBox(tr("main.google_auth_group"));
    this->googleAuthGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(this->googleAuthGroup);

    this->googleAuthLineEdit = new QLineEdit;
    this->googleAuthLineEdit->setEnabled(false);
    this->googleAuthGroup->layout()->addWidget(this->googleAuthLineEdit);

    this->authNewUserBtn = new QPushButton(tr("main.auth_user_btn"));
    this->googleAuthGroup->layout()->addWidget(this->authNewUserBtn);

    this->revokeUserBtn = new QPushButton(tr("main.revoke_user_btn"));
    this->googleAuthGroup->layout()->addWidget(this->revokeUserBtn);

    this->folderSelectGroup = new QGroupBox(tr("main.folder_select_group"));
    this->folderSelectGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(this->folderSelectGroup);

    this->selectFoldersBtn = new QPushButton(tr("main.select_folders_btn"));
    this->folderSelectGroup->layout()->addWidget(this->selectFoldersBtn);

    this->indexOptionsGroup = new QGroupBox(tr("main.index_options_group"));
    auto indexOptionsLayout = new QVBoxLayout;
    this->indexOptionsGroup->setLayout(indexOptionsLayout);
    centralLayout->addWidget(this->indexOptionsGroup);

    auto compressionLayout = new QHBoxLayout;
    this->zstdCompressionBtn = new QRadioButton(tr("main.index_options_group.zstd_compress_btn"));
    this->zstdCompressionBtn->toggle(); // make zstd default compression
    this->zlibCompressionBtn = new QRadioButton(tr("main.index_options_group.zlib_compress_btn"));
    this->noCompressionBtn = new QRadioButton(tr("main.index_options_group.no_compress_btn"));
    compressionLayout->addWidget(this->zstdCompressionBtn);
    compressionLayout->addWidget(this->zlibCompressionBtn);
    compressionLayout->addWidget(this->noCompressionBtn);
    indexOptionsLayout->addLayout(compressionLayout);

    auto successLayout = new QHBoxLayout;
    this->successMsgCheckBox = new QCheckBox(tr("main.index_options_group.success"));
    this->successMsgLineEdit = new QLineEdit;
    this->successMsgLineEdit->setEnabled(false);
    successLayout->addWidget(this->successMsgCheckBox);
    successLayout->addWidget(this->successMsgLineEdit);
    indexOptionsLayout->addLayout(successLayout);

    auto filterOptionsLayout = new QGridLayout;
    this->titleIdFilterCheckBox = new QCheckBox(tr("main.index_options_group.title_id_filter"));
    this->extensionFilterCheckBox = new QCheckBox(tr("main.index_options_group.extension_filter"));
    filterOptionsLayout->addWidget(this->titleIdFilterCheckBox, 0, 0);
    filterOptionsLayout->addWidget(this->extensionFilterCheckBox, 0, 1);
    indexOptionsLayout->addLayout(filterOptionsLayout);

    // TODO: chainload options

    auto indexOutputPathLayout = new QHBoxLayout;
    this->indexOutPathSelectBtn = new QPushButton(tr("main.index_options_group.select_output_btn"));
    this->indexOutPathLineEdit = new QLineEdit;
    this->indexOutPathLineEdit->setEnabled(false);
    indexOutputPathLayout->addWidget(this->indexOutPathSelectBtn);
    indexOutputPathLayout->addWidget(this->indexOutPathLineEdit);
    indexOptionsLayout->addLayout(indexOutputPathLayout);

    this->encIndexOptionsGroup = new QGroupBox(tr("main.encrypt_index_options_group"));
    auto encIndexOptionsGroupLayout = new QVBoxLayout;
    this->encIndexOptionsGroup->setLayout(encIndexOptionsGroupLayout);
    centralLayout->addWidget(this->encIndexOptionsGroup);

    this->encryptIndexCheckBox = new QCheckBox(tr("main.encrypt_index_options_group.encrypt_index"));
    encIndexOptionsGroupLayout->addWidget(this->encryptIndexCheckBox, 0, Qt::AlignHCenter);

    auto encPubKeyLayout = new QHBoxLayout;
    encIndexOptionsGroupLayout->addLayout(encPubKeyLayout);

    this->encPubKeyPathSelectBtn = new QPushButton(tr("main.encrypt_index_options_group.select_key_btn"));
    this->encPubKeyPathSelectBtn->setEnabled(false);
    this->encPubKeyPathLineEdit = new QLineEdit;
    this->encPubKeyPathLineEdit->setEnabled(false);
    encPubKeyLayout->addWidget(this->encPubKeyPathSelectBtn);
    encPubKeyLayout->addWidget(this->encPubKeyPathLineEdit);

    this->generateBtn = new QPushButton(tr("main.generate_btn"));
    centralLayout->addWidget(this->generateBtn);

    centralLayout->addStretch();

    this->onRevokeSuccess();
}

void CentralWidget::onOAuthGrant()
{
    auto extraTokens = this->googleOAuthFlow->extraTokens();
    auto extraTokensKeys = extraTokens.keys();
    for(auto const &extraTokenkey: extraTokensKeys)
    {
        // if id_token present, update login status
        if(extraTokenkey == "id_token")
        {
#if 1
            // without jwt-cpp
            auto idTokenJwtTokenParts = extraTokens[extraTokenkey].toString().split(".");
            auto jwtTokenHeader = idTokenJwtTokenParts[0];
            Q_UNUSED(jwtTokenHeader);
            auto jwtTokenPayload = idTokenJwtTokenParts[1].toUtf8();
            auto userProfile = QJsonDocument::fromJson(QByteArray::fromBase64(jwtTokenPayload, QByteArray::Base64UrlEncoding));
            auto jwtTokenSignature = idTokenJwtTokenParts[2];
            Q_UNUSED(jwtTokenSignature);
            auto userFullName = userProfile["name"].toString();
            this->onAuthSuccess(userFullName);
#else
            // with jwt-cpp
            auto idTokenJwt = jwt::decode(extraTokens[extraTokenkey].toString().toStdString());
            for(auto &claim: idTokenJwt.get_payload_claims())
            {
                if(claim.first == "name") {
                    auto userFullName = QString::fromStdString(claim.second.as_string());
                    googleAuthLineEdit->setText(tr("main.logged_in_as") + " " + userFullName);
                    authNewUserBtn->setEnabled(false);
                    revokeUserBtn->setEnabled(true);
                    selectFoldersBtn->setEnabled(true);
                }
            }
#endif
        }
    }
}

void CentralWidget::revokeUserToken()
{
    // TODO: Use openid discovery later
    // QUrl googleOpenIDConfigUrl("https://accounts.google.com/.well-known/openid-configuration");
    // QNetworkRequest googleOpenIDConfigReq(googleOpenIDConfigUrl);
    // auto googleOpenIDConfigRes = this->networkAccessManager->get(googleOpenIDConfigReq);
    QUrl googleOAuthRevokeUrl("https://oauth2.googleapis.com/revoke");
    QUrlQuery reqBody({{"token", this->googleOAuthFlow->refreshToken()}});;
    QNetworkRequest googleOAuthRevokeReq(googleOAuthRevokeUrl);
    googleOAuthRevokeReq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    auto googleOAuthRevokeRes = this->networkAccessManager->post(googleOAuthRevokeReq, reqBody.toString(QUrl::FullyEncoded).toUtf8());
    connect(googleOAuthRevokeRes, &QNetworkReply::finished, [this, googleOAuthRevokeRes](){
        auto resStatusCode = googleOAuthRevokeRes->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (resStatusCode != 200)
            QMessageBox::warning(this, "Failed to revoke token", "Status Code: " + QString::number(resStatusCode));
        else
            QMessageBox::information(this, "Token Revoke Success", "Token revoked successfully!");
    });
    connect(googleOAuthRevokeRes, &QNetworkReply::finished, this, &CentralWidget::onRevokeSuccess);
    connect(googleOAuthRevokeRes, &QNetworkReply::finished, googleOAuthRevokeRes, &QNetworkReply::deleteLater);
}

void CentralWidget::onRevokeSuccess()
{
    this->googleAuthLineEdit->setText(QString(tr("main.not_authorized")));
    this->authNewUserBtn->setEnabled(true);
    this->revokeUserBtn->setEnabled(false);
    this->selectFoldersBtn->setEnabled(false);
    this->generateBtn->setEnabled(false);
}

void CentralWidget::onAuthSuccess(const QString& userName)
{
    this->googleAuthLineEdit->setText(tr("main.logged_in_as") + " " + userName);
    this->authNewUserBtn->setEnabled(false);
    this->revokeUserBtn->setEnabled(true);
    this->selectFoldersBtn->setEnabled(true);
    this->generateBtn->setEnabled(true);
}
