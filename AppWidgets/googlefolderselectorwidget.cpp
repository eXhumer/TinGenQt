#include "googlefolderselectorwidget.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QTreeView>

GoogleFolderSelectorWidget::GoogleFolderSelectorWidget(QWidget *parent)
    : QWidget(parent)
{
    auto widgetLayout = new QVBoxLayout;
    this->setLayout(widgetLayout);
    auto treeView = new QTreeView;
    widgetLayout->addWidget(treeView);
    auto btnsLayout = new QHBoxLayout;
    btnsLayout->addStretch();
    btnsLayout->addWidget(new QPushButton);
    btnsLayout->addWidget(new QPushButton);
    btnsLayout->addStretch();
    widgetLayout->addLayout(btnsLayout);
}
