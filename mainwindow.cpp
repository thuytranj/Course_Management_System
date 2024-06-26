#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


void MainWindow::setTeacherInfos(QVector<teacherInfo> _TeacherInfo)
{
    TeacherInfo=_TeacherInfo;
}

void MainWindow::setPosTeacherUser(const int &_pos)
{
    posTeacherUser=_pos;
}

QVector<teacherInfo> MainWindow::getTeacherInfos() const
{
    return TeacherInfo;
}

int MainWindow::getPosTeacherUser()
{
    return posTeacherUser;
}

void MainWindow::setListOfClass(QVector<Class> _list)
{
    listOfClass=_list;
}

QVector<Class>& MainWindow::getListOfClass()
{
    return listOfClass;
}
void MainWindow::setListOfCourse (QVector<course> list){
    listOfCourse=list;
}
QVector<course>& MainWindow::getListOfCourse (){
    return listOfCourse;
}
void MainWindow::setKindOfSemester (const QString& _kindOfSemester){
    kindOfSemester=_kindOfSemester;
}
void MainWindow::setSchoolYear (const QString& _schoolYear){
    schoolYear=_schoolYear;
}
void MainWindow::setStartDate (const QString& _startDate){
    startDate=_startDate;
}
void MainWindow::setEndDate (const QString& _endDate){
    endDate=_endDate;
}
QString MainWindow::getKindOfSemester (){
    return kindOfSemester;
}
QString MainWindow::getSchoolYear (){
    return schoolYear;
}
QString MainWindow::getStartDate(){
    return startDate;
}
QString MainWindow::getEndDate(){
    return endDate;
}
void MainWindow::setPosNoStudent (const int& pos){
    posNoStudent=pos;
}

void MainWindow::setPosClassStudent (const int& pos){
    posClassStudent=pos;
}

int MainWindow::getPosNoStudent (){
    return posNoStudent;
}

int MainWindow::getPosClassStudent (){
    return posClassStudent;
}

course MainWindow::findCourse(const QString &name, QVector<course> list)
{
    for (int i=0;i<list.size();i++) {
        if (name==list[i].getClassName()) {
            return list[i];
        }
    }
    QMessageBox::warning(this, "Khoá học", "Khoá học không tồn tại!");
    return course ();
}

void MainWindow::findIndexStudent(const QString &id, int& posClass, int& pos)
{
    QVector<Class> list=getListOfClass();
    for (int i=0;i<list.size();i++) {
        QVector<student> listStudent=list[i].getListOfStudent();
        std::sort (listStudent.begin(), listStudent.end(), cmpIdStudent);
        if (listStudent[0].getIdSudent()==id) {
            pos=0;
            posClass=i;
            return;
        }
        else if (listStudent[listStudent.size()-1].getIdSudent()==id) {
            pos=listStudent.size()-1;
            posClass=i;
            return;
        }
        else if (listStudent[0].getIdSudent()<id && listStudent[listStudent.size()-1].getIdSudent()>id) {
            int l=0, r=listStudent.size()-1;
            while (l<=r) {
                int m=(l+r)/2;
                if (listStudent[m].getIdSudent()==id) {
                    pos=m;
                    posClass=i;
                    return;
                }
                else if (listStudent[m].getIdSudent()<id) l=m+1;
                else r=m-1;
            }
        }
    }
}

int MainWindow::findIndexCourse(const QString &className, QVector<course> list)
{
    for (int i=0;i<list.size();i++) {
        if (className==list[i].getClassName()) return i;
    }
    return -1;
}

double MainWindow::gpa(student x)
{
    double sum=0;
    int cnt=0;
    QVector<course> list=x.getListOfCourses();
    for (int i=0;i<list.size();i++) {
        sum+=list[i].getTotal()*list[i].getNumOfCredits();
        cnt+=list[i].getNumOfCredits();
    }
    return sum/cnt;
}

int MainWindow::findIndexClass(const QString &nameClass, QVector<Class> list)
{
    for (int i=0;i<list.size();i++) {
        if (nameClass==list[i].getClassName()) return i;
    }
    return -1;
}

bool MainWindow::isTeacher()
{
    return teacher;
}

