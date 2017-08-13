#ifndef STATISTICS_H
#define STATISTICS_H
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtSql/QSqlQuery>
#include <QWidget>
#include <QVector>
#include <QString>
#include "analyzer.h"

class Statistics : public QWidget
{
    Q_OBJECT
public:
   explicit Statistics();
   void sendAccess(QSqlQuery * );

private slots:
    void handleDoubleClicked();
    void setCheckIn();
    void setCheckOut();
    void setActive();
    void setInService();
    void setHealthAbove();
    void setHealthBelow();
    void setCheckInDist();
    void setCheckOutDist();
    void setActiveDist();
    void setInServiceDist();
    void setHealthAboveDist();
    void setHealthBelowDist();

private:
    Analyzer *compute;
    QSqlQuery *query;
    QVBoxLayout *mainLayout;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *buttonLayoutHorizontal;
    QHBoxLayout *buttonLayoutHorizontal2;
    QHBoxLayout *buttonLayoutHorizontal3;
    QTableWidget *mTable;
    QVector<QString> data;
    void setTable(QVector<QString>);
    void setTableTwoColumns(QVector<QString>);
};

#endif // STATISTICS_H
