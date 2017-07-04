#ifndef BIKESERVICED_H
#define BIKESERVICED_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "bikehealth.h"

class bikeServiced : public QWidget
{
    Q_OBJECT
public:
    explicit bikeServiced(bikeHealth *);

private slots:
    void toggleInService();

private:
    QLabel *serviced;
    int bikeID;
    bool inService;
    QVBoxLayout *myQVBox;
    void checkInService();
    bikeHealth *myBikeHealth;

};

#endif // BIKESERVICED_H