void MainWindow::setTeacher(const bool &t)
{
    teacher=t;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Tên đăng nhập");
    ui->password->setPlaceholderText("Mật khẩu");
    QVector<Class> classInSemester;
    readClasses ("/Users/thuytran/Documents/Course_Management_System/build/Qt_6_7_1_for_macOS-Debug/database/classes.csv", classInSemester);
    QVector<course> courseInSemester;
    QVector<QString> semester = readCourseInSemester("/Users/thuytran/Documents/Course_Management_System/build/Qt_6_7_1_for_macOS-Debug/database/semester.csv", courseInSemester);
    setListOfClass(classInSemester);
    setListOfCourse(courseInSemester);
    setKindOfSemester(semester[0]);
    setSchoolYear(semester[1]);
    setStartDate(semester[2]);
    setEndDate(semester[3]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_teacher_clicked()
{
    QVector<teacherInfo> TeacherInfo=getTeacherInfos();
    if (TeacherInfo.size()==0) {
        readTeacherInfo("/Users/thuytran/Documents/Course_Management_System/build/Qt_6_7_1_for_macOS-Debug/database/Teacher.csv", TeacherInfo);
        setTeacherInfos (TeacherInfo);
    }
    int pos=-1;
    QString name=ui->username->text();
    QString pass=ui->password->text();
    if (isValidLogin(name, pass, TeacherInfo, pos)) {
        setPosTeacherUser(pos);
        ui->stackedWidget->setCurrentIndex(1);
        setTeacher(1);
    }
    else {
        QMessageBox::warning(this, "Đăng nhập", "Tài khoản hoặc mật khẩu không hợp lệ!");
    }
}


void MainWindow::on_account_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QVector<teacherInfo> cur = getTeacherInfos();
    int pos=getPosTeacherUser();
    ui->firstName->setText(cur[pos].getFirstName());
    ui->lastName->setText(cur[pos].getLastName());
    ui->gender->setText(cur[pos].getGender());
    ui->dateOfBirth->setText(cur[pos].getDateOfBirth());
    ui->socialId->setText(cur[pos].getSocialId());
    ui->email->setText(cur[pos].getEmail());
    ui->username_2->setText(cur[pos].getTeacherAccount().getUsername());
}


void MainWindow::on_home_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_changePass_clicked()
{
    QString newPassword=ui->newPass->text();
    QString confirm=ui->comfirmPass->text();
    if (newPassword!=confirm) {
        QMessageBox::warning(this, "Đổi mật khẩu", "Mật khẩu xác nhận không trùng khớp!");
        return;
    }
    if (isTeacher()) {
        int pos=getPosTeacherUser();
        QVector <teacherInfo> list=getTeacherInfos();
        account x=list[pos].getTeacherAccount();
        x.setPassword(newPassword);
        list[pos].setTeacherAccount(x);
        setTeacherInfos(list);
    }
    else {
        int posClass=getPosClassStudent();
        int pos=getPosNoStudent();
        QVector<Class> list=getListOfClass();
        account x=list[posClass].getListOfStudent()[pos].getStudentAccount();
        x.setPassword(newPassword);
        list[posClass].getListOfStudent()[pos].setStudentAccount(x);
        setListOfClass(list);
    }
    QMessageBox::warning(this, "Đổi mật khẩu", "Đổi mật khẩu thành công!");
}


void MainWindow::on_logOut_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_schoolYear_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(0);
    QString year=getSchoolYear();
    QString kindSemester=getKindOfSemester();
    QString StartDate=getStartDate();
    QString EndDate=getEndDate();
    ui->schoolYear_4->setText(year);
    ui->semester->setText(kindSemester);
    ui->startDate->setText(StartDate);
    ui->endDate->setText(EndDate);
    QVector<Class> lstClass=getListOfClass();
    ui->table_class->setColumnWidth(0, 300);
    ui->table_class->setColumnWidth(1, 300);
    ui->table_class->setRowCount(lstClass.size());
    for (int i=0;i<lstClass.size();i++) {
        ui->table_class->setItem(i, 0, new QTableWidgetItem(lstClass[i].getClassName()));
        ui->table_class->setItem(i, 1, new QTableWidgetItem(QString::number(lstClass[i].getListOfStudent().size())));
    }
}


void MainWindow::on_listClasses_clicked()
{
    //ui->stackedWidget_2->setCurrentIndex(0);
    on_schoolYear_clicked();
}


void MainWindow::on_listStudentInClass_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_find_clicked()
{
    QString name=ui->className->text();
    QVector<Class> classInSemester=getListOfClass();
    for (int i=0;i<classInSemester.size();i++){
        if (name==classInSemester[i].getClassName()) {
            //set width column
            QVector<student> list=classInSemester[i].getListOfStudent();
            ui->tableStudents->setRowCount (list.size());
            for (int j=0;j<list.size();j++) {
                ui->tableStudents->setItem (j, 0, new QTableWidgetItem (list[j].getIdSudent()));
                ui->tableStudents->setItem (j, 1, new QTableWidgetItem (list[j].getFirstName()));
                ui->tableStudents->setItem (j, 2, new QTableWidgetItem (list[j].getLastName()));
                ui->tableStudents->setItem (j, 3, new QTableWidgetItem (list[j].getGender()));
                ui->tableStudents->setItem (j, 4, new QTableWidgetItem (list[j].getDateOfBirth()));
                ui->tableStudents->setItem (j, 5, new QTableWidgetItem (list[j].getSocialId()));
            }
            return;
        }
    }
    QMessageBox::information(this, "Tìm lớp", "Không tồn tại lớp trong học kì!");
}


void MainWindow::on_home_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_account_3_clicked()
{
    on_account_clicked();
}


void MainWindow::on_account_2_clicked()
{
    on_account_clicked();
}


void MainWindow::on_schoolYear_2_clicked()
{
    on_schoolYear_clicked();
}


