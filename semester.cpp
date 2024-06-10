#include "semester.h"

void Semester::setStartDate(const QString& _StartDate)
{
    this->StartDate = _StartDate;
}

QString Semester::getStartDate()
{
    return this->StartDate;
}

void Semester::setEndDate(const QString& _EndDate)
{
    this->EndDate = _EndDate;
}

QString Semester::getEndDate()
{
    return this->EndDate;
}

void Semester::setNOofSemester(int _NOofSemester)
{
    this->NOofSemester = _NOofSemester;
}
int Semester::getNOofSemester()
{
    return this->NOofSemester;
}

void Semester::setListofCourse(QVector<course> _listOfCourse)
{
    this->listOfCourse = _listOfCourse;
}

QVector<course>& Semester::getListOfCourse()
{
    return this->listOfCourse;
}

Semester::Semester(int _NOofSemester, const QString& _StartDate, const QString& _EndDate, QVector<course> _listOfCourse)
{
    this->NOofSemester = _NOofSemester;
    this->StartDate = _StartDate;
    this->EndDate = _EndDate;
    this->listOfCourse = _listOfCourse;
}

void Semester::AddaCourse(const course& Course)
{
    this->listOfCourse.push_back(Course);
}

void Semester::RemoveCoursebyID(const QString& ID)
{
    int a = 0;
    for (int i = 0; i < listOfCourse.size(); i++) {
        if (listOfCourse[i].getCourseId() == ID) {
            a = i;
            break;
        }
    }
    listOfCourse.erase(listOfCourse.begin() + a);
}
