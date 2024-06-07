#include "navigate.h"
#include "ui_navigate.h"

navigate::navigate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::navigate)
{
    ui->setupUi(this);
    readinsidePlacesFromFile();
}

navigate::~navigate()
{
    delete ui;
}

void navigate::readinsidePlacesFromFile() {
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


void navigate::reverse(QVector<Edge>::iterator first, QVector<Edge>::iterator last) {
    while ((first != last) && (first != --last)) {
        std::iter_swap(first, last);
        ++first;
    }
}

void navigate::heapifyDown(QVector<QPair<double, int>>& heap, int size, int i) {
    int minIndex = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && heap[l].first < heap[minIndex].first) {
        minIndex = l;
    }
    if (r < size && heap[r].first < heap[minIndex].first) {
        minIndex = r;
    }
    if (minIndex != i) {
        qSwap(heap[i], heap[minIndex]);
        heapifyDown(heap, size, minIndex);
    }
}

void navigate::heapifyUp(QVector<QPair<double, int>>& heap, int i) {
    while (i > 0 && heap[(i - 1) / 2].first > heap[i].first) {
        qSwap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void navigate::pushHeap(QVector<QPair<double, int>>& heap, int& size, QPair<double, int> value) {
    heap.push_back(value);
    size++;
    heapifyUp(heap, size - 1);
}

QPair<double, int> navigate::popHeap(QVector<QPair<double, int>>& heap, int& size) {
    if (size == 0) {
        return qMakePair(std::numeric_limits<double>::max(), -1);
    }
    QPair<double, int> root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(heap, size, 0);
    return root;
}

// Dijkstra算法实现
QVector<Edge> navigate::dijkstra(const QVector<QVector<Edge>>& adjList, const QMap<QString, Point>& points, const QString& startPointName, const QString& endPointName, bool useTime) {
    int src = points.value(startPointName).id; // 起始点的编号
    int dest = points.value(endPointName).id; // 目标点的编号
    int n = adjList.size(); // 图中节点的数量
    QVector<double> dist(n, std::numeric_limits<double>::max()); // 从起始点到各节点的距离/时间
    QVector<int> prev(n, -1); // 最短路径的前驱节点
    QVector<QPair<double, int>> heap; // 最小堆用于Dijkstra算法
    int heapSize = 0;

    dist[src] = 0; // 起始点到自身的距离为0
    pushHeap(heap, heapSize, { 0, src }); // 将起始点加入优先队列

    // Dijkstra算法核心部分
    while (heapSize > 0) {
        int u = popHeap(heap, heapSize).second; // 获取当前距离起始点最近的节点

        // 遍历当前节点的所有邻居
        for (const auto& edge : adjList[u]) {
            int v = edge.dest.id; // 邻居节点的编号
            double weight = useTime ? edge.congestion : edge.distance; // 根据useTime判断权重类型

            // 松弛操作：如果通过当前节点u到节点v的距离/时间更短，则更新距离/时间，并将v加入队列
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pushHeap(heap, heapSize, { dist[v], v });
            }
        }
    }

    // 构造最短路径
    QVector<Edge> path;
    int current = dest;
    while (current != -1) {
        // 获取当前节点的名称
        QString currentName;
        for (const auto& entry : points.toStdMap()) {
            if (entry.second.id == current) {
                currentName = entry.first;
                break;
            }
        }

        Point currentPoint = points.value(currentName); // 获取当前节点的信息
        double currentDist = dist[current]; // 获取当前节点的距离/时间

        // 将当前节点信息添加到路径中
        path.push_back({ currentPoint, currentDist });

        // 更新当前节点为上一个节点
        current = prev[current];
    }

    // 将路径反转，使其从起始点到目标点
    reverse(path.begin(), path.end());
    ui->result->setRowCount(path.size());
    int row = 0;
    for(const auto& edge : path){
        ui->result->setItem(row, 0, new QTableWidgetItem(edge.dest.name));


        if(ui->distance->isChecked())
        {

            ui->result->setItem(row, 1, new QTableWidgetItem(QString::number(edge.distance)));
        }

        else if(ui->time->isChecked())
        {
            QDebug qdebug = qDebug();
            qdebug << edge.congestion;
            ui->result->setItem(row, 1, new QTableWidgetItem(QString::number(edge.distance)));
        }


        ++row;
    }
    return path; // 返回最短路径
}

void navigate::on_start_clicked()
{
    QString begin = ui->begin->text();
    QString dest = ui->dest->text();

    bool flag = false;
    if(ui->distance->isChecked())
    {
        flag = false;
    }
    else if(ui->time->isChecked())
    {
        flag = true;
    }
    QVector<Edge> path = dijkstra(adjList, points, begin, dest, flag);

}


void navigate::on_quit_clicked()
{
    close();
}

