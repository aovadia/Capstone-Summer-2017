#include "pathview.h"

PathView::PathView()
{
    mainLayout = new QVBoxLayout(this);

    mWebView = new QWebEngineView();
    mWebView->load(QUrl("http://www.gpsvisualizer.com/map_input?form=data"));

    mainLayout->addWidget(mWebView);

    setLayout(mainLayout);
}
