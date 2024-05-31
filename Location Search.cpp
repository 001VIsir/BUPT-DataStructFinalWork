#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include "Graph.h"

using namespace std;

int main() {
    ifstream file("inside_path.csv");
    string line;
    map<string, Point> points;
    int pointCount = 0;
    vector<vector<Edge>> adjList;

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
        Edge edge = { p2, stod(distance), stod(congestion) };
        adjList[p1.id].push_back(edge);
        edge.dest = p1;
        adjList[p2.id].push_back(edge);
    }

    string pointName, typeFilter;
    bool filterByType;
    cout << "Enter the name of the point: ";
    cin >> pointName;

    cout << "Do you want to filter by type? (1 for yes, 0 for no): ";
    cin >> filterByType;

    if (filterByType) {
        cout << "Enter the type of the points: ";
        cin >> typeFilter;
    }

    findNearbyPoints(adjList, points, pointName, 500, filterByType ? &typeFilter : nullptr);

    return 0;
}

