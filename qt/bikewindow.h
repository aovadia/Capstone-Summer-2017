#ifndef BIKEWINDOW_H
#define BIKEWINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class bikeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit bikeWindow(QWidget *parent = 0);
    void setupBikeWindow();

private slots:
    void checkBikeID();

private:
    QLineEdit *editBikeID;
    QLabel *enterBikeID;
    QPushButton *acceptBikeID;
    QVBoxLayout *myQVBox;
    QVBoxLayout *myQVBox2;
    QHBoxLayout *myQHBox;
    QHBoxLayout *myQHBox4;
    int bikeID;

    void displayBikeInfo();
    void backToManagePage();
    QString setTimeOfUpdate();
};

#endif // BIKEWINDOW_H
