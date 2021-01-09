#include "centralwidget.h"
#include <QDesktopServices>
#include <QApplication>
#include <QFormLayout>
#include <QBoxLayout>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    this->networkAccessManager = new QNetworkAccessManager(this);
    this->googleOAuthFlow = new GoogleOAuth2Flow(this->networkAccessManager, this);
    connect(this->googleOAuthFlow, &GoogleOAuth2Flow::authorizeWithBrowser, &QDesktopServices::openUrl);

    auto centralLayout = new QVBoxLayout;
    this->setLayout(centralLayout);

    this->appLabel = new QLabel(QCoreApplication::applicationName());
    centralLayout->addWidget(this->appLabel, 0, Qt::AlignHCenter);

    this->googleAuthGroup = new QGroupBox(tr("main.google_auth_group"));
    this->googleAuthGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(this->googleAuthGroup);

    auto lineEdit = new QLineEdit;
    googleAuthGroup->layout()->addWidget(lineEdit);

    auto authNewUserBtn = new QPushButton(tr("main.auth_user_btn"));
    connect(authNewUserBtn, &QPushButton::clicked, this, &CentralWidget::authBtnClicked);
    googleAuthGroup->layout()->addWidget(authNewUserBtn);

    auto revokeUserBtn = new QPushButton(tr("main.revoke_user_btn"));
    googleAuthGroup->layout()->addWidget(revokeUserBtn);

    auto folderSelectGroup = new QGroupBox(tr("main.folder_select_group"));
    folderSelectGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(folderSelectGroup);

    auto selectFoldersBtn = new QPushButton(tr("main.select_folders_btn"));
    folderSelectGroup->layout()->addWidget(selectFoldersBtn);

    auto indexOptionsGroup = new QGroupBox(tr("main.index_options_group"));
    indexOptionsGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(indexOptionsGroup);

    auto encIndexOptionsGroup = new QGroupBox(tr("main.encrypt_index_options_group"));
    encIndexOptionsGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(encIndexOptionsGroup);

    auto generateBtn = new QPushButton(tr("main.generate_btn"));
    centralLayout->addWidget(generateBtn);

    centralLayout->addStretch();
}

void CentralWidget::authBtnClicked(bool clicked) {
    Q_UNUSED(clicked);
    this->googleOAuthFlow->grant();
}
