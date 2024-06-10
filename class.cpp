#include "class.h"
#include <iostream>

void Class::setClassName (const QString& _className){
    className=_className;
}
void Class::setListOfStudent (QVector<student> _list){
    listOfStudent=_list;
}
QString Class::getClassName (){
    return className;
}
QVector<student>& Class::getListOfStudent (){
    return listOfStudent;
}

void Class::AddnewStudent(const student& s)
{
    listOfStudent.push_back(s);
}

void Class::UpdateStudentFromCsv(const QString &path)
{
    QFile ifile(path);
    if (ifile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&ifile);
        while (!stream.atEnd()) {
            QString idStudent, firstName, lastName, gender, dateOfBirth, socialId, score;
            double gpa;

            QString textLine = stream.readLine();
            QStringList data = textLine.split(";");

            idStudent = data[0];
            firstName = data[1];
            lastName = data[2];
            gender = data[3];
            dateOfBirth = data[4];
            socialId = data[5];
            score = data[6];

            gpa = score.toDouble();
            student s(idStudent, firstName, lastName, gender, dateOfBirth, socialId, gpa);

            listOfStudent.append(s);
        }
    } else qDebug()<<"Khong mo duoc file";
}

void readClasses(const QString &path, QVector<Class> &list)
{
    QFile ifile (path);
    if (ifile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&ifile);
        QString lineData=stream.readLine().trimmed();
        QStringList data=lineData.split(";");
        int size= (data.at(0)).toInt();
        QVector<student> listStudents;
        for (int i=0;i<size;i++) {
            listStudents.clear();
            lineData=stream.readLine().trimmed();
            data=lineData.split(";");
            QString className=data.at(0);
            int cnt= (data.at(1)).toInt();
            for (int j=0;j<cnt;j++) {
                lineData=stream.readLine().trimmed();
                data=lineData.split(";");
                student x;
                x.setIdStudent(data.at(0));
                x.setFirstName(data.at(1));
                x.setLastName(data.at(2));
                x.setGender(data.at(3));
                x.setDateOfBirth(data.at(4));
                x.setSocialId(data.at(5));
                account ac;
                ac.setUsername(data.at(6));
                ac.setPassword(data.at(7));
                x.setStudentAccount(ac);
                x.setGpa(data.at(8).toDouble());
                int numsCourse=data.at(9).toInt();
                QVector<course> listCourses;
                for (int k=10;k<=10+(numsCourse-1)*5;k+=5) {
                    course tmp;
                    tmp.setClassName(data.at(k));
                    tmp.setTotal(data.at(k+1).toDouble());
                    tmp.setFinal(data.at(k+2).toDouble());
                    tmp.setMid(data.at(k+3).toDouble());
                    tmp.setOtherMark(data.at(k+4).toDouble());

                    listCourses.append(tmp);
                }
                x.setListOfCourses(listCourses);
                listStudents.append(x);
            }
            Class cls;
            cls.setClassName(className);
            cls.setListOfStudent(listStudents);
            list.append(cls);
        }
        ifile.close();
    }
    else qDebug()<<"Khong mo duoc file";
}
