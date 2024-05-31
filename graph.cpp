#include "Graph.h"

void bubbleSort(vector<Edge>& edges) {
    int n = edges.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (edges[j].distance > edges[j + 1].distance) {
                swap(edges[j], edges[j + 1]);
            }
        }
    }
}

vector<Edge> filterByType(const vector<Edge>& edges, const string& type) {
    vector<Edge> filteredEdges;
    for (const auto& edge : edges) {
        if (edge.dest.type == type) {
            filteredEdges.push_back(edge);
        }
    }
    return filteredEdges;
}

void findNearbyPoints(const vector<vector<Edge>>& adjList, const map<string, Point>& points, const string& pointName, double range, const string* typeFilter) {
    if (points.find(pointName) == points.end()) {
        cout << "Point " << pointName << " does not exist." << endl;
        return;
    }

    Point point = points.at(pointName);
    vector<Edge> nearbyPoints;

    for (const auto& edge : adjList[point.id]) {
        if (edge.distance <= range) {
            nearbyPoints.push_back(edge);
        }
    }

    if (typeFilter != nullptr) {
        nearbyPoints = filterByType(nearbyPoints, *typeFilter);
    }

    bubbleSort(nearbyPoints);

    cout << "Nearby points within " << range << " of point " << pointName;
    if (typeFilter != nullptr) {
        cout << " of type " << *typeFilter;
    }
    cout << ":" << endl;
    for (const auto& edge : nearbyPoints) {
        cout << "Point " << edge.dest.name << ", distance: " << edge.distance << ", congestion: " << edge.congestion << endl;
    }
}
