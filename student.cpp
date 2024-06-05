#include "student.h"

void student::setIdStudent(const QString &_idStudent)
{
    idStudent=_idStudent;
}

void student::setFirstName (const QString& _firstName){
    firstName=_firstName;
}
void student::setLastName (const QString& _lastName){
    lastName=_lastName;
}
void student::setGender (const QString& _gender){
    gender=_gender;
}
void student::setDateOfBirth (const QString& _dateOfBirth){
    dateOfBirth=_dateOfBirth;
}
void student::setSocialId (const QString& _socialId){
    socialId=_socialId;
}

void student::setGpa(const double &_gpa)
{
    gpa=_gpa;
}

void student::setListOfCourses(QVector<course> _listOfCourse)
{
    listOfCourses=_listOfCourse;
}

QString student::getIdSudent()
{
    return idStudent;
}
void student::setStudentAccount(account _studentAccount)
{
    studentAccount.setUsername(_studentAccount.getUsername());
    studentAccount.setPassword(_studentAccount.getPassword());
}
QString student::getFirstName (){
    return firstName;
}
QString student::getLastName(){
    return lastName;
}
QString student::getGender(){
    return gender;
}
QString student::getDateOfBirth(){
    return dateOfBirth;
}
QString student::getSocialId (){
    return socialId;
}

double student::getGpa()
{
    return gpa;
}
account student::getStudentAccount(){
    return studentAccount;
}

QVector<course> &student::getListOfCourses()
{
    return listOfCourses;
}

QVector<student> readListStudent(const QString &path)
{
    QVector<student> list;
    QFile ifile (path);
    if (ifile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&ifile);
        while (stream.atEnd()==false){
            QString lineData=stream.readLine();
            QStringList data=lineData.split (";");
            if (data.size()==7) {
                student x;
                x.setIdStudent(data.at(1));
                x.setFirstName(data.at(2));
                x.setLastName(data.at(3));
                x.setGender(data.at(4));
                x.setDateOfBirth(data.at(5));
                x.setSocialId(data.at(6));
                list.append(x);
            }
            else {
                qDebug()<<"Error: Incorrect number of fields in line in classes file.";
            }
        }
        return list;
    }
    return list;
}

bool cmpIdStudent(student a, student b)
{
    return a.getIdSudent()<b.getIdSudent();
}

bool validLogin(const QString& name, const QString& pass, QVector<student> list, int& pos)
{
    for (int i=0;i<list.size();i++) {
        if (name==list[i].getStudentAccount().getUsername() && pass==list[i].getStudentAccount().getPassword()){
            pos=i;
            return true;
        }
    }
    return false;
}
