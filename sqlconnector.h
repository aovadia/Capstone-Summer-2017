#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


class sqlConnector
{
public:
    sqlConnector(int);
    ~sqlConnector();

    bool setNewBikeID(int);
    bool setBikeHealth(int);
    bool setBikeService(bool);
    bool setBikeCheckout(time_t);
    bool setBikeCheckin(time_t);
    bool setBikeRentalTime(int);

private:
    QSqlDatabase db;
    QSqlQuery query;
    int bikeID;
};

#endif // SQLCONNECTOR_H
