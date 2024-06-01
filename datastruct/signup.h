#ifndef SIGNUP_H
#define SIGNUP_H

#include "loginwindow.h" // 鍖呭惈loginwindow.h
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QFont>
#include <QMessageBox>
#include <QScreen>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class signup;
}

class signup : public QWidget
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