void MainWindow::on_listClasses_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
    QVector<course> list=getListOfCourse();
    ui->tableCourse->setRowCount (list.size());
    qDebug()<<list.size();
    for (int i=0;i<list.size();i++) {
        ui->tableCourse->setItem(i, 0, new QTableWidgetItem(list[i].getCourseId()));
        ui->tableCourse->setItem(i, 1, new QTableWidgetItem(list[i].getCourseName()));
        ui->tableCourse->setItem(i, 2, new QTableWidgetItem(list[i].getClassName()));
        ui->tableCourse->setItem(i, 3, new QTableWidgetItem(list[i].getTeacher()));
        ui->tableCourse->setItem(i, 4, new QTableWidgetItem(QString::number(list[i].getNumOfCredits())));
        ui->tableCourse->setItem(i, 5, new QTableWidgetItem(list[i].getDayOfWeek() + " " + list[i].getSession()));
    }
}

void MainWindow::on_course_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    on_listClasses_2_clicked();
    QString year=getSchoolYear();
    QString kindSemester=getKindOfSemester();
    QString StartDate=getStartDate();
    QString EndDate=getEndDate();
    ui->schoolYear_6->setText(year);
    ui->semester_2->setText(kindSemester);
    ui->startDate_2->setText(StartDate);
    ui->endDate_2->setText(EndDate);
}

void MainWindow::on_course_2_clicked()
{
    on_course_clicked();
}


void MainWindow::on_course_3_clicked()
{
    on_course_clicked();
}


void MainWindow::on_home_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_account_4_clicked()
{
    on_account_clicked();
}


void MainWindow::on_schoolYear_5_clicked()
{
    on_schoolYear_clicked();
}


void MainWindow::on_logOut_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

student MainWindow::findStudent(const QString &id)
{
    QVector<Class> list=getListOfClass();
    for (int i=0;i<list.size();i++) {
        QVector<student> listStudent=list[i].getListOfStudent();
        std::sort (listStudent.begin(), listStudent.end(), cmpIdStudent);
        if (listStudent[0].getIdSudent()==id) return listStudent[0];
        else if (listStudent[listStudent.size()-1].getIdSudent()==id) return listStudent[listStudent.size()-1];
        else if (listStudent[0].getIdSudent()<id && listStudent[listStudent.size()-1].getIdSudent()>id) {
            int l=0, r=listStudent.size()-1;
            while (l<=r) {
                int m=(l+r)/2;
                if (listStudent[m].getIdSudent()==id) return listStudent[m];
                else if (listStudent[m].getIdSudent()<id) l=m+1;
                else r=m-1;
            }
        }
    }
    QMessageBox::information(this, "Sinh viên", "Không tồn tại sinh viên này trong học kì!");
    return student();
}

void MainWindow::on_listStudentInClass_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    ui->className_2->setText(ui->className_3->text());
    ui->tableStudenInCourse->setColumnWidth(0, 100);
    ui->tableStudenInCourse->setColumnWidth(1, 200);
    ui->tableStudenInCourse->setColumnWidth(2, 100);
    ui->tableStudenInCourse->setColumnWidth(3, 100);
    ui->tableStudenInCourse->setColumnWidth(4, 100);
    QString name=ui->className_3->text();
    QVector<course> listCourse=getListOfCourse();
    for (int i=0;i<listCourse.size();i++) {
        if (name==listCourse[i].getClassName()) {
            QVector<QString> list=listCourse[i].getListOfStudent();
            ui->tableStudenInCourse->setRowCount(list.size());
            for (int j=0;j<list.size();j++) {
                student x=findStudent(list[j]);
                ui->tableStudenInCourse->setItem(j, 0, new QTableWidgetItem(x.getIdSudent()));
                ui->tableStudenInCourse->setItem(j, 1, new QTableWidgetItem(x.getFirstName()));
                ui->tableStudenInCourse->setItem(j, 2, new QTableWidgetItem(x.getLastName()));
                ui->tableStudenInCourse->setItem(j, 3, new QTableWidgetItem(x.getGender()));
                ui->tableStudenInCourse->setItem(j, 4, new QTableWidgetItem(x.getDateOfBirth()));
            }
            return;
        }
    }
    QMessageBox::information(this, "Khoá học", "Không tồn tại khoá học này trong học kì!");
}

void MainWindow::on_newSemester_3_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
}


void MainWindow::on_findCourse_clicked()
{
    QString name=ui->className_3->text();
    QVector<course> list=getListOfCourse();
    for (int i=0;i<list.size();i++) {
        if (name==list[i].getClassName()) {
            ui->idCourse->setText (list[i].getCourseId());
            ui->courseName->setText(list[i].getCourseName());
            ui->className_4->setText (list[i].getClassName());
            ui->teacherName->setText (list[i].getTeacher());
            ui->credits->setText (QString::number(list[i].getNumOfCredits()));
            ui->time->setText (list[i].getDayOfWeek() + ' ' + list[i].getSession());
            ui->maxStudents->setText (QString::number(list[i].getMaxStudent()));
            ui->enrolledStudent->setText (QString::number(list[i].getListOfStudent().size()));
            return;
        }
    }
    QMessageBox::information(this, "Khoá học", "Không tồn tại khoá học này trong học kì!");
}



