#ifndef MYTIMER_H
#define MYTIMER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>

class myTimer : public QWidget
{
    Q_OBJECT

public:
    explicit myTimer(QSqlQuery *query, int BikeId);
    void setData();

public slots:
    void updateTimer();

private:
    QLabel *ElapsedTimeLbl;
    QLabel *tElapsedLbl;
    QVBoxLayout *myQVBox;
    double tElapsed;
    QSqlQuery *query;
    int BikeId;
    int old_diff;
};

#endif // MYTIMER_H
