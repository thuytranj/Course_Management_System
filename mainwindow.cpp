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

QVector<Class> MainWindow::getListOfClass()
{
    return listOfClass;
}
void MainWindow::setListOfCourse (QVector<course> list){
    listOfCourse=list;
}
QVector<course> MainWindow::getListOfCourse (){
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Tên đăng nhập");
    ui->password->setPlaceholderText("Mật khẩu");
    QVector<Class> classInSemester;
    readClasses ("/Users/thuytran/Documents/Course_Management_System/build/Qt_6_7_0_for_macOS-Debug/database/classes.csv", classInSemester);
    QVector<course> courseInSemester;
    QVector<QString> semester = readCourseInSemester("/Users/thuytran/Documents/Course_Management_System/build/Qt_6_7_0_for_macOS-Debug/database/semester.csv", courseInSemester);
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
    QVector<teacherInfo> TeacherInfo;
    readTeacherInfo("/Users/thuytran/Documents/Course_Management_System/build/Qt_6_7_0_for_macOS-Debug/database/Teacher.csv", TeacherInfo);
    setTeacherInfos (TeacherInfo);
    int pos=-1;
    QString name=ui->username->text();
    QString pass=ui->password->text();
    if (isValidLogin(name, pass, TeacherInfo, pos)) {
        setPosTeacherUser(pos);
        ui->stackedWidget->setCurrentIndex(1);

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
    QVector<teacherInfo> cur = getTeacherInfos();
    int pos=getPosTeacherUser();
    QString newPassword=ui->newPass->text();
    QString comfirm=ui->comfirmPass->text();
    if (newPassword.isEmpty()) {
        QMessageBox::warning(this, "Đổi mật khẩu", "Mật khẩu mới không được để trống!");
        return;
    }
    if (newPassword==comfirm) {
        account ac;
        ac.setUsername(cur[pos].getTeacherAccount().getUsername());
        ac.setPassword(newPassword);
        cur[pos].setTeacherAccount(ac);
        QFile file ("/Users/thuytran/Documents/Course_Management_System/build/Qt_6_7_0_for_macOS-Debug/database/Teacher.csv");
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            QTextStream stream (&file);
            for (int i=0;i<cur.size();i++) {
                stream << "\""<<cur[i].getTeacherAccount().getUsername()<<"\";"
                       << "\""<<cur[i].getTeacherAccount().getPassword()<<"\";"
                       << "\""<<cur[i].getFirstName()<<"\";"
                       << "\""<<cur[i].getLastName()<<"\";"
                       << "\""<<cur[i].getGender()<<"\";"
                       << "\""<<cur[i].getDateOfBirth()<<"\";"
                       << "\""<<cur[i].getSocialId()<<"\";"
                       << "\""<<cur[i].getEmail()<<"\"\r\n";
            }
            stream.flush();
        }
        file.close();
        QMessageBox::information(this, "Đổi mật khẩu", "Mật khẩu đã cập nhật!");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        QMessageBox::warning(this, "Đổi mật khẩu", "Mật khẩu xác nhận không trùng khớp!");
        return;
    }
}


void MainWindow::on_logOut_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_schoolYear_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    QString year=getSchoolYear();
    QString kindSemester=getKindOfSemester();
    QString StartDate=getStartDate();
    QString EndDate=getEndDate();
    ui->schoolYear_4->setText(year);
    ui->semester->setText(kindSemester);
    ui->startDate->setText(StartDate);
    ui->endDate->setText(EndDate);
    QVector<Class> lstClass=getListOfClass();
    ui->table_class->setColumnWidth(0, 250);
    ui->table_class->setColumnWidth(1, 250);
    ui->table_class->setRowCount(lstClass.size());
    for (int i=0;i<lstClass.size();i++) {
        ui->table_class->setItem(i, 0, new QTableWidgetItem(lstClass[i].getClassName()));
        ui->table_class->setItem(i, 1, new QTableWidgetItem(QString::number(lstClass[i].getListOfStudent().size())));
    }
}


void MainWindow::on_listClasses_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
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

}

void MainWindow::on_course_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
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
    ui->stackedWidget->setCurrentIndex(2);
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
    int posNo=-1, posClass=-1;
    if (loginStudent(name, pass, list, posNo, posClass)) {
        ui->stackedWidget->setCurrentIndex(6);
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
    // ui->stackedWidget_4->setCurrentIndex(2);
    // ui->schoolYear_7->setText(getSchoolYear());
    // ui->semester_3->setText (getKindOfSemester());
    // ui->startDate_3->setText (getStartDate());
    // ui->endDate_3->setText(getEndDate());
    // QVector<course> listCourse=getListOfCourse();
    // int classPos=getPosClassStudent();
    // int noPos=getPosNoStudent();
    // QVector<Class> list=getListOfClass();
    // QVector<QString> listClassName=list[classPos].getListOfStudent()[noPos].getListOfCourses();
    // ui->schedule_2->setRowCount ();
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
                    stream<<x.getIdSudent()<<";"
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

        while (!file.atEnd()) {
            lineData=stream.readLine().trimmed();
            QStringList data=lineData.split(";");
            QString id=data.at(1);
            int posClass=-1, pos=-1;
            findIndexStudent(id, posClass, pos);
            if (posClass!=-1 && pos!=-1) {
                int posCourse = findIndexCourse(className, list[posClass].getListOfStudent()[pos].getListOfCourses());
                if (posCourse!=-1) {
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setTotal(data.at(4).toDouble());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setFinal(data.at(5).toDouble());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setMid(data.at(6).toDouble());
                    list[posClass].getListOfStudent()[pos].getListOfCourses()[posCourse].setOtherMark(data.at(7).toDouble());
                }
            }

        }

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
    for (int i=0;i<list.size();i++) {
        student stu=findStudent(list[i]);
        int pos=findIndexCourse(className, stu.getListOfCourses());

        ui->scoreboard->setItem(i, 0, new QTableWidgetItem(stu.getIdSudent()));
        ui->scoreboard->setItem(i, 1, new QTableWidgetItem(stu.getFirstName()));
        ui->scoreboard->setItem(i, 2, new QTableWidgetItem(stu.getLastName()));
        ui->scoreboard->setItem(i, 3, new QTableWidgetItem(stu.getListOfCourses()[pos].getTotal()));
        ui->scoreboard->setItem(i, 4, new QTableWidgetItem(stu.getListOfCourses()[pos].getFinal()));
        ui->scoreboard->setItem(i, 5, new QTableWidgetItem(stu.getListOfCourses()[pos].getMid()));
        ui->scoreboard->setItem(i, 6, new QTableWidgetItem(stu.getListOfCourses()[pos].getOtherMark()));
    }
}

