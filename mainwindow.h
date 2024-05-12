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

    student findStudent (const QString& id);

    void setPosNoStudent (const int& pos);

    void setPosClassStudent (const int& pos);

    int getPosNoStudent ();

    int getPosClassStudent ();

    bool loginStudent (const QString& name, const QString& pass, QVector<Class> list, int& posNo, int& posClass);

    course findCourse (const QString& name, QVector<course> list);

    void setCourseForStudent (QVector<course> listCourse, QVector<Class> &listClass);

private slots:
    void on_teacher_clicked();

    void on_account_clicked();

    void on_home_2_clicked();

    void on_pushButton_clicked();

    void on_changePass_clicked();

    void on_logOut_2_clicked();

    void on_schoolYear_clicked();

    void on_listClasses_clicked();

    void on_listStudentInClass_clicked();

    void on_find_clicked();

    void on_home_3_clicked();

    void on_account_3_clicked();

    void on_account_2_clicked();

    void on_schoolYear_2_clicked();

    void on_listClasses_2_clicked();

    void on_course_clicked();

    void on_course_2_clicked();

    void on_course_3_clicked();

    void on_home_4_clicked();

    void on_account_4_clicked();

    void on_schoolYear_5_clicked();

    void on_logOut_4_clicked();

    void on_listStudentInClass_2_clicked();

    void on_findStudentInCourse_clicked();

    void on_newSemester_3_clicked();

    void on_findCourse_clicked();

    void on_back_clicked();

    void on_student_clicked();

    void on_account_Student_clicked();

    void on_logOut_5_clicked();

    void on_schedule_clicked();

private:
    Ui::MainWindow *ui;
    QVector<teacherInfo> TeacherInfo;
    int posTeacherUser;
    int posNoStudent, posClassStudent;
    QVector<Class> listOfClass;
    QVector<course> listOfCourse;
    QString kindOfSemester, schoolYear,startDate, endDate;
};
#endif // MAINWINDOW_H
