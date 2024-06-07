void planRouteAndLog() { // 路径规划并生成日志
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

    // 输入当前位置名称
    string startPointName;
    cout << "Enter the name of the starting point: ";
    cin >> startPointName;
    if (points.find(startPointName) == points.end()) {
        cerr << "Error: Starting point '" << startPointName << "' does not exist." << endl;
        return ;
    }

    int strategy;
    // 输入多个目标地点名称
    vector<string> targetPoints;
    string targetPointName;
    cout << "Enter the names of the target points (enter 'done' to finish): ";
    while (cin >> targetPointName && targetPointName != "done") {
        if (points.find(targetPointName) == points.end()) {
            cerr << "Error: Target point '" << targetPointName << "' does not exist." << endl;
            return ;
        }
        targetPoints.push_back(targetPointName);
    }

    // 输入路线策略
    cout << "Enter 0 for shortest path strategy or 1 for shortest time strategy: ";
    cin >> strategy;
    if (strategy != 0 && strategy != 1) {
        cerr << "Error: Invalid strategy. Enter 0 for shortest path or 1 for shortest time." << endl;
        return ;
    }

    // 规划最优游学路线
    vector<Edge> finalPath;
    string currentPoint = startPointName;
    double totalDistance = 0.0;
    while (!targetPoints.empty()) {
        double minDistance = numeric_limits<double>::max();
        string nextPoint;
        vector<Edge> shortestPath;

        for (const string& target : targetPoints) {
            vector<Edge> path = dijkstra(adjList, points, currentPoint, target, strategy == 1);
            double pathDistance = path.back().distance;
            if (pathDistance < minDistance) {
                minDistance = pathDistance;
                nextPoint = target;
                shortestPath = path;
            }
        }

        if (!shortestPath.empty()) {
            finalPath.insert(finalPath.end(), shortestPath.begin() + 1, shortestPath.end());
            totalDistance += minDistance;
            currentPoint = nextPoint;
            targetPoints.erase(remove(targetPoints.begin(), targetPoints.end(), nextPoint), targetPoints.end());
        }
    }

    // 输出最终的游学路线
    cout << (strategy == 0 ? "Shortest path" : "Fastest path") << " for the tour:" << endl;
    stringstream pathStream;
    for (size_t i = 0; i < finalPath.size(); ++i) {
        cout << finalPath[i].dest.name << " (" << (strategy == 0 ? "distance: " : "time: ") << finalPath[i].distance << ")" << endl;
        pathStream << finalPath[i].dest.name << " (" << (strategy == 0 ? "distance: " : "time: ") << finalPath[i].distance << ")";
        if (i != finalPath.size() - 1) {
            pathStream << " -> ";
        }
    }
    cout << "Total " << (strategy == 0 ? "distance: " : "time: ") << totalDistance << endl;

    // 创建日志并保存
    Journal journal;
    journal.name = startPointName; // 修改日志名称为起始地点
    journal.content = "Route: " + startPointName + " -> " + pathStream.str();
    journal.views = 0;
    journal.rating = 0.0;
    journal.ratingsCount = 0;

    // 设置日志的目的地为所有目标地点的字符串表示形式
    journal.destination = pathStream.str();

    journals.push_back(journal);

    saveJournals("journals.txt");
    cout << "Route logged successfully." << endl;
}