void MainWindow::on_back_clicked()
{
    if (isTeacher()) ui->stackedWidget->setCurrentIndex(2);
    else ui->stackedWidget->setCurrentIndex(6);
}

bool MainWindow::loginStudent(const QString &name, const QString &pass, QVector<Class> list, int &posNo, int &posClass)
{
    for (int i=0;i<list.size();i++) {
        QVector<student> listStudent=list[i].getListOfStudent();
        if (validLogin(name, pass, listStudent, posNo)) {
            posClass=i;
            setPosNoStudent(posNo);
            setPosClassStudent(posClass);
            return true;
        }
    }
    return false;
}

void MainWindow::on_student_clicked()
{
    QVector<Class> list = getListOfClass();
    QString name=ui->username->text();
    QString pass=ui->password->text();
    int pos=-1, posClass=-1;
    if (loginStudent(name, pass, list, pos, posClass)) {
        ui->stackedWidget->setCurrentIndex(6);
        ui->stackedWidget_4->setCurrentIndex(0);
        QVector <course> listCourse=getListOfCourse();
        for (int i=0;i<list[posClass].getListOfStudent()[pos].getListOfCourses().size();i++){
            course x=findCourse (list[posClass].getListOfStudent()[pos].getListOfCourses()[i].getClassName(), listCourse);
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setCourseName(x.getCourseName());
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setDayOfWeek(x.getDayOfWeek());
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setIdCourse(x.getCourseId());
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setListOfStudent(x.getListOfStudent());
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setMaxStudent(x.getMaxStudent());
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setNumOfCredits(x.getNumOfCredits());
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setSession(x.getSession());
            list[posClass].getListOfStudent()[pos].getListOfCourses()[i].setTeacherName(x.getTeacher());
        }
        setListOfClass(list);
        setTeacher(0);
        return;
    }
    QMessageBox::warning(this, "Đăng nhập", "Tài khoản hoặc mật khẩu không hợp lệ!");
}

void MainWindow::on_account_Student_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
    int classPos=getPosClassStudent();
    int noPos=getPosNoStudent();
    QVector<Class> list=getListOfClass();
    ui->username_3->setText(list[classPos].getListOfStudent()[noPos].getStudentAccount().getUsername());
    ui->firstName_2->setText(list[classPos].getListOfStudent()[noPos].getFirstName());
    ui->lastName_2->setText(list[classPos].getListOfStudent()[noPos].getLastName());
    ui->gender_2->setText(list[classPos].getListOfStudent()[noPos].getGender());
    ui->dateOfBirth_2->setText(list[classPos].getListOfStudent()[noPos].getDateOfBirth());
    ui->socialId_2->setText(list[classPos].getListOfStudent()[noPos].getSocialId());
    ui->idStudent->setText(list[classPos].getListOfStudent()[noPos].getIdSudent());
}


void MainWindow::on_logOut_5_clicked()
{
    on_logOut_2_clicked();
}


void MainWindow::on_schedule_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
    int classPos=getPosClassStudent();
    int noPos=getPosNoStudent();
    QVector<course> list=getListOfClass()[classPos].getListOfStudent()[noPos].getListOfCourses();
    ui->schedule_2->setRowCount(list.size());
    for (int i=0;i<list.size();i++) {
        ui->schedule_2->setItem(i, 0, new QTableWidgetItem(list[i].getCourseId()));
        ui->schedule_2->setItem(i, 1, new QTableWidgetItem(list[i].getCourseName()));
        ui->schedule_2->setItem(i, 2, new QTableWidgetItem(list[i].getClassName()));
        ui->schedule_2->setItem(i, 3, new QTableWidgetItem(list[i].getTeacher()));
        ui->schedule_2->setItem(i, 4, new QTableWidgetItem(QString::number(list[i].getNumOfCredits())));
        ui->schedule_2->setItem(i, 5, new QTableWidgetItem(list[i].getDayOfWeek() + " " + list[i].getSession()));
    }
}

void MainWindow::on_outputList_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Select Folder", QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString name=ui->className_3->text();
    QVector<course> listCourse=getListOfCourse();
    QString filePath=folderPath+"/"+name+".csv";
    QFile file (filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream stream (&file);
        for (int i=0;i<listCourse.size();i++){
            if (name==listCourse[i].getClassName()) {
                QVector<QString> list=listCourse[i].getListOfStudent();
                for (int j=0;j<list.size();j++) {
                    student x=findStudent(list[j]);
                    stream <<x.getIdSudent()<<";"
                           <<x.getFirstName()<<";"
                           <<x.getLastName()<<";"
                           <<x.getGender()<<";"
                           <<x.getDateOfBirth()<<";"
                           <<x.getSocialId()<<"\n";
                }
                break;
            }
        }
    }
    file.close();
}



