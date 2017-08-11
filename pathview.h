#ifndef PATHVIEW_H
#define PATHVIEW_H

#include <QWidget>
#include <QWebEngineView>
#include <QVBoxLayout>

class PathView : public QWidget
{
    Q_OBJECT

public:
   explicit PathView();

private:
    QWebEngineView *mWebView;
    QVBoxLayout *mainLayout;


};

#endif // PATHVIEW_H
