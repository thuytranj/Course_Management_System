#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Tên đăng nhập");
    ui->password->setPlaceholderText("Mật khẩu");
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    ui->table_class->setRowCount(lstClass.size());
    for (int i=0;i<lstClass.size();i++) {
        ui->table_class->setItem(i, 0, new QTableWidgetItem(lstClass[i].getClassName()));
        ui->table_class->setItem(i, 1, new QTableWidgetItem(QString::number(lstClass[i].getListOfStudent().size())));
    }
}

