#include "account.h"


void account::setUsername(const QString _username)
{
    username=_username;
}

void account::setPassword(const QString _password)
{
    password=_password;
}

QString account::getUsername()
{
    return username;
}

QString account::getPassword()
{
    return password;
}
