#ifndef SCHOOLYEAR_H
#define SCHOOLYEAR_H

#include "semester.h"
#include <QString>
#include <QVector>

class SchoolYear
{
private:
    QString NameofSchoolYear;
    QVector<Semester> listOfSemester;
public:
    void setNameofSchoolYear(const QString& _NameofSchoolYear);
    QString getNameofSchoolYear();
    void setlistOfSemester(QVector<Semester> _listOfSemester);
    QVector<Semester>& getListOfSemester();
    SchoolYear(const QString& _NameofSchoolYear = "", QVector<Semester> _listOfSemester = QVector<Semester>());
};

#endif // SCHOOLYEAR_H