void MainWindow::on_importFile_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)){
        QString className=ui->className_3->text();
        QTextStream stream(&file);
        QString lineData;
        QVector<Class> list=getListOfClass();
        course x=findCourse (className, getListOfCourse());
        while (stream.atEnd()==false){
            lineData=stream.readLine().trimmed();
            QStringList data=lineData.split(";");
            QString id=data.at(1);
            int posClass=-1, pos=-1;
            findIndexStudent(id, posClass, pos);
            if (posClass!=-1 && pos!=-1) {
                int posCourse = findIndexCourse(className, list[posClass].getListOfStudent()[pos].getListOfCourses());
                if (posCourse!=-1) {
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setCourseName(x.getCourseName());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setIdCourse(x.getCourseId());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setNumOfCredits(x.getNumOfCredits());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setTeacherName(x.getTeacher());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setNumOfCredits(x.getNumOfCredits());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setTotal(data.at(4).toDouble());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setFinal(data.at(5).toDouble());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setMid(data.at(6).toDouble());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setOtherMark(data.at(7).toDouble());
                }
            }

        }
        setListOfClass(list);
        file.close();
        QMessageBox::information(this, "Cập nhật", "Cập nhật điểm thành công!");
    }
}


void MainWindow::on_viewScoreBoard_clicked()
{
    QString className=ui->className_3->text();
    course x=findCourse (className, getListOfCourse());
    ui->stackedWidget_3->setCurrentIndex(3);
    ui->scoreboard->setColumnWidth(0, 100);
    ui->scoreboard->setColumnWidth(1, 200);
    ui->scoreboard->setColumnWidth(2, 100);
    ui->scoreboard->setColumnWidth(3, 100);
    ui->scoreboard->setColumnWidth(4, 100);
    ui->scoreboard->setColumnWidth(5, 100);
    ui->scoreboard->setColumnWidth(6, 100);

    QVector<QString> list=x.getListOfStudent();
    ui->scoreboard->setRowCount (list.size());
    for (int i=0;i<list.size();i++) {
        student stu=findStudent(list[i]);
        QVector<course> list=stu.getListOfCourses();
        int pos=findIndexCourse(className, list);
        if (pos<0 || pos>=list.size()) {
            QMessageBox::warning(this, "Error", "Error!");
            return;
        }

        ui->scoreboard->setItem(i, 0, new QTableWidgetItem(stu.getIdSudent()));
        ui->scoreboard->setItem(i, 1, new QTableWidgetItem(stu.getFirstName()));
        ui->scoreboard->setItem(i, 2, new QTableWidgetItem(stu.getLastName()));
        ui->scoreboard->setItem(i, 3, new QTableWidgetItem(QString::number(list[pos].getTotal(), 'f', 2)));
        ui->scoreboard->setItem(i, 4, new QTableWidgetItem(QString::number(list[pos].getFinal(), 'f', 2)));
        ui->scoreboard->setItem(i, 5, new QTableWidgetItem(QString::number(list[pos].getMid(), 'f', 2)));
        ui->scoreboard->setItem(i, 6, new QTableWidgetItem(QString::number(list[pos].getOtherMark(), 'f',2)));
    }
}


void MainWindow::on_viewScoreboard_clicked(){
    ui->stackedWidget_2->setCurrentIndex(2);
    ui->gpaClass->setColumnWidth(0, 100);
    ui->gpaClass->setColumnWidth(1, 200);
    ui->gpaClass->setColumnWidth(2, 100);
    ui->gpaClass->setColumnWidth(3, 200);
    QString className=ui->className->text();
    QVector<Class> list=getListOfClass();

    int posClass=findIndexClass(className, list);
    if (posClass!=-1) {
        ui->gpaClass->setRowCount (list[posClass].getListOfStudent().size());
        for (int i=0;i<list[posClass].getListOfStudent().size();i++) {
            ui->gpaClass->setItem(i, 0, new QTableWidgetItem(list[posClass].getListOfStudent()[i].getIdSudent()));
            ui->gpaClass->setItem(i, 1, new QTableWidgetItem(list[posClass].getListOfStudent()[i].getFirstName()));
            ui->gpaClass->setItem(i, 2, new QTableWidgetItem(list[posClass].getListOfStudent()[i].getLastName()));
            list[posClass].getListOfStudent()[i].setGpa(gpa (list[posClass].getListOfStudent()[i]));
            ui->gpaClass->setItem(i, 3, new QTableWidgetItem(QString::number(list[posClass].getListOfStudent()[i].getGpa(), 'f', 2)));
        }
        setListOfClass(list);
    }
    else QMessageBox::warning(this, "Lớp học", "Không tồn tại lớp trong học kì này!");
}


void MainWindow::on_viewMore_clicked(){
    ui->stackedWidget_2->setCurrentIndex(3);
}


void MainWindow::on_viewStudentScoreboard_clicked(){
    QString id=ui->idStudent_2->text();
    student s=findStudent(id);
    QVector<course> list=s.getListOfCourses();
    ui->studentScoreboard->setRowCount (list.size());
    for (int i=0;i<list.size();i++) {
        ui->studentScoreboard->setItem(i, 0, new QTableWidgetItem(list[i].getCourseName()));
        ui->studentScoreboard->setItem(i, 1, new QTableWidgetItem(list[i].getCourseId()));
        ui->studentScoreboard->setItem(i, 2, new QTableWidgetItem(QString::number(list[i].getNumOfCredits())));
        ui->studentScoreboard->setItem(i, 3, new QTableWidgetItem(list[i].getClassName()));
        ui->studentScoreboard->setItem(i, 4, new QTableWidgetItem(list[i].getTeacher()));
        ui->studentScoreboard->setItem(i, 5, new QTableWidgetItem(QString::number(list[i].getFinal(), 'f', 2)));
    }
}


