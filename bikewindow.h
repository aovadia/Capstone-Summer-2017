#ifndef BIKEWINDOW_H
#define BIKEWINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtSql/QSqlQuery>

class bikeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit bikeWindow(QWidget *parent = 0);
    void setupBikeWindow();
    void queryAccess(QSqlQuery *);
    void displayBikeInfo(int);


private slots:
    void checkBikeID();
    void openMapView();

private:
    QSqlQuery *query;
    QLineEdit *editBikeID;
    QLabel *enterBikeID;
    QPushButton *acceptBikeID;
    QVBoxLayout *myQVBox;
    QVBoxLayout *myQVBox2;
    QHBoxLayout *myQHBox;
    QHBoxLayout *myQHBox4;
    int bikeID;

    void backToManagePage();
    QString setTimeOfUpdate();
};

#endif // BIKEWINDOW_H
