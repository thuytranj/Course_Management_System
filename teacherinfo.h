#ifndef TEACHERINFO_H
#define TEACHERINFO_H
#include "account.h"
#include <QtCore>
#include <QFile>
#include <QVector>

class teacherInfo
{
public:
    teacherInfo(const QString& _firstName="", const QString& _lastName="", const QString& _gender="", const QString& _dateOfBirth="", const QString& _socialId="", const QString& _email="", account _teacherAccount=account()){
        firstName=_firstName;
        lastName=_lastName;
        gender=_gender;
        dateOfBirth=_dateOfBirth;
        socialId=_socialId;
        email=_email;
        teacherAccount.setUsername(_teacherAccount.getUsername());
        teacherAccount.setPassword(_teacherAccount.getPassword());
    }

    void setFirstName (const QString& _firstName);

    void setLastName (const QString& _lastName);

    void setGender (const QString& _gender);

    void setDateOfBirth (const QString& _dateOfBirth);

    void setSocialId (const QString& _socialId);

    void setEmail (const QString& _email);

    void setTeacherAccount (account _teacherAccount);

    QString getFirstName ();

    QString getLastName();

    QString getGender();

    QString getDateOfBirth();

    QString getSocialId ();

    QString getEmail();

    account getTeacherAccount();
private:
    QString firstName, lastName, gender, dateOfBirth, socialId, email;
    account teacherAccount;
};
void readTeacherInfo (const QString &path, QVector<teacherInfo>& TeacherInfo);

bool isValidLogin (const QString& name, const QString& pass, QVector<teacherInfo> TeacherInfo, int& pos);
#endif // TEACHERINFO_H