void MainWindow::on_home_5_clicked(){
    ui->stackedWidget_4->setCurrentIndex(0);
}


void MainWindow::on_summary_clicked(){
    ui->stackedWidget_4->setCurrentIndex(3);
    ui->schoolYear_7->setText (getSchoolYear());
    ui->semester_3->setText (getKindOfSemester());
    ui->startDate_3->setText(getStartDate());
    ui->endDate_4->setText (getEndDate());
    int posClass=getPosClassStudent();
    int pos=getPosNoStudent();
    QVector<Class> list=getListOfClass();
    //if (list[posClass].getListOfStudent()[pos].getGpa()==0) {
        list[posClass].getListOfStudent()[pos].setGpa(gpa (list[posClass].getListOfStudent()[pos]));
        setListOfClass(list);
    //}
    QVector<course> x=list[posClass].getListOfStudent()[pos].getListOfCourses();
    ui->gpa->setText(QString::number(list[posClass].getListOfStudent()[pos].getGpa(),'f',2));
    ui->scoreboard_2->setRowCount(x.size());
    for (int i=0;i<x.size();i++){
        ui->scoreboard_2->setItem (i, 0, new QTableWidgetItem (x[i].getCourseId()));
        ui->scoreboard_2->setItem (i, 1, new QTableWidgetItem (x[i].getCourseName()));
        ui->scoreboard_2->setItem (i, 2, new QTableWidgetItem (QString::number(x[i].getTotal(), 'f', 2) ));
        ui->scoreboard_2->setItem (i, 3, new QTableWidgetItem (QString::number(x[i].getFinal(), 'f', 2)));
        ui->scoreboard_2->setItem (i, 4, new QTableWidgetItem (QString::number(x[i].getMid(), 'f', 2)));
        ui->scoreboard_2->setItem (i, 5, new QTableWidgetItem (QString::number(x[i].getOtherMark(),  'f', 2)));
    }
}

void MainWindow::on_changePassword_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_logOut_3_clicked(){
    on_logOut_2_clicked();
}

void MainWindow::on_logOut_clicked()
{
    on_logOut_2_clicked();
}


void MainWindow::on_newAccount_2_clicked()
{
    QString firstName=ui->firstName_3->text();
    if (firstName=="") {
        QMessageBox::warning(this, "Thông báo", "Họ không được để trống");
        return;
    }
    QString lastName=ui->lastName_3->text();
    if (lastName=="") {
        QMessageBox::warning(this, "Thông báo", "Tên không được để trống");
        return;
    }
    QString gender=ui->gender_3->text();
    if (gender=="") {
        QMessageBox::warning(this, "Thông báo", "Giới tính không được để trống");
        return;
    }
    QString dateOfBirth=ui->dateOfBirth_3->text();
    if (dateOfBirth=="") {
        QMessageBox::warning(this, "Thông báo", "Ngày sinh không được để trống");
        return;
    }
    QString socialId=ui->socialId_3->text();
    if (socialId=="") {
        QMessageBox::warning(this, "Thông báo", "CCCD không được để trống");
        return;
    }
    QString email=ui->email_2->text();
    if (email==""){
        QMessageBox::warning(this, "Thông báo", "Email không được để trống");
        return;
    }
    QString userName=ui->username_4->text();
    if (userName=="") {
        QMessageBox::warning(this, "Thông báo", "Tên đăng nhập không được để trống");
        return;
    }
    QString password=ui->password_2->text();
    if (password=="") {
        QMessageBox::warning(this, "Thông báo", "Mật khẩu không được để trống");
        return;
    }
    teacherInfo x;
    x.setFirstName(firstName);
    x.setLastName(lastName);
    x.setGender(gender);
    x.setDateOfBirth(dateOfBirth);
    x.setSocialId(socialId);
    x.setEmail(email);
    account tmp;
    tmp.setUsername(userName);
    tmp.setPassword(password);
    x.setTeacherAccount(tmp);
    QVector<teacherInfo> list=getTeacherInfos();
    list.append(x);
    setTeacherInfos(list);
    QMessageBox::warning(this, "Thông báo", "Tạo tài khoản thành công!");
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_newAccount_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_update_clicked()
{
    QString name=ui->className_3->text();
    QString idCourse=ui->idCourse_2->text();
    QString nameCourse=ui->courseName_2->text();
    QString nameClass=ui->className_5->text();
    QString teacherName=ui->teacherName_2->text();
    int credits= ui->credits_2->text().toInt();
    QStringList data=ui->time_2->text().split (" ");

    QVector<course> list = getListOfCourse();
    int pos=findIndexCourse (name, list);
    if (pos>=0 && pos<list.size()) {
        if (list[pos].getClassName()!=nameClass) {
            QVector<Class> listClass=getListOfClass();
            for (int i=0;i<list[pos].getListOfStudent().size();i++) {
                int posClass=-1, posNo=-1;
                findIndexStudent(list[pos].getListOfStudent()[i], posClass, posNo);
                if (posClass>=0 && posNo>=0) {
                    for (int j=0;j<listClass[posClass].getListOfStudent()[posNo].getListOfCourses().size();j++) {
                        if (listClass[posClass].getListOfStudent()[posNo].getListOfCourses()[j].getClassName()==list[pos].getClassName()) {
                            listClass[posClass].getListOfStudent()[posNo].getListOfCourses()[j].setClassName(nameClass);
                            break;
                        }
                    }
                }
            }
            setListOfClass(listClass);
        }
        list[pos].setClassName(nameClass);
        list[pos].setIdCourse(idCourse);
        list[pos].setCourseName(nameCourse);
        list[pos].setTeacherName(teacherName);
        list[pos].setNumOfCredits(credits);
        if (data.size()==2) {
            list[pos].setDayOfWeek(data.at(0));
            list[pos].setSession(data.at(1));
        }
        setListOfCourse(list);
    }
    QMessageBox::warning(this, "Thông báo", "Cập nhật thành công!");
}


void MainWindow::on_updateCourseInfo_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(4);
}

