#include "initialscreen.h"
#include "mainwindow.h"

#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QMessageBox>

/*
 * Class used to create the initial view of our app upon executing
 * Setup the initialScreen widget layout
 */
initialScreen::initialScreen(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle("Capstone Bikes");
    QLabel *welcomeMessage =  new QLabel();
    QFont font("Arial",22,QFont::Bold);
    welcomeMessage->setText("Capstone Bikes");
    welcomeMessage->setFont(font);
    welcomeMessage->setAlignment(Qt::AlignHCenter);

    QLabel *version = new QLabel();
    version->setText("Release v1.0");
    version->setAlignment(Qt::AlignLeft);
    QVBoxLayout *myQVBox = new QVBoxLayout(this);

    myQVBox->addWidget(welcomeMessage);
    myQVBox->addWidget(version);

    QString imgPath = ":/Res/Res/logo.jpg";
    QImage image(imgPath);
    QLabel *logo = new QLabel();
    logo->setPixmap(QPixmap::fromImage(image));
    logo->setAlignment(Qt::AlignHCenter);
    myQVBox->addWidget(logo);

    QPushButton *manage = new QPushButton();
    manage->setText("Manage Bikes");
    myQVBox->addWidget(manage);

    QPushButton *aboutUs = new QPushButton();
    aboutUs->setText("About us");
    myQVBox->addWidget(aboutUs);

    // Connect button widgets to a handler function
    connect(manage, &QPushButton::released, this, &initialScreen::manageBikes);
    connect(aboutUs, &QPushButton::released, this, &initialScreen::displayAboutUs);
    this->setFixedSize(this->width(), this->height());
}

/*
 * Function to handle when the 'manage' button is pressed.
 * Instantiate 'MainWindow' class to login
 */
void initialScreen::manageBikes() {

    MainWindow *main = new MainWindow;
    close(); // Close initialScreen
    main->show();
}

/*
 * Function to handle when the 'aboutUs' button is pressed.
 * Display a popup information with our names
 */
void initialScreen::displayAboutUs() const {
    QMessageBox *us = new QMessageBox();
    QString project("Bike rental service created for our capstone class\n\n");
    us->setText(project + "Adam Ovadia\nLiam Hayes\nPhillip Gornstein\nTasdique Chowdhury\nVlad Shostak");
    us->show();
}
