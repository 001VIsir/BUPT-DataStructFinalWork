#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h" // 包含loginwindow.h
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
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

   void on_beginButton_clicked();

private:
    Ui::MainWindow *ui;
    loginwindow *loginWindow; // 添加LoginWindow对象
    QPushButton *beginButton; // 添加QPushButton对象
};
#endif // MAINWINDOW_H
