#include "schoolyear.h"

void SchoolYear::setNameofSchoolYear(const QString& _NameofSchoolYear)
{
    this->NameofSchoolYear = _NameofSchoolYear;
}

QString SchoolYear::getNameofSchoolYear()
{
    return this->NameofSchoolYear;
}

void SchoolYear::setlistOfSemester(QVector<Semester> _listOfSemester)
{
    this->listOfSemester = _listOfSemester;
}

QVector<Semester>& SchoolYear::getListOfSemester()
{
    return this->listOfSemester;
}

SchoolYear::SchoolYear(const QString& _NameofSchoolYear, QVector<Semester> _listOfSemester)
{
    this->NameofSchoolYear = _NameofSchoolYear;
    this->listOfSemester = _listOfSemester;
}

