#include "mainwindow.h"
#include <QHeaderView>

#define BLOCK_SIZE 50

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sudu = new Suduko("070000000008005000000100020000980000400000603000000500030090006090040712050062904");
    sudu = new Suduko();

    tableWidget = new QTableWidget(9, 9, this);

    QFont font;
    font.setFamily("宋体"); //设置文字字体
    font.setPointSize(30);//字体大小
    tableWidget->setFont(font);
//    tableWidget->resizeColumnsToContents();
//    tableWidget->resizeRowsToContents();
    for (int i = 0; i < 9; i++)
        tableWidget->setColumnWidth(i, BLOCK_SIZE);
    for (int i = 0; i < 9; i++)
        tableWidget->setRowHeight(i, BLOCK_SIZE);
    tableWidget->resize(BLOCK_SIZE*9+50, BLOCK_SIZE*9+50);

    //tableWidget->horizontalHeader()->hide();//取消列号
    //tableWidget->verticalHeader()->hide();//取消行号

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            tableitems[i][j] = new QTableWidgetItem("");
            // 0x0004 Centers horizontally in the available space
            // 0x0080 Centers vertically in the available space
            tableitems[i][j]->setTextAlignment(0x0004 | 0x0080);
            tableWidget->setItem(i,j, tableitems[i][j]);
        }

    butt_solve = new QPushButton("Solve", this);
    //butt_init = new QPushButton("Init", this);
    butt_clear = new QPushButton("Clear", this);
    connect(butt_solve, &QPushButton::clicked, this, &MainWindow::onButtonSolveClicked);
    //connect(butt_init, &QPushButton::clicked, this, &MainWindow::onButtonInitClicked);
    connect(butt_clear, &QPushButton::clicked, this, &MainWindow::onButtonClearClicked);

    butt_solve->move(10, BLOCK_SIZE*9+50+20);
    //butt_init->move(10, BLOCK_SIZE*9+50+50);
    butt_clear->move(10, BLOCK_SIZE*9+50+50);
}

void MainWindow::onButtonSolveClicked()
{
    // read data from the table, update the suduko internal data
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            QString qs = tableitems[i][j]->text();
            int element = qs.toInt();
            sudu->set_element(i, j, element);
        }

    if (sudu->solve())
        sudu->pretty_print();

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            tableitems[i][j]->setText(QString::number(sudu->get_element(i,j)));
        }

}

void MainWindow::onButtonInitClicked()
{
    sudu->init();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            tableitems[i][j]->setText(QString::number(sudu->get_element(i,j)));
        }
}

void MainWindow::onButtonClearClicked()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            tableitems[i][j]->setText(QString(""));
        }
}

MainWindow::~MainWindow()
{
}

