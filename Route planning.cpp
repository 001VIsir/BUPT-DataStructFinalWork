#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Point {
    int id;
    string name;
    string type;
};

struct Edge {
    Point dest;
    double distance;
    double time;
};

double idealSpeed = 5.0;  // 理想速度

// Dijkstra算法
vector<Edge> dijkstra(const vector<vector<Edge>>& adjList, const map<string, Point>& points, const string& startPointName, const string& endPointName, bool useTime) {
    int src = points.at(startPointName).id; // 起始点的编号
    int dest = points.at(endPointName).id; // 目标点的编号
    int n = adjList.size(); // 图中节点的数量
    vector<double> dist(n, numeric_limits<double>::max()); // 从起始点到各节点的距离/时间
    vector<int> prev(n, -1); // 最短路径的前驱节点
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; // 最小堆用于Dijkstra算法

    dist[src] = 0; // 起始点到自身的距离为0
    pq.push({ 0, src }); // 将起始点加入优先队列

    // Dijkstra算法核心部分
    while (!pq.empty()) {
        int u = pq.top().second; // 获取当前距离起始点最近的节点
        pq.pop();

        // 遍历当前节点的所有邻居
        for (const auto& edge : adjList[u]) {
            int v = edge.dest.id; // 邻居节点的编号
            double weight = useTime ? edge.time : edge.distance; // 根据useTime判断权重类型

            // 松弛操作：如果通过当前节点u到节点v的距离/时间更短，则更新距离/时间，并将v加入队列
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    // 构造最短路径
    vector<Edge> path;
    int current = dest;
    while (current != -1) {
        // 获取当前节点的名称
        string currentName;
        for (const auto& entry : points) {
            if (entry.second.id == current) {
                currentName = entry.first;
                break;
            }
        }

        Point currentPoint = points.at(currentName); // 获取当前节点的信息
        double currentDist = dist[current]; // 获取当前节点的距离/时间

        // 将当前节点信息添加到路径中
        path.push_back({ currentPoint, currentDist });

        // 更新当前节点为上一个节点
        current = prev[current];
    }

    // 将路径反转，使其从起始点到目标点
    reverse(path.begin(), path.end());

    return path; // 返回最短路径
}

int main() {
    ifstream file("inside_path.csv");
    string line;
    map<string, Point> points;
    int pointCount = 0;
    vector<vector<Edge>> adjList;

    // 读取并丢弃第一行
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string point1, point2, distance, congestion;
        getline(ss, point1, ',');
        getline(ss, point2, ',');
        getline(ss, distance, ',');
        getline(ss, congestion, ',');

        string type1 = point1.substr(0, point1.find_first_of("0123456789"));
        string type2 = point2.substr(0, point2.find_first_of("0123456789"));

        if (points.find(point1) == points.end()) {
            points[point1] = { pointCount++, point1, type1 };
            adjList.resize(pointCount);
        }

        if (points.find(point2) == points.end()) {
            points[point2] = { pointCount++, point2, type2 };
            adjList.resize(pointCount);
        }

        Point p1 = points[point1];
        Point p2 = points[point2];
        double dist = stod(distance);
        double time = dist / (stod(congestion) * idealSpeed);

        Edge edge1 = { p2, dist, time };
        Edge edge2 = { p1, dist, time };
        adjList[p1.id].push_back(edge1);
        adjList[p2.id].push_back(edge2);
    }

    // 输入地点名称
    string pointName1, pointName2;
    cout << "Enter the name of the starting point: ";
    cin >> pointName1;
    if (points.find(pointName1) == points.end()) {
        cerr << "Error: Starting point '" << pointName1 << "' does not exist." << endl;
        return 1;
    }

    cout << "Enter the name of the destination point: ";
    cin >> pointName2;
    if (points.find(pointName2) == points.end()) {
        cerr << "Error: Destination point '" << pointName2 << "' does not exist." << endl;
        return 1;
    }

    // 输入路线策略
    int strategy;
    cout << "Enter 0 for shortest path strategy or 1 for shortest time strategy: ";
    cin >> strategy;
    if (strategy != 0 && strategy != 1) {
        cerr << "Error: Invalid strategy. Enter 0 for shortest path or 1 for shortest time." << endl;
        return 1;
    }

    // 根据选择的策略找出路径
    vector<Edge> path = dijkstra(adjList, points, pointName1, pointName2, strategy == 1);
    cout << (strategy == 0 ? "Shortest path" : "Fastest path") << " from " << pointName1 << " to " << pointName2 << ":" << endl;
    for (const auto& edge : path) {
        cout << edge.dest.name << " (" << (strategy == 0 ? "distance: " : "time: ") << edge.distance << ")" << endl;
    }

    return 0;
}




