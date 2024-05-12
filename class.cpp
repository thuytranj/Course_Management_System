#include "class.h"

void Class::setClassName (const QString& _className){
    className=_className;
}
void Class::setListOfStudent (QVector<student> _list){
    listOfStudent=_list;
}
QString Class::getClassName (){
    return className;
}
QVector<student> Class::getListOfStudent (){
    return listOfStudent;
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
                for (int k=0;k<numsCourse;k++) {
                    course tmp;
                    tmp.setClassName(data.at(k+10));
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
