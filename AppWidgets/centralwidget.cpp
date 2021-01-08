#include "centralwidget.h"
#include <QApplication>
#include <QFormLayout>
#include <QBoxLayout>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
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
    googleAuthGroup->layout()->addWidget(authNewUserBtn);

    auto revokeUserBtn = new QPushButton(tr("main.revoke_user_btn"));
    googleAuthGroup->layout()->addWidget(revokeUserBtn);

    auto folderSelectGroup = new QGroupBox(tr("main.folder_select_group"));
    folderSelectGroup->setLayout(new QVBoxLayout);
    centralLayout->addWidget(folderSelectGroup);

    auto selectFoldersBtn = new QPushButton(tr("main.select_folders_btn"));
    folderSelectGroup->layout()->addWidget(selectFoldersBtn);

    // TODO: Index Creation Options in a Group Box
    // TODO: Add Encryption Options in a Group Box
    // TODO: Add generate button

    centralLayout->addStretch();
}
