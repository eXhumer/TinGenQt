#ifndef GOOGLEFOLDERSELECTORWIDGET_H
#define GOOGLEFOLDERSELECTORWIDGET_H

#include "googleoauth2flow.h"
#include <QWidget>

class GoogleFolderSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GoogleFolderSelectorWidget(GoogleOAuth2Flow *googleFlow, QWidget *parent = nullptr);

private:
    void initUI();
    GoogleOAuth2Flow *googleFlow;
};

#endif // GOOGLEFOLDERSELECTORWIDGET_H
