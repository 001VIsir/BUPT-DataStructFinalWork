#include "insidesearch.h"
#include "ui_insidesearch.h"

insidesearch::insidesearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insidesearch)
{
    ui->setupUi(this);
    readinsidePlacesFromFile();



    //默认显示所有地方
    ui->table1->setRowCount(points.size());
    int row = 0;
    for (auto it = insidesearch::points.constBegin(); it != insidesearch::points.constEnd(); ++it) {
        // 创建一个新的行，并将点的信息添加到这个行中
        ui->table1->setItem(row, 0, new QTableWidgetItem(it.key()));
        ui->table1->setItem(row, 1, new QTableWidgetItem(it.value().type));
//        ui->table1->setItem(row, 2, new QTableWidgetItem(QString::number(it.value().id)));
        ++row;
    }
}

insidesearch::~insidesearch()
{
    delete ui;
}

void insidesearch::readinsidePlacesFromFile() {
    QFile file("C:\\Users\\visir\\Desktop\\shujvjiegou\\inside_path.csv"); // 创建文件对象，指定文件路径

    // 尝试以只读和文本模式打开文件，如果失败则弹出警告框
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Warning", "Cannot open file");
    }

    QTextStream in(&file); // 创建文本流，关联到文件
    // 注释掉的代码，如果需要可以取消注释以设置编码为UTF-8
    // in.setCodec(QTextCodec::codecForName("UTF-8"));
    in.readLine(); // 读取并丢弃标题行

    // 逐行读取文件内容
    while (!in.atEnd()) {
        QString line = in.readLine(); // 读取一行数据
        QString point1 = line.section(',', 0, 0);
        QString point2 = line.section(',', 1, 1);
        QString distance = line.section(',', 2, 2);
        QString congestion = line.section(',', 3, 3);
//        QMessageBox::warning(nullptr, "Warning", "Cannot open file");
        QString qType1 = point1.left(point1.indexOf(QRegExp("[0-9]")));
        QString qType2 = point2.left(point2.indexOf(QRegExp("[0-9]")));

        if (!points.contains(point1)) {
            points[point1] = { pointCount++, point1, qType1 };
            adjList.resize(pointCount);
        }

        if (!points.contains(point2)) {
            points[point2] = { pointCount++, point2, qType2 };
            adjList.resize(pointCount);
        }

        Point p1 = points[point1];
        Point p2 = points[point2];
        double dist = distance.toDouble();
        double time = dist / (congestion.toDouble() * idealSpeed);

        Edge edge1 = { p2, dist, time };
        Edge edge2 = { p1, dist, time };
        adjList[p1.id].push_back(edge1);
        adjList[p2.id].push_back(edge2);
    }

    file.close(); // 关闭文件
    return; // 函数返回
}

//冒泡排序
void insidesearch::bubbleSort(QVector<Edge>& edges) {
    int n = edges.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (edges[j].distance > edges[j + 1].distance) {
                qSwap(edges[j], edges[j + 1]);
            }
        }
    }
}

QVector<Edge> insidesearch::filterByType(const QVector<Edge>& edges, const QString& type) {
    QVector<Edge> filteredEdges;
    for (const auto& edge : edges) {
        if (edge.dest.type == type) {
            filteredEdges.push_back(edge);
        }
    }
    return filteredEdges;
}

void insidesearch::findNearbyPoints(const QVector<QVector<Edge>>& adjList, const QMap<QString, Point>& points, const QString& pointName, double range, const QString* typeFilter) {
    if (!points.contains(pointName)) {
        qDebug() << "Point " << pointName << " does not exist.";
        return;
    }

    Point point = points.value(pointName);
    QVector<Edge> nearbyPoints;

    for (const auto& edge : adjList[point.id]) {
        if (edge.distance <= range) {
            nearbyPoints.push_back(edge);
        }
    }

    if (typeFilter != nullptr) {
        nearbyPoints = filterByType(nearbyPoints, *typeFilter);
    }

    bubbleSort(nearbyPoints);

    ui->table1->setRowCount(nearbyPoints.size()); // 设置行数为点的数

    int row = 0;
    for (const auto& edge : nearbyPoints) {
        // 创建一个新的行，并将点的信息添加到这个行中
        ui->table1->setItem(row, 0, new QTableWidgetItem(edge.dest.name));
        ui->table1->setItem(row, 1, new QTableWidgetItem(edge.dest.type));
        ui->table1->setItem(row, 2, new QTableWidgetItem(QString::number(edge.distance)));
        ui->table1->setItem(row, 3, new QTableWidgetItem(QString::number(edge.congestion)));
        ++row;
    }
}

void insidesearch::on_start_clicked()
{
    QString name = ui->place->text();
    QString type1 = ui->type->text();
    int flag2 = 0;
    if (ui->yes->isChecked()) {
        flag2 = 1; // 如果选中了按受欢迎程度排序，则设置flag2为1
    } else if (ui->no->isChecked()) {
        flag2 = 0; // 如果选中了按评分排序，则设置flag2为0
    }
    findNearbyPoints(adjList, points, name, 500, flag2 ? &type1 : nullptr);

}

