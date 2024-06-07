#ifndef JOURNAL_H
#define JOURNAL_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QMap>
#include <QVector>
#include <QDebug>
#include <QPair>
namespace Ui {
class journal;
}

struct Journal {
    QString name;
    QString content;
    int views;
    double rating;
    int ratingsCount;
    QString destination;
};

class journal : public QWidget
{
    Q_OBJECT

public:
    explicit journal(QWidget *parent = nullptr);
    ~journal();
    QVector<Journal> journals;
private:
    Ui::journal *ui;
};

#endif // JOURNAL_H
