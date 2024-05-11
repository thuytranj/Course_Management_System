#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "teacherinfo.h"
#include "class.h"
#include "course.h"
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTeacherInfos (QVector<teacherInfo> _TeacherInfo);
    void setPosTeacherUser (const int& _pos);
    QVector<teacherInfo> getTeacherInfos () const;
    int getPosTeacherUser ();
    void setListOfClass (QVector<Class> _list);
    QVector<Class> getListOfClass ();
    void setListOfCourse (QVector<course> list);
    QVector<course> getListOfCourse ();
    void setKindOfSemester (const QString& _kindOfSemester);
    void setSchoolYear (const QString& _schoolYear);
    void setStartDate (const QString& _startDate);
    void setEndDate (const QString& _endDate);
    QString getKindOfSemester ();
    QString getSchoolYear ();
    QString getStartDate();
    QString getEndDate();

private slots:
    void on_teacher_clicked();

    void on_account_clicked();

    void on_home_2_clicked();

    void on_pushButton_clicked();

    void on_changePass_clicked();

    void on_logOut_2_clicked();

    void on_schoolYear_clicked();

private:
    Ui::MainWindow *ui;
    QVector<teacherInfo> TeacherInfo;
    int posTeacherUser;
    QVector<Class> listOfClass;
    QVector<course> listOfCourse;
    QString kindOfSemester, schoolYear,startDate, endDate;
};
#endif // MAINWINDOW_H