void MainWindow::on_addStudentToCourse_clicked()
{
    QString id=ui->idStudent_3->text();
    int posClass=-1, pos=-1;
    findIndexStudent(id, posClass, pos);
    if (posClass>=0 && pos>=0) {
        QVector<Class> list=getListOfClass();
        QVector<course> listCourse=getListOfCourse();
        ui->firstName_4->setText (list[posClass].getListOfStudent()[pos].getFirstName());
        ui->lastName_4->setText (list[posClass].getListOfStudent()[pos].getLastName());
        ui->gender_4->setText (list[posClass].getListOfStudent()[pos].getGender());
        ui->dateOfBirth_4->setText (list[posClass].getListOfStudent()[pos].getDateOfBirth());
        ui->class_2->setText (list[posClass].getClassName());
        ui->socialId_4->setText (list[posClass].getListOfStudent()[pos].getSocialId());

        QString name=ui->className_3->text();
        int posCourse = findIndexCourse(name, listCourse);
        if (posCourse>=0) {
            listCourse[posCourse].getListOfStudent().append (id);
            list[posClass].getListOfStudent()[pos].getListOfCourses().append (listCourse[posCourse]);

            std::sort (listCourse[posCourse].getListOfStudent().begin(), listCourse[posCourse].getListOfStudent().end(), cmpIdStudent2);

            setListOfCourse(listCourse);
            setListOfClass(list);
            QMessageBox::warning(this, "Thông báo", "Thêm sinh viên thành công!");
        }
    }
    else QMessageBox::warning(this, "Thông báo", "Không tìm thấy sinh viên!");
}


void MainWindow::on_addStudent_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(5);
}


void MainWindow::on_removeStudent_clicked()
{
    QString id=ui->idStudent_4->text();
    int posClass=-1, pos=-1;
    findIndexStudent(id, posClass, pos);
    if (posClass>=0 && pos>=0) {
        QVector<Class> list=getListOfClass();
        QVector<course> listCourse=getListOfCourse();
        ui->firstName_5->setText (list[posClass].getListOfStudent()[pos].getFirstName());
        ui->lastName_5->setText (list[posClass].getListOfStudent()[pos].getLastName());
        ui->gender_5->setText (list[posClass].getListOfStudent()[pos].getGender());
        ui->dateOfBirth_5->setText (list[posClass].getListOfStudent()[pos].getDateOfBirth());
        ui->class_3->setText (list[posClass].getClassName());
        ui->socialId_5->setText (list[posClass].getListOfStudent()[pos].getSocialId());

        QString name=ui->className_3->text();
        int posCourse = findIndexCourse(name, listCourse);
        if (posCourse>=0) {
            listCourse[posCourse].RemoveStudentbyID(id);
            for (int i=0;i<list[posClass].getListOfStudent()[pos].getListOfCourses().size();i++) {
                if (list[posClass].getListOfStudent()[pos].getListOfCourses()[i].getClassName()==name) {
                    list[posClass].getListOfStudent()[pos].getListOfCourses().erase (list[posClass].getListOfStudent()[pos].getListOfCourses().begin()+i);
                    break;
                }
            }

            setListOfCourse(listCourse);
            setListOfClass(list);
            QMessageBox::warning(this, "Thông báo", "Xoá sinh viên thành công!");
        }
    }
    else QMessageBox::warning(this, "Thông báo", "Không tìm thấy sinh viên!");
}


void MainWindow::on_removeAStudent_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(6);
}


