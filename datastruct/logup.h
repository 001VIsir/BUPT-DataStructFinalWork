#ifndef LOGUP_H
#define LOGUP_H

#include <QWidget>
#include "loginwindow.h"
#include "feature_list.h"
namespace Ui {
class logup;
}

class logup : public QWidget
{
    Q_OBJECT

public:
    explicit logup(QWidget *parent = nullptr);
    ~logup();

private slots:
    void on_confirm_clicked();

    void on_quit_clicked();

private:
    Ui::logup *ui;
//    loginwindow *loginWindow;
};

#endif // LOGUP_H
