#ifndef ADD_STUDENT_H
#define ADD_STUDENT_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class add_student;
}

class add_student : public QDialog
{
    Q_OBJECT

public:
    explicit add_student(QWidget *parent = 0);
    explicit add_student(QMap<QString, QStringList> *data,QWidget *parent = 0);
    ~add_student();

private:
    QStringList mClass;  //存放课程名
    Ui::add_student *ui;
};

#endif // ADD_STUDENT_H
