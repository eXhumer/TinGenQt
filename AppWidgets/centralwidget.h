#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

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

private:
    QLabel *appLabel;
    QGroupBox *googleAuthGroup;
};

#endif // CENTRALWIDGET_H
