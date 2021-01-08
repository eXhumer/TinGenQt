#include "centralwidget.h"
#include <QBoxLayout>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setLayout(new QVBoxLayout);
}
