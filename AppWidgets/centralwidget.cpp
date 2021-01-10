#include "centralwidget.h"
#include <QDesktopServices>
#include <QApplication>
#include <QRadioButton>
#include <QFormLayout>
#include <QBoxLayout>
#include <QCheckBox>

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
    auto indexOptionsLayout = new QVBoxLayout;
    indexOptionsGroup->setLayout(indexOptionsLayout);
    centralLayout->addWidget(indexOptionsGroup);

    auto compressionLayout = new QHBoxLayout;
    auto zstdCompressionBtn = new QRadioButton(tr("main.index_options_group.zstd_compress_btn"));
    auto zlibCompressionBtn = new QRadioButton(tr("main.index_options_group.zlib_compress_btn"));
    auto noCompressionBtn = new QRadioButton(tr("main.index_options_group.no_compress_btn"));
    compressionLayout->addWidget(zstdCompressionBtn);
    compressionLayout->addWidget(zlibCompressionBtn);
    compressionLayout->addWidget(noCompressionBtn);
    indexOptionsLayout->addLayout(compressionLayout);

    auto successLayout = new QHBoxLayout;
    auto successMsgCheckBox = new QCheckBox(tr("main.index_options_group.success"));
    auto successMsgLineEdit = new QLineEdit;
    successLayout->addWidget(successMsgCheckBox);
    successLayout->addWidget(successMsgLineEdit);
    indexOptionsLayout->addLayout(successLayout);

    // chainload options
    // add-nsw-files-without-title-id
    // add-non-nsw-files

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
