#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    loginWindow = new loginwindow(this); // 初始化LoginWindow对象
    connect(beginButton, &QPushButton::clicked, this, &MainWindow::on_beginButton_clicked); // 连接按钮的clicked信号到showLoginWindow槽函数
}

MainWindow::~MainWindow()
{
    delete ui;

    delete loginWindow; // 删除LoginWindow对象

}

// 添加一个槽函数，用于显示登录窗口


void MainWindow::on_beginButton_clicked()
{

    loginWindow = new loginwindow;
    loginWindow->loadUsersFromCSV();
    loginWindow->show(); // 显示登录窗口
}

