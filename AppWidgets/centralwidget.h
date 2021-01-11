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

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "googleoauth2flow.h"
#include <QNetworkAccessManager>
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
    QNetworkAccessManager *networkAccessManager;
    GoogleOAuth2Flow *googleOAuthFlow;

};

#endif // CENTRALWIDGET_H
