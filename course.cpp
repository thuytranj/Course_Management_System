#include "course.h"

void course::setIdCourse (const QString& _courseId){
    courseId=_courseId;
}
void course::setCourseName (const QString& _courseName){
    courseName=_courseName;
}
void course::setClassName (const QString& _className){
    className=_className;
}
void course::setTeacherName (const QString& _teacherName){
    teacherName=_teacherName;
}
void course::setDayOfWeek (const QString& _dateOfWeek){
    dayOfWeek=_dateOfWeek;
}
void course::setSession (const QString& _session){
    session=_session;
}
void course::setNumOfCredits (const int& credits){
    numOfCerdits=credits;
}
void course::setMaxStudent (const int& max){
    maxStudent=max;
}
void course::setTotal (const double& _total){
    total=_total;
}
void course::setFinal (const double& _final){
    final=_final;
}
void course::setMid (const double& _mid){
    mid=_mid;
}
void course::setOtherMark (const double& _otherMark){
    otherMark=_otherMark;
}

void course::setListOfStudent(QVector<QString> _listOfStudent)
{
    listOfStudents=_listOfStudent;
}
QString course::getCourseId (){
    return courseId;
}
QString course::getCourseName(){
    return courseName;
}
QString course::getClassName (){
    return className;
}
QString course::getTeacher(){
    return teacherName;
}
QString course::getDayOfWeek (){
    return dayOfWeek;
}
QString course::getSession (){
    return session;
}
int course::getNumOfCredits (){
    return numOfCerdits;
}
int course::getMaxStudent(){
    return maxStudent;
}
double course::getTotal (){
    return total;
}
double course::getFinal (){
    return final;
}
double course::getMid(){
    return mid;
}
double course::getOtherMark(){
    return otherMark;
}

QVector<QString>& course::getListOfStudent()
{
    return listOfStudents;
}

void course::AddaStudent(const QString& s)
{
    this->listOfStudents.push_back(s);
}

void course::RemoveStudentbyID(const QString& ID)
{
    int a = -1;
    for (int i = 0; i < listOfStudents.size(); i++) {
        if (listOfStudents[i] == ID) {
            a = i;
            break;
        }
    }
    listOfStudents.erase(listOfStudents.begin() + a);
}

void course::LoadStudentFromCsv(const QString &path) {
    QFile ifile(path);
    if (ifile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&ifile);
        while (!stream.atEnd()) {
            QString textLine = stream.readLine();
            QStringList data = textLine.split(";");

            QString idStudent = data[0];

            listOfStudents.append(idStudent);
        }
    } else qDebug()<<"Khong mo duoc file";
}

QVector<QString> readCourseInSemester(const QString &path, QVector<course> &list)
{
    QFile ifile (path);
    if (ifile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&ifile);
        QString lineData=stream.readLine().trimmed();
        QStringList data=lineData.split (";");
        QVector<QString> semester;
        semester.append(data.at(0));
        semester.append(data.at(1));
        semester.append(data.at(2));
        semester.append(data.at(3));
        while (stream.atEnd()==false){
            lineData=stream.readLine().trimmed();
            data=lineData.split (";");

            if (data.size()>=9) {
                course x;
                x.setIdCourse(data.at(0));
                x.setCourseName(data.at(1));
                x.setClassName(data.at(2));
                x.setTeacherName(data.at(3));
                x.setNumOfCredits(data.at(4).toInt());
                x.setMaxStudent(data.at(5).toInt());
                x.setDayOfWeek(data.at(6));
                x.setSession(data.at(7));
                int numStudents=data.at(8).toInt();
                QVector<QString> idStudent;
                for (int i=0;i<numStudents;i++) {
                    idStudent.append(data.at(i+9));
                }
                x.setListOfStudent(idStudent);
                list.append(x);
            }
            else {
                qDebug()<<"Error: Incorrect number of fields in line in semester file.";
            }
        }
        ifile.close();
        return semester;
    }
    return QVector<QString> ();
}
