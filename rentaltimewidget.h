#ifndef RENTALTIMEWIDGET_H
#define RENTALTIMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QComboBox>
#include <QDialog>
#include <QtSql/QSqlQuery>
class rentalTimeWidget : public QWidget
{
    Q_OBJECT
public:
   explicit rentalTimeWidget();
    void setData(int);

private:
    QLabel *rentalTimeUpdateLbl;
    QVBoxLayout *myQVBox;
    QString getRentalTime();
    QComboBox *mComboBox;
    QDialog *mDialog;
};

#endif // RENTALTIMEWIDGET_H
