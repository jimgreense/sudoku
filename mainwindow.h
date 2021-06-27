#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>

#include "suduko.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTableWidget *tableWidget;
    QPushButton *butt_solve;
    QPushButton *butt_init;
    QPushButton *butt_clear;
    QTableWidgetItem *tableitems[9][9];

    Suduko *sudu;

    bool checkdata();  // check if the data on the table is valid

protected slots:
    void onButtonSolveClicked();
    void onButtonInitClicked();
    void onButtonClearClicked();
};
#endif // MAINWINDOW_H
