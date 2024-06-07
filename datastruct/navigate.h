#ifndef NAVIGATE_H
#define NAVIGATE_H

#include <insidesearch.h>
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
class navigate;
}

class navigate : public QWidget
{
    Q_OBJECT

public:
    explicit navigate(QWidget *parent = nullptr);
    ~navigate();
    QVector<Edge> edges;
    QMap<QString, Point> points;
    QVector<QVector<Edge>> adjList;
    int pointCount = 0;
    void readinsidePlacesFromFile();
    double idealSpeed = 5.0;  // 理想速度
    void reverse(QVector<Edge>::iterator first, QVector<Edge>::iterator last);
    void heapifyDown(QVector<QPair<double, int>>& heap, int size, int i);
    void heapifyUp(QVector<QPair<double, int>>& heap, int i);
    void pushHeap(QVector<QPair<double, int>>& heap, int& size, QPair<double, int> value);
    QPair<double, int> popHeap(QVector<QPair<double, int>>& heap, int& size);
    QVector<Edge> dijkstra(const QVector<QVector<Edge>>& adjList, const QMap<QString, Point>& points, const QString& startPointName, const QString& endPointName, bool useTime);


private slots:


    void on_start_clicked();

    void on_quit_clicked();

private:
    Ui::navigate *ui;
};

#endif // NAVIGATE_H
