#include "mytimer.h"
#include <QTimer>
#include <QDateTime>

myTimer::myTimer()
{
    tElapsed = setTimeElapsed();
    tElapsedLbl = new QLabel();
    ElapsedTimeLbl = new QLabel("Time Elapsed");
    ElapsedTimeLbl->setFont(QFont("Times", 16, QFont::Bold));
    myQVBox = new QVBoxLayout();

    QTimer *time = new QTimer();
    connect(time, &QTimer::timeout, this, &myTimer::updateTimer);
    time->start(1000);

    myQVBox->addWidget(ElapsedTimeLbl);
    myQVBox->addWidget(tElapsedLbl);
    myQVBox->setAlignment(Qt::AlignLeft);

    setLayout(myQVBox);
}

void myTimer::updateTimer() {
    tElapsedLbl->setText(QString(QDateTime::fromTime_t(tElapsed).toUTC().toString("hh:mm:ss")));
    tElapsed++;
}

int myTimer::setTimeElapsed() {
    // Get Time elapsed from server and convert to int
    return 120; //test
}
