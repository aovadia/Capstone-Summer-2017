#ifndef RENTALTIMEWIDGET_H
#define RENTALTIMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>

class rentalTimeWidget : public QWidget
{
    Q_OBJECT
public:
   explicit rentalTimeWidget();

private:
    QLabel *rentalTimeUpdateLbl;
    QVBoxLayout *myQVBox;
    QString getRentalTime();
};

#endif // RENTALTIMEWIDGET_H
