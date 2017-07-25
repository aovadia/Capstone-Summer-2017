#ifndef BIKEHEALTH_H
#define BIKEHEALTH_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QProgressBar>
#include <QtSql/QSqlQuery>

class bikeHealth : public QWidget
{
    Q_OBJECT
public:
    explicit bikeHealth(int id);
    void setData(int);
    void sendQuery(QSqlQuery *);


private slots:
    void changeHealth();

private:
    int BikeId;
    QVBoxLayout *myQVBox;
    QSlider *healthSlider;
    QProgressBar *healthBar;
    void setHealth();
    QSqlQuery *query;

};

#endif // BIKEHEALTH_H
