#ifndef CLASS_H
#define CLASS_H
#include "student.h"
#include <QVector>
#include <QtCore>
class Class
{
public:
    Class(const QString& _className="", QVector<student> _list=QVector<student> ()){
        className=_className;
        listOfStudent=_list;
    }

    void setClassName (const QString& _className);

    void setListOfStudent (QVector<student> _list);

    QString getClassName ();

    QVector <student>& getListOfStudent ();

    void AddnewStudent(const student& s);

    void UpdateStudentFromCsv(const QString &path);

private:
    QString className;

    QVector<student> listOfStudent;
};

void readClasses (const QString& path, QVector<Class>& list);

#endif // CLASS_H
