#ifndef SEMESTER_H
#define SEMESTER_H

#include "course.h"
#include <QString>
#include <QVector>

class Semester
{
private:
    int NOofSemester;
    QVector<course> listOfCourse;
    QString StartDate, EndDate;

public:
    void setStartDate(const QString& _StartDate);
    QString getStartDate();
    void setEndDate(const QString& _EndDate);
    QString getEndDate();
    void setNOofSemester(int _NOofSemester);
    int getNOofSemester();
    void setListofCourse(QVector<course> _listOfCourse);
    QVector<course>& getListOfCourse();
    Semester(int _NOofSemester = 0, const QString& _StartDate = "", const QString& _EndDate = "", QVector<course> _listOfCourse = QVector<course>());
    void AddaCourse(const course& Course);
    void RemoveCoursebyID(const QString& ID);
};

#endif // SEMESTER_H
