#ifndef CHECKUSER_H
#define CHECKUSER_H

#include <QString>
#include <string>

class checkUser
{
public:
    checkUser(QString, QString);
    ~checkUser();
    bool isAccountFound() const;

private:
    std::string name, password;
    QString generateHash(const char *data);

};

#endif // CHECKUSER_H
