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
#include <QRadioButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QWidget>
#include <QLabel>

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);

private slots:
    void onOAuthGrant();

private:
    QPushButton *encPubKeyPathSelectBtn;
    QPushButton *selectFoldersBtn;
    QPushButton *authNewUserBtn;
    QPushButton *indexOutPathSelectBtn;
    QPushButton *revokeUserBtn;
    QPushButton *generateBtn;
    QCheckBox *encryptIndexCheckBox;
    QCheckBox *titleIdFilterCheckBox;
    QCheckBox *extensionFilterCheckBox;
    QCheckBox *successMsgCheckBox;
    QRadioButton *zstdCompressionBtn;
    QRadioButton *zlibCompressionBtn;
    QRadioButton *noCompressionBtn;
    QGroupBox *googleAuthGroup;
    QGroupBox *folderSelectGroup;
    QGroupBox *indexOptionsGroup;
    QGroupBox *encIndexOptionsGroup;
    QLineEdit *googleAuthLineEdit;
    QLineEdit *encPubKeyPathLineEdit;
    QLineEdit *indexOutPathLineEdit;
    QLineEdit *successMsgLineEdit;
    QLabel *appLabel;
    QNetworkAccessManager *networkAccessManager;
    GoogleOAuth2Flow *googleOAuthFlow;
    void initGUI();
};

#endif // CENTRALWIDGET_H
