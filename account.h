#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QString>
class account
{
public:
    account(const QString& _username ="", const QString _password="") {
        username=_username;
        password=_password;
    }

    void setUsername (const QString _username);

    void setPassword (const QString _password);

    QString getUsername ();

    QString getPassword ();

private:
    QString username, password;
};

#endif // ACCOUNT_H
