#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include "common.h"
#include "mainwindow.h"

namespace Ui {
class welcome;
}

class welcome : public QWidget
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = 0);
    ~welcome();

private slots:
    void on_sql_source_button_clicked();

    void on_file_source_button_clicked();

private:
    Ui::welcome *ui;
    MainWindow *main_window;
signals:
    void file_geted(QStringList data,QString path);
};

#endif // WELCOME_H
