#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "checkuser.h"
#include "bikewindow.h"
#include "accountmanage.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString imgPath = ":/Res/Res/logo.jpg";
    QImage image(imgPath);
    ui->imgView->setPixmap(QPixmap::fromImage(image));

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("capstone-bikes.cphpxguj45gw.us-east-1.rds.amazonaws.com");
    db.setUserName("db_admin");
    db.setPassword("capstone");
    db.setPort(3306);
    db.setDatabaseName("Capstone_Bike_Shop");
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=15");
    if(!db.open()) {
           QSqlError err = db.lastError();
           qDebug() << err.text();
    }
     query = new QSqlQuery(db);
     //query->exec("INSERT INTO Master (BikeId, CheckedOut, Service, Distance, Health) VALUES (2, 0, 0, 0, 10);");
     connect(ui->usernameTxt, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_released);
     connect(ui->passwordTxt, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_released);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Quits application when Quit button is released
void MainWindow::on_cancelButton_released()
{
    QApplication::quit();
}


// Checks user entered account info when login button is pressed
void MainWindow::on_loginButton_released()
{
    checkUser *isUPValid = new checkUser(ui->usernameTxt->text(), ui->passwordTxt->text());
    isUPValid->queryAccess(query);
    if (isUPValid->isAccountFound()) {
        qDebug() <<"Success!";
        hide();
        accountManage *myManage = new accountManage();
        myManage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        myManage->queryAccess(query);
        myManage->show();
    } else { /* Display error message on status bar */
        ui->statusBar->showMessage("Invalid Username and/or Password!", 3000);
        ui->passwordTxt->clear();
    }
}
