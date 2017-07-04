#ifndef CHECKINHISTORY_H
#define CHECKINHISTORY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
class checkInHistory : public QWidget
{
    Q_OBJECT
public:
    explicit checkInHistory(const int id);
    void testEnterCheckinData();

private slots:
    void copyCheckInData();

private:
    int bikeID;
    QVBoxLayout *myQVBox;
    QListWidget *myList;
    void enterCheckinData();
};

#endif // CHECKINHISTORY_H
