#include "checkuser.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QCryptographicHash>
#include <string>
#include <QMessageBox>

/* Constructor
 * Takes two QString values (a username and password)
 * Encrypts the entered 'mPassword' entry using sha256
 * Sets private membors 'name' and 'password'
 */
checkUser::checkUser(QString mName, QString *mPassword)
{
    name = mName.toStdString();
    QString encryptPass = generateHash(mPassword);
    password = encryptPass.toStdString();
}

/* PreCondition: string name, password are filled
 * Checks server to see if account is found
 * Return true if 'name' and 'password' is found in the server
 */
bool checkUser::isAccountFound() const {

    //  std::string name, password; check server against these values
    // return true if account is found using sql queries
    //return "63939540b5a5aadf20920ba5558ed7d089e265d48d16152d00fa47f5fe827d43" == password; //test for now
    bool found;
    std::string foundPwd;
    std::string statement = "SELECT Password FROM Users WHERE UserId = '";
    statement.append(name);
    statement.append("'");
    if (query->exec(QString::fromUtf8(statement.c_str()))) {
        query->next();
        if (query->value(0).toString() != NULL) {
          foundPwd = query->value(0).toString().toStdString();
          if (password == foundPwd) found = true;
        }
    }
    else {
        QMessageBox *serverErr = new QMessageBox();
        serverErr->setWindowTitle("Server Error");
        serverErr->setText("Try again in a few seconds");
        serverErr->show();
    }
return found;
}
// Encrypts 'char *' using sha256 hash algorithm
// Returns QString value in Hex format
QString checkUser::generateHash(QString *data) {
    QCryptographicHash *userPass = new QCryptographicHash(QCryptographicHash::Sha256);
    userPass->addData(data->toStdString().c_str(), strlen(data->toStdString().c_str()));
    qDebug() <<"generated pass: " <<userPass->result().toHex();
    return userPass->result().toHex();
}

void checkUser::queryAccess(QSqlQuery *a) {
    query = a;
}
