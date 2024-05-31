#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Point {
    int id;
    string name;
    string type;
};

struct Edge {
    Point dest;
    double distance;
    double congestion;
};

void bubbleSort(vector<Edge>& edges);

vector<Edge> filterByType(const vector<Edge>& edges, const string& type);

void findNearbyPoints(const vector<vector<Edge>>& adjList, const map<string, Point>& points, const string& pointName, double range, const string* typeFilter);

#endif // GRAPH_H
