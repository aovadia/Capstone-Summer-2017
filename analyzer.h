#ifndef ANALYZER_H
#define ANALYZER_H

#include <QtSql/QSqlQuery>
#include <QString>
#include <QVector>
#include <QVariant>

class Analyzer
{
public:
    Analyzer(QSqlQuery *a);
    QVector<QString> TotalBikesCheckedIn();
    QVector<QString> TotalBikesCheckedOut();
    QVector<QString> TotalBikesInService();
    QVector<QString> TotalBikesActive();
    QVector<QString> TotalBikesAbove5();
    QVector<QString> TotalBikesBelow5();
    QVector<QString> DistanceBikesCheckedIn();
    QVector<QString> DistanceBikesCheckedOut();
    QVector<QString> DistanceBikesInService();
    QVector<QString> DistanceBikesActive();
    QVector<QString> DistanceBikesAbove5();
    QVector<QString> DistanceBikesBelow5();

private:
    QSqlQuery *query;
    QString select1 = "SELECT BikeId" ;
    QString select2 = "SELECT BikeId, Distance ";
    QString from = "FROM Master ";
    QString where = "WHERE ";
    QString orderBy = "ORDER BY ";
    QString desc = " DESC";
};

#endif // ANALYZER_H
