#ifndef BIKEHEALTH_H
#define BIKEHEALTH_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include <QProgressBar>

class bikeHealth : public QWidget
{
    Q_OBJECT
public:
    explicit bikeHealth();
    void setBikeServicedHealth(int);


private slots:
    void changeHealth();

private:
    QVBoxLayout *myQVBox;
    QSlider *healthSlider;
    QProgressBar *healthBar;
    void setHealth();

};

#endif // BIKEHEALTH_H
