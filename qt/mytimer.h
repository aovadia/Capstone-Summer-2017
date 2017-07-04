#ifndef MYTIMER_H
#define MYTIMER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class myTimer : public QWidget
{
    Q_OBJECT

public:
    explicit myTimer();

public slots:
    void updateTimer();

private:
    QLabel *ElapsedTimeLbl;
    QLabel *tElapsedLbl;
    int setTimeElapsed();
    QVBoxLayout *myQVBox;
    int tElapsed;
};

#endif // MYTIMER_H
