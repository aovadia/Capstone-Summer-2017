#include "checkuser.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <QCryptographicHash>

/* Constructor
 * Takes two QString values (a username and password)
 * Encrypts the entered 'mPassword' entry using sha256
 * Sets private membors 'name' and 'password'
 */
checkUser::checkUser(QString mName, QString mPassword)
{
    name = mName.toStdString();
    const char * tempPass = mPassword.toStdString().c_str();
    QString encryptPass = generateHash(tempPass);
    password = encryptPass.toStdString();
}

/* PreCondition: string name, password are filled
 * Checks server to see if account is found
 * Return true if 'name' and 'password' is found in the server
 */
bool checkUser::isAccountFound() const {

    //  std::string name, password; check server against these values
    // return true if account is found using sql queries
    return "63939540b5a5aadf20920ba5558ed7d089e265d48d16152d00fa47f5fe827d43" == password; //test for now
}

// Encrypts 'char *' using sha256 hash algorithm
// Returns QString value in Hex format
QString checkUser::generateHash(const char *data) {
    QCryptographicHash *userPass = new QCryptographicHash(QCryptographicHash::Sha256);
    userPass->addData(data, strlen(data));
    qDebug() <<"generated pass: " <<userPass->result().toHex();
    return userPass->result().toHex();
}

