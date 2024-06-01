#include "logup.h"
#include "ui_logup.h"

logup::logup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logup)
{
    ui->setupUi(this);
}

logup::~logup()
{
    delete ui;
}

void logup::on_confirm_clicked()
{
    int account = ui->inputAcconut->text().toInt();
    QString password = ui->inputPassword->text();
    QString name = ui->inputName->text();

    User* xinlaide = new User();
    xinlaide->account = account;
    xinlaide->password = password;
    xinlaide->name = name;
    int index = loginwindow::hashFunction(account);

    loginwindow *loginWindow;
    loginWindow->addUser(account, password, name); // 传递 loginwindow 类的实例来访问 users 数组

    QMessageBox::warning(this, "logup","注册成功");

}


void logup::on_quit_clicked()
{
    close();
}

