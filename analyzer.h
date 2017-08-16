#ifndef ANALYZER_H
#define ANALYZER_H

#include <QtSql/QSqlQuery>
#include <QString>
#include <QVector>
//#include <QVariant>

//Analyzer class used to provide analysis to the Bike Statistics user interface.
class Analyzer
{
public:
    //functions (to be described in the definition file)
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
    //preset formatted strings for perfomring queries
    QSqlQuery *query;
    QString select1 = "SELECT BikeId" ;
    QString select2 = "SELECT BikeId, Distance ";
    QString from = " FROM Master ";
    QString where = "WHERE ";
    QString orderBy = "ORDER BY ";
    QString desc = " DESC";
};

#endif // ANALYZER_H