void MainWindow::on_deleteCourse_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xoá khoá học", "Bạn thật sự muốn xoá khoá học?", QMessageBox::Yes | QMessageBox::No);
    if (reply==QMessageBox::Yes ) {
        QString name=ui->className_3->text();
        QVector<course> listCourse = getListOfCourse();
        QVector<Class> listClass = getListOfClass();
        int pos= findIndexCourse(name, listCourse);
        if (pos>=0) {
            for (int i=0;i<listCourse[pos].getListOfStudent().size();i++) {
                int posClass=-1, posNo=-1;
                findIndexStudent(listCourse[pos].getListOfStudent()[i], posClass, posNo);
                if (posClass>=0 && posNo>=0) {
                    for (int j=0;j<listClass[posClass].getListOfStudent()[posNo].getListOfCourses().size();j++) {
                        if (listClass[posClass].getListOfStudent()[posNo].getListOfCourses()[j].getClassName()==name) {
                            listClass[posClass].getListOfStudent()[posNo].getListOfCourses().erase(listClass[posClass].getListOfStudent()[posNo].getListOfCourses().begin()+j);
                            break;
                        }
                    }
                }
            }
            listCourse.erase (listCourse.begin()+pos);
            setListOfClass(listClass);
            setListOfCourse(listCourse);
        }
        else QMessageBox::warning(this, "Thông báo", "Không tìm thấy khoá học!");
    }
}


void MainWindow::on_uploadAndAddCourse_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)){
        course x;
        QVector<Class> listClass=getListOfClass();
        QVector<course> listCourse=getListOfCourse();
        x.setIdCourse(ui->idCourse_3->text());
        x.setCourseName(ui->courseName_3->text());
        x.setClassName(ui->className_6->text());
        x.setMaxStudent(ui->maxStudents_2->text().toInt());
        x.setTeacherName(ui->teacherName_3->text());
        x.setNumOfCredits(ui->credits_3->text().toInt());
        x.setDayOfWeek(ui->time_3->text());
        x.setSession(ui->session->text());


        QTextStream stream(&file);
        while (stream.atEnd()==false){
            QString lineData=stream.readLine();
            QStringList data=lineData.split (";");
            x.getListOfStudent().append(data.at(0));
        }
        for (int i=0;i<x.getListOfStudent().size();i++) {
            int posClass=-1, posNo=-1;
            findIndexStudent (x.getListOfStudent()[i], posClass, posNo);
            if (posClass>=0 && posNo>=0){
                listClass[posClass].getListOfStudent()[posNo].getListOfCourses().append(x);
            }
        }
        listCourse.append(x);
        setListOfClass(listClass);
        setListOfCourse(listCourse);
        file.close();
        QMessageBox::information(this, "Thông báo", "Thêm khoá học thành công!");
    }
}


void MainWindow::on_newSemester_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(7);
}


void MainWindow::on_newSemester_4_clicked()
{
    QString start=ui->startDate_4->text();
    QString end=ui->endDate_3->text();
    QString kind=ui->noSemeter->text();
    QVector<course> list=getListOfCourse();
    list.clear();
    QVector<Class> listClass=getListOfClass();
    for (int i=0;i<listClass.size();i++) {
        for (int j=0;j<listClass[i].getListOfStudent().size();j++){
            listClass[i].getListOfStudent()[j].getListOfCourses().clear();
        }
    }
    setListOfCourse(list);
    setListOfClass(listClass);
    setStartDate(start);
    setEndDate(end);
    setKindOfSemester(kind);
    QMessageBox::information(this, "Thông báo", "Tạo học kì thành công!");
}


void MainWindow::on_newSemester_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_newSchoolyear_clicked()
{
    QString schoolYear=ui->schoolyear->text();
    setStartDate("");
    setEndDate("");
    setKindOfSemester("");
    setSchoolYear(schoolYear);
    QVector<course> list=getListOfCourse();
    list.clear();
    setListOfCourse(list);

    QVector<Class> listClass=getListOfClass();
    while (listClass.size()>1 && listClass[0].getClassName()[0]==listClass[1].getClassName()[0] && listClass[0].getClassName()[1]==listClass[1].getClassName()[1]) {
        listClass.erase (listClass.begin());
    }
    listClass.erase (listClass.begin());
    for (int i=0;i<listClass.size();i++) {
        for (int j=0;j<listClass[i].getListOfStudent().size();j++){
            listClass[i].getListOfStudent()[j].getListOfCourses().clear();
        }
    }
    setListOfClass(listClass);
    QMessageBox::information(this, "Thông báo", "Tạo năm học mới thành công!");
}


void MainWindow::on_uploadListStudent_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)){
        QVector<Class> list= getListOfClass();
        Class x;
        x.setClassName(ui->className_7->text());
        QTextStream stream(&file);
        while (stream.atEnd()==false){
            student tmp;
            QString lineData=stream.readLine();
            QStringList data=lineData.split (";");
            if (data.size()==7) {
                tmp.setIdStudent(data.at(1));
                account cur;
                cur.setUsername(data.at(1));
                cur.setPassword(data.at(1));
                tmp.setStudentAccount(cur);

                tmp.setFirstName(data.at(2));
                tmp.setLastName(data.at(3));
                tmp.setGender (data.at(4));
                tmp.setDateOfBirth(data.at(5));
                tmp.setSocialId(data.at(6));
                x.getListOfStudent().append(tmp);
            }
        }
        list.append(x);
        setListOfClass(list);
        file.close();
        QMessageBox::information(this, "Thông báo", "Thêm lớp học thành công!");
    }
}


void MainWindow::on_newSchoolYear_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

