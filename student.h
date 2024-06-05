#ifndef STUDENT_H
#define STUDENT_H
#include "account.h"
#include <QVector>
#include "course.h"
#include <QtCore>

class student
{
public:
    //student () {}
    student(const QString& _idStudent="", const QString& _firstName="", const QString& _lastName="", const QString& _gender="", const QString& _dateOfBirth="", const QString& _socialId="", const double& _gpa=0, account _studentAccount=account (), QVector<course> _listOfCourses=QVector<course> ()) {
        idStudent=_idStudent;
        firstName=_firstName;
        lastName=_lastName;
        gender=_gender;
        dateOfBirth=_dateOfBirth;
        socialId=_socialId;
        gpa=_gpa;
        studentAccount.setUsername(_studentAccount.getUsername());
        studentAccount.setPassword(_studentAccount.getPassword());
        listOfCourses=_listOfCourses;
    }

    void setIdStudent (const QString& _idStudent);

    void setFirstName (const QString& _firstName);

    void setLastName (const QString& _lastName);

    void setGender (const QString& _gender);

    void setDateOfBirth (const QString& _dateOfBirth);

    void setSocialId (const QString& _socialId);

    void setStudentAccount (account _studentAccount);

    void setGpa (const double& _gpa);

    void setListOfCourses (QVector<course> _listOfCourse);

    QString getIdSudent();

    QString getFirstName ();

    QString getLastName();

    QString getGender();

    QString getDateOfBirth();

    QString getSocialId ();

    double getGpa();

    account getStudentAccount();

    QVector<course> &getListOfCourses ();

private:
    QString idStudent, firstName, lastName, gender, dateOfBirth, socialId;
    double gpa;
    account studentAccount;
    QVector<course> listOfCourses;

};
QVector<student> readListStudent (const QString& path);

bool cmpIdStudent (student a, student b);

bool validLogin (const QString& name, const QString& pass, QVector<student> list, int &pos);
#endif // STUDENT_H
