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
    void update_textView();//更新文字预览
private slots:
    void on_lineEdit_name_editingFinished();

    void on_lineEdit_num_editingFinished();

    void on_lineEdit_major_editingFinished();

    void on_lineEdit_grade_editingFinished();

    void on_lineEdit_score_editingFinished();

    void on_buttonBox_accepted();
signals:
    void add_stu_data(QStringList *mClass,QMap<QString,QString> *add_data);
private:
    QStringList mClass;  //存放课程名
    Ui::add_student *ui;
    QMap<QString,QString> add_data;//要添加的数据
};

#endif // ADD_STUDENT_H
