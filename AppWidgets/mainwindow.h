#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void showAbout();
    void showAboutQt();
};
#endif // MAINWINDOW_H
