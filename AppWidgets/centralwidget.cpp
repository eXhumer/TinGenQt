#include "centralwidget.h"
#include <QDesktopServices>
#include <jwt-cpp/jwt.h>
#include <QApplication>
#include <QRadioButton>
#include <QMessageBox>
#include <QFormLayout>
#include <QBoxLayout>
#include <QCheckBox>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    this->networkAccessManager = new QNetworkAccessManager(this);
    this->googleOAuthFlow = new GoogleOAuth2Flow(this->networkAccessManager, this);
    this->googleOAuthFlow->setScope("https://www.googleapis.com/auth/drive openid profile email");

    auto centralLayout = new QVBoxLayout;
    this->setLayout(centralLayout);

    this->appLabel = new QLabel(QCoreApplication::applicationName());
    centralLayout->addWidget(this->appLabel, 0, Qt::AlignHCenter);

    this->googleAuthGroup = new QGroupBox(tr("main.google_auth_group"));
    this->googleAuthGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(this->googleAuthGroup);

    auto googleAuthLineEdit = new QLineEdit;
    googleAuthLineEdit->setEnabled(false);
    googleAuthGroup->layout()->addWidget(googleAuthLineEdit);

    auto authNewUserBtn = new QPushButton(tr("main.auth_user_btn"));
    googleAuthGroup->layout()->addWidget(authNewUserBtn);

    auto revokeUserBtn = new QPushButton(tr("main.revoke_user_btn"));
    revokeUserBtn->setEnabled(false);
    googleAuthGroup->layout()->addWidget(revokeUserBtn);

    auto folderSelectGroup = new QGroupBox(tr("main.folder_select_group"));
    folderSelectGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(folderSelectGroup);

    auto selectFoldersBtn = new QPushButton(tr("main.select_folders_btn"));
    selectFoldersBtn->setEnabled(false);
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
    successMsgLineEdit->setEnabled(false);
    successLayout->addWidget(successMsgCheckBox);
    successLayout->addWidget(successMsgLineEdit);
    indexOptionsLayout->addLayout(successLayout);

    auto filterOptionsLayout = new QGridLayout;
    auto titleIdFilterCheckBox = new QCheckBox(tr("main.index_options_group.title_id_filter"));
    auto extensionFilterCheckBox = new QCheckBox(tr("main.index_options_group.extension_filter"));
    filterOptionsLayout->addWidget(titleIdFilterCheckBox, 0, 0);
    filterOptionsLayout->addWidget(extensionFilterCheckBox, 0, 1);
    indexOptionsLayout->addLayout(filterOptionsLayout);

    // TODO: chainload options

    auto indexOutputPathLayout = new QHBoxLayout;
    auto indexOutPathSelectBtn = new QPushButton(tr("main.index_options_group.select_output_btn"));
    auto indexOutPathLineEdit = new QLineEdit;
    indexOutputPathLayout->addWidget(indexOutPathSelectBtn);
    indexOutputPathLayout->addWidget(indexOutPathLineEdit);
    indexOptionsLayout->addLayout(indexOutputPathLayout);

    auto encIndexOptionsGroup = new QGroupBox(tr("main.encrypt_index_options_group"));
    auto encIndexOptionsGroupLayout = new QVBoxLayout;
    encIndexOptionsGroup->setLayout(encIndexOptionsGroupLayout);
    centralLayout->addWidget(encIndexOptionsGroup);

    auto encryptIndexCheckBox = new QCheckBox(tr("main.encrypt_index_options_group.encrypt_index"));
    encIndexOptionsGroupLayout->addWidget(encryptIndexCheckBox, 0, Qt::AlignHCenter);

    auto encPubKeyLayout = new QHBoxLayout;
    encIndexOptionsGroupLayout->addLayout(encPubKeyLayout);

    auto encPubKeyPathSelectBtn = new QPushButton(tr("main.encrypt_index_options_group.select_key_btn"));
    auto encPubKeyPathLineEdit = new QLineEdit;
    encPubKeyLayout->addWidget(encPubKeyPathSelectBtn);
    encPubKeyLayout->addWidget(encPubKeyPathLineEdit);

    auto generateBtn = new QPushButton(tr("main.generate_btn"));
    centralLayout->addWidget(generateBtn);

    centralLayout->addStretch();

    connect(authNewUserBtn, &QPushButton::clicked, this, [this](){
        this->googleOAuthFlow->grant();
    });
    connect(this->googleOAuthFlow, &GoogleOAuth2Flow::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(this->googleOAuthFlow, &GoogleOAuth2Flow::granted, this, [=](){
        auto extraTokens = this->googleOAuthFlow->extraTokens();
        auto extraTokensKeys = extraTokens.keys();
        for(auto const &extraTokenkey: extraTokensKeys)
        {
            if(extraTokenkey == "id_token")
            {
                auto idTokenJwt = jwt::decode(extraTokens[extraTokenkey].toString().toStdString());
                for(auto &claim: idTokenJwt.get_payload_claims())
                {
                    if(claim.first == "name") {
                        googleAuthLineEdit->setText("Logged in as " + QString::fromStdString(claim.second.as_string()));
                        authNewUserBtn->setEnabled(false);
                        revokeUserBtn->setEnabled(true);
                        selectFoldersBtn->setEnabled(true);
                    } else {
                        continue;
                    }
                }
            } else {
                continue;
            }
        }
    });
}
