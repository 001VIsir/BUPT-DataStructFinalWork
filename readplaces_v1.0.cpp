#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 定义一个结构体来保存景点的信息
struct Place {
    int id;
    string name;
    string type;
    int popularity;
    double score;
};

int main() {
    ifstream file("places.csv"); // 打开CSV文件

    if (!file.good()) {
        cout << "无法打开文件" << endl;
        return 1; // 如果无法打开文件，返回错误代码
    }

    const int MAX_PLACES = 1000; // 假设最多有1000个景点
    Place places[MAX_PLACES]; // 创建一个Place结构体的数组来保存数据
    int placeCount = 0; // 记录已经读取的景点数量

    string line;
    getline(file, line); // 读取并丢弃标题行

    while (getline(file, line) && placeCount < MAX_PLACES) { // 逐行读取文件
        stringstream ss(line);
        Place& place = places[placeCount];

        string field;
        getline(ss, field, ','); // 使用逗号作为分隔符
        place.id = stoi(field);

        getline(ss, place.name, ',');
        getline(ss, place.type, ',');

        getline(ss, field, ',');
        place.popularity = stoi(field);

        getline(ss, field, ',');
        place.score = stod(field);

        placeCount++; // 增加已经读取的景点数量
    }

    if (!file.eof()) {
        cout << "在读取文件时出现错误" << endl;
        return 1; // 如果在读取过程中出现错误，返回错误代码
    }

    // 打印读取到的数据
    for (int i = 0; i < placeCount; i++) {
        const Place& place = places[i];
        cout << "ID: " << place.id << ", Name: " << place.name << ", Type: " << place.type
            << ", Popularity: " << place.popularity << ", Score: " << place.score << endl;
    }

    return 0;
}
