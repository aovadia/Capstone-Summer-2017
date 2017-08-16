#include "pathview.h"

/*
 * Class used to open webpage to display bike path.
 * Setup pathView widget layout
 */
PathView::PathView()
{
    mainLayout = new QVBoxLayout(this);

    mWebView = new QWebEngineView();
    mWebView->load(QUrl("http://www.gpsvisualizer.com/map_input?form=data"));
    mWebView->setZoomFactor(1.7);

    mainLayout->addWidget(mWebView);

    setLayout(mainLayout);
}
