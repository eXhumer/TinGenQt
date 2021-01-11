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
