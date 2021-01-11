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

#ifndef GOOGLEOAUTH2FLOW_H
#define GOOGLEOAUTH2FLOW_H

#include <QOAuth2AuthorizationCodeFlow>

class GoogleOAuth2Flow : public QOAuth2AuthorizationCodeFlow
{
    Q_OBJECT

public:
    explicit GoogleOAuth2Flow(QNetworkAccessManager *networkAccessMgr = nullptr, QObject *parent = nullptr);
};

#endif // GOOGLEOAUTH2FLOW_H
