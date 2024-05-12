#ifndef COURSE_H
#define COURSE_H

#include <QVector>
#include <QtCore>
#include <QFile>
class course
{
public:
    course(const QString& _courseId="", const QString _courseName="", const QString& _teacherName="", const QString& _className="", const int& _numOfCredits=0, const int& _maxStudent=50, const QString& _dayOfWeek="", const QString& _session="", const double& _total=0, const double& _final=0, const double& _mid=0, const double& _otherMark=0,  QVector<QString> _listOfStudent=QVector<QString> ()){
        courseId=_courseId;
        courseName=_courseName;
        teacherName=_teacherName;
        className=_className;
        numOfCerdits=_numOfCredits;
        maxStudent=_maxStudent;
        dayOfWeek=_dayOfWeek;
        session=_session;
        total=_total;
        final=_final;
        mid=_mid;
        otherMark=_otherMark;
        listOfStudents=_listOfStudent;
    }

    void setIdCourse (const QString& _courseId);

    void setCourseName (const QString& _courseName);

    void setClassName (const QString& _className);

    void setTeacherName (const QString& _teacherName);

    void setDayOfWeek (const QString& _dateOfWeek);

    void setSession (const QString& _session);

    void setNumOfCredits (const int& credits);

    void setMaxStudent (const int& max);

    void setTotal (const double& _total);

    void setFinal (const double& _final);

    void setMid (const double& _mid);

    void setOtherMark (const double& _otherMark);

    void setListOfStudent (QVector<QString> _listOfStudent);

    QString getCourseId ();

    QString getCourseName();

    QString getClassName ();

    QString getTeacher();

    QString getDayOfWeek ();

    QString getSession ();

    int getNumOfCredits ();

    int getMaxStudent();

    double getTotal ();

    double getFinal ();

    double getMid();

    double getOtherMark();

    QVector<QString> getListOfStudent ();

private:
    QString courseId, courseName, className, teacherName, dayOfWeek, session;
    int numOfCerdits, maxStudent;
    double total, final, mid, otherMark;
    QVector<QString> listOfStudents;
};

QVector<QString> readCourseInSemester (const QString& path, QVector<course> &list);
#endif // COURSE_H
