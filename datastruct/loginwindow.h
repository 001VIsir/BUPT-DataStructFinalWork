#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "logup.h"
#include "feature_list.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <qstring.h>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QList>
#include <QtGlobal>
#include <QDebug>
#define TABLE_SIZE 100 // 哈希表的大小

namespace Ui {
class loginwindow;
}

struct User {
    int account;
    QString password;
    QString name;
    User* next;
};
//QDebug operator<<(QDebug debug, const User& user);

class loginwindow : public QWidget
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();
    void addUser(int account, QString password, QString name);
    User* users[TABLE_SIZE] = {nullptr}; // 哈希表，初始化为null
    void loadUsersFromCSV();
    static int hashFunction(int id);
    void printf_hash();
private slots:

    void loginUser();

    void on_quit_clicked();

    void on_sign_up_clicked();

private:
    Ui::loginwindow *ui;

    int loggedInUser = -1; // 当前登录的用户ID，-1表示没有用户登录


    void registerUser();
    void logoutUser();
    void getUserInfo();
    void printHashTable();
    feature_list *feature_List;
//    logup *logUp;
//    sign_up *sign_Up;
};

#endif // LOGINWINDOW_H
