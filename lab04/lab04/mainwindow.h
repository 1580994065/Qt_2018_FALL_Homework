#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "common.h"
#include "dataworker.h"
#include "add_student.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    DataWorker* getDataworker();

private slots:
    void on_pushButton_search_clicked();
    void on_radioButton_num_clicked();
    void on_radioButton_name_clicked();

    void table_updata(QMap<QString,QStringList> *m_data);
    void on_pushButton_adddata_clicked();

    void on_pushButton_output_sql_clicked();

private:
    Ui::MainWindow *ui;
    DataWorker *dataworker;
    add_student *add;
};

#endif // MAINWINDOW_H
