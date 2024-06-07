#ifndef INSIDESEARCH_H
#define INSIDESEARCH_H

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
namespace Ui {
class insidesearch;
}
struct Point {
    int id;
    QString name;
    QString type;
};

struct Edge {
    Point dest;
    double distance;
    double congestion;
};



class insidesearch : public QWidget
{
    Q_OBJECT

public:
    explicit insidesearch(QWidget *parent = nullptr);
    ~insidesearch();
    void bubbleSort(QVector<Edge>& edges);
    QVector<Edge> edges;
    QMap<QString, Point> points;
    QVector<QVector<Edge>> adjList;
    int pointCount = 0;

    void readinsidePlacesFromFile();
    QVector<Edge> filterByType(const QVector<Edge>& edges, const QString& type);
    double idealSpeed = 5.0;  // 理想速度


private slots:
    void on_start_clicked();

private:
    Ui::insidesearch *ui;
    void findNearbyPoints(const QVector<QVector<Edge>>& adjList, const QMap<QString, Point>& points, const QString& pointName, double range, const QString* typeFilter);
};

#endif // INSIDESEARCH_H
