#ifndef BIKESERVICED_H
#define BIKESERVICED_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QtSql/QSqlQuery>
#include "bikehealth.h"

class bikeServiced : public QWidget
{
    Q_OBJECT
public:
    explicit bikeServiced(bikeHealth *);
    void setData(bool);
    void accessSql(QSqlQuery *, int);

private slots:
    void toggleInService();

private:
    QLabel *serviced;
    int bikeID;
    QSqlQuery *query;
    bool inService;
    QVBoxLayout *myQVBox;
    bikeHealth *myBikeHealth;

};

#endif // BIKESERVICED_H
