#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets>
#include <QFrame>
#include "centerframe.h"
#include "drawwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createToolBar();
public slots:
    void penColorChangged ();
    void penStyleChangged (int index = 0);
private:
    Ui::MainWindow *ui;
    CenterFrame* centerFrame;
    QToolButton* clearBtn;
    QToolButton* colorBtn;
    QComboBox* styleComboBox;
    QSpinBox* widthSpinBox;
    QLabel* styleLabel;
    QLabel* widthLabel;
};

#endif // MAINWINDOW_H
