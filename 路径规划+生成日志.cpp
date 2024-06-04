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

    // 输入地点名称
    string pointName1, pointName2;
    cout << "Enter the name of the starting point: ";
    cin >> pointName1;
    if (points.find(pointName1) == points.end()) {
        cerr << "Error: Starting point '" << pointName1 << "' does not exist." << endl;
        return;
    }

    cout << "Enter the name of the destination point: ";
    cin >> pointName2;
    if (points.find(pointName2) == points.end()) {
        cerr << "Error: Destination point '" << pointName2 << "' does not exist." << endl;
        return;
    }

    // 输入路线策略
    int strategy;
    cout << "Enter 0 for shortest path strategy or 1 for shortest time strategy: ";
    cin >> strategy;
    if (strategy != 0 && strategy != 1) {
        cerr << "Error: Invalid strategy. Enter 0 for shortest path or 1 for shortest time." << endl;
        return;
    }

    // 根据选择的策略找出路径
    vector<Edge> path = dijkstra(adjList, points, pointName1, pointName2, strategy == 1);
    cout << (strategy == 0 ? "Shortest path" : "Fastest path") << " from " << pointName1 << " to " << pointName2 << ":" << endl;

    stringstream pathStream;
    for (const auto& edge : path) {
        cout << edge.dest.name << " (" << (strategy == 0 ? "distance: " : "time: ") << edge.distance << ")" << endl;
        pathStream << edge.dest.name << " (" << (strategy == 0 ? "distance: " : "time: ") << edge.distance << "), ";
    }

    // 创建日志并保存
    Journal journal;
    journal.name = "Path from " + pointName1 + " to " + pointName2;
    journal.content = pathStream.str();
    journal.views = 0;
    journal.rating = 0.0;
    journal.ratingsCount = 0;
    journal.destination = pointName2;
    journals.push_back(journal);

    saveJournals("journals.txt");
    cout << "Route logged successfully." << endl;
}