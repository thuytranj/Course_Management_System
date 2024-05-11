#include "teacherinfo.h"

void teacherInfo::setFirstName (const QString& _firstName){
    firstName=_firstName;
}
void teacherInfo::setLastName (const QString& _lastName){
    lastName=_lastName;
}
void teacherInfo::setGender (const QString& _gender){
    gender=_gender;
}
void teacherInfo::setDateOfBirth (const QString& _dateOfBirth){
    dateOfBirth=_dateOfBirth;
}
void teacherInfo::setSocialId (const QString& _socialId){
    socialId=_socialId;
}
void teacherInfo::setEmail (const QString& _email){
    email=_email;
}

void teacherInfo::setTeacherAccount(account _teacherAccount)
{
    teacherAccount.setUsername(_teacherAccount.getUsername());
    teacherAccount.setPassword(_teacherAccount.getPassword());
}
QString teacherInfo::getFirstName (){
    return firstName;
}
QString teacherInfo::getLastName(){
    return lastName;
}
QString teacherInfo::getGender(){
    return gender;
}
QString teacherInfo::getDateOfBirth(){
    return dateOfBirth;
}
QString teacherInfo::getSocialId (){
    return socialId;
}
QString teacherInfo::getEmail(){
    return email;
}
account teacherInfo::getTeacherAccount(){
    return teacherAccount;
}

void readTeacherInfo(const QString &path, QVector<teacherInfo> &TeacherInfo)
{
    QFile ifile (path);
    if (ifile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&ifile);
        while (stream.atEnd()==false){
            QString lineData=stream.readLine().trimmed();
            QStringList data;
            bool inQuotes = false;
            QString field;

            for (const QChar &c : lineData) {
                if (c == '"') {
                    inQuotes = !inQuotes;
                } else if (c == ';' && !inQuotes) {
                    data.append(field.trimmed()); // Add field to data
                    field.clear(); // Clear field for next field
                } else {
                    field += c; // Add character to field
                }
            }
            data.append(field.trimmed());
            qDebug()<<data;
            if (data.size()==8) {
                teacherInfo x;
                account p;
                p.setUsername(data.at(0));
                p.setPassword(data.at(1));
                x.setTeacherAccount(p);
                x.setFirstName(data.at(2));
                x.setLastName(data.at(3));
                x.setGender(data.at(4));
                x.setDateOfBirth(data.at(5));
                x.setSocialId(data.at(6));
                x.setEmail(data.at(7));
                TeacherInfo.append (x);
            }
            else {
                qDebug()<<"Error: Incorrect number of fields in line in teacher file";
            }
        }
    }
}

bool isValidLogin(const QString &name, const QString &pass, QVector<teacherInfo> TeacherInfo, int &pos)
{
    for (int i=0;i<TeacherInfo.size();i++){
        if (TeacherInfo[i].getTeacherAccount().getUsername()==name && TeacherInfo[i].getTeacherAccount().getPassword()==pass){
            pos=i;
            return 1;
        }
    }
    pos=-1;
    return 0;
}
