#include "mytimer.h"
#include <QTimer>
#include <QDateTime>
#include <QVariant>
myTimer::myTimer(QSqlQuery *query1,int BikeId1)
{
    query = query1;
    BikeId = BikeId1;
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
    bool CheckedOut;
    QDateTime prevTime;
    int diff, days;
    const int SECSTODAYS = 86400;
    QString statement = "SELECT CheckedOut FROM Master WHERE BikeId = ";
    statement.append(QString::fromStdString(std::to_string(BikeId)));
    if (query->exec(statement)) {
        query->next();
        CheckedOut = query->value(0).toBool();
        statement = "SELECT ";
        if (CheckedOut) statement.append("Rented ");
        else statement.append("Returned ");
        statement.append("FROM Rentals WHERE BikeId = ");
        statement.append(QString::fromStdString(std::to_string(BikeId)));
        statement.append(" ORDER BY RentalId DESC");
        if (query->exec(statement)) {
            query->next();
            prevTime = query->value(0).toDateTime();
            QDateTime curTime = QDateTime::currentDateTime();
            diff = prevTime.secsTo(curTime);
            days = diff / SECSTODAYS;
            diff = diff % SECSTODAYS;
            if (CheckedOut) old_diff = diff;
        }
    }
    QString time;
    if (days) {
        time = QString::fromStdString(std::to_string(days));
        time.append(" days , ");
    } else {
        time = "";
    }
    time.append(QDateTime::fromTime_t(old_diff).toUTC().toString("hh:mm:ss"));
    tElapsedLbl->setText(time);
}
