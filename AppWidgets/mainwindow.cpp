/*
    TinGen - Index Generator for Tinfoil
    Copyright (C) 2021 eXhumer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "centralwidget.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QBoxLayout>
#include <QStatusBar>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Menu Bar Setup
    this->setMenuBar(new QMenuBar);
    auto fileMenu = this->menuBar()->addMenu(tr("header.file"));
    auto exitAct = fileMenu->addAction(tr("header.file.exit"));
    auto helpMenu = this->menuBar()->addMenu(tr("header.help"));
    auto aboutAct = helpMenu->addAction(tr("header.help.about"));
    auto aboutQtAct = helpMenu->addAction(tr("header.help.aboutqt"));

    // Menu Bar Signal/Slot connections
    connect(exitAct, &QAction::triggered, QCoreApplication::quit);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::showAbout);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::showAboutQt);

    // Status Bar Setup
    this->setStatusBar(new QStatusBar);
    this->statusBar()->showMessage(tr("status.ready"));

    // Central Widget Setup
    this->setCentralWidget(new CentralWidget);
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("header.help.about"), tr("header.help.about.text"));
}

void MainWindow::showAboutQt()
{
    QMessageBox::aboutQt(this, tr("header.help.aboutqt"));
}
