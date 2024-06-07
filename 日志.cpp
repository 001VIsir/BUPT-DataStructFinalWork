#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

struct Journal { // 定义日志结构体
    string name; // 日志名称
    string content; // 日志内容
    int views; // 日志浏览次数
    double rating; // 日志评分
    int ratingsCount; // 评分次数
    string destination; // 日志目的地
};

vector<Journal> journals; // 日志列表

struct Point { // 定义点结构体
    int id; // 点的ID
    string name; // 点的名称
    string type; // 点的类型
};

struct Edge { // 定义边结构体
    Point dest; // 边的目标点
    double distance; // 边的距离
    double time; // 边的时间
};

double idealSpeed = 5.0; // 理想速度

void loadJournals(const string& filePath) { // 从文件加载日志
    ifstream file(filePath); // 打开文件
    if (!file) { // 如果文件无法打开
        cerr << "Error opening file: " << filePath << endl; // 输出错误信息
        return; // 返回
    }

    string line; // 行字符串
    Journal journal; // 日志结构体
    while (getline(file, line)) { // 逐行读取文件
        if (line == "JOURNAL") { // 如果行是"JOURNAL"
            if (!journal.name.empty()) { // 如果日志名称不为空
                journals.push_back(journal); // 将日志添加到列表
            }
            journal = Journal(); // 重置日志
        }
        else if (line.substr(0, 5) == "NAME:") { // 如果行以"NAME:"开头
            journal.name = line.substr(5); // 提取名称
        }
        else if (line.substr(0, 8) == "CONTENT:") { // 如果行以"CONTENT:"开头
            journal.content = line.substr(8); // 提取内容
        }
        else if (line.substr(0, 6) == "VIEWS:") { // 如果行以"VIEWS:"开头
            journal.views = stoi(line.substr(6)); // 提取浏览次数
        }
        else if (line.substr(0, 7) == "RATING:") { // 如果行以"RATING:"开头
            journal.rating = stod(line.substr(7)); // 提取评分
        }
        else if (line.substr(0, 13) == "RATINGS_COUNT:") { // 如果行以"RATINGS_COUNT:"开头
            journal.ratingsCount = stoi(line.substr(13)); // 提取评分次数
        }
        else if (line.substr(0, 11) == "DESTINATION:") { // 如果行以"DESTINATION:"开头
            journal.destination = line.substr(11); // 提取目的地
        }
    }
    if (!journal.name.empty()) { // 如果日志名称不为空
        journals.push_back(journal); // 将日志添加到列表
    }
    file.close(); // 关闭文件
}

void saveJournals(const string& filePath) { // 将日志保存到文件
    ofstream file(filePath); // 打开文件
    if (!file) { // 如果文件无法打开
        cerr << "Error opening file: " << filePath << endl; // 输出错误信息
        return; // 返回
    }

    for (const auto& journal : journals) { // 遍历日志列表
        file << "JOURNAL\n"; // 写入"JOURNAL"
        file << "NAME:" << journal.name << "\n"; // 写入日志名称
        file << "CONTENT:" << journal.content << "\n"; // 写入日志内容
        file << "VIEWS:" << journal.views << "\n"; // 写入浏览次数
        file << "RATING:" << journal.rating << "\n"; // 写入评分
        file << "RATINGS_COUNT:" << journal.ratingsCount << "\n"; // 写入评分次数
        file << "DESTINATION:" << journal.destination << "\n"; // 写入目的地
    }
    file.close(); // 关闭文件
}

void displayJournalCount() { // 显示日志数量
    cout << "Number of journals: " << journals.size() << endl; // 输出日志数量
}

void browseAndQueryJournals() { // 浏览和查询日志
    string query; // 查询字符串
    cout << "Enter journal name to search (or leave blank to browse all): "; // 提示输入日志名称
    getline(cin, query); // 读取查询字符串

    for (const auto& journal : journals) { // 遍历日志列表
        if (query.empty() || journal.name == query) { // 如果查询字符串为空或日志名称匹配
            cout << "Name: " << journal.name << endl; // 输出日志名称
            cout << "Content: " << journal.content << endl; // 输出日志内容
            cout << "Views: " << journal.views << endl; // 输出浏览次数
            cout << "Rating: " << journal.rating << endl; // 输出评分
            cout << "Destination: " << journal.destination << endl; // 输出目的地
            cout << endl; // 输出空行
        }
    }
}

void rateJournal() { // 评分日志
    string journalName; // 日志名称
    double rating; // 评分
    cout << "Enter the name of the journal to rate: "; // 提示输入日志名称
    getline(cin, journalName); // 读取日志名称

    auto it = find_if(journals.begin(), journals.end(), [&](const Journal& j) { // 查找日志
        return j.name == journalName;
        });

    if (it != journals.end()) { // 如果找到日志
        cout << "Enter your rating (1-5): "; // 提示输入评分
        cin >> rating; // 读取评分
        cin.ignore(); // 忽略输入缓冲区的换行符

        it->rating = (it->rating * it->ratingsCount + rating) / (it->ratingsCount + 1); // 计算新的平均评分
        it->ratingsCount++; // 增加评分次数
        cout << "Journal rated successfully." << endl; // 输出评分成功信息
    }
    else { // 如果未找到日志
        cout << "Journal not found." << endl; // 输出未找到信息
    }
}

void recommendJournals() { // 推荐日志
    vector<Journal> sortedJournals = journals; // 复制日志列表
    sort(sortedJournals.begin(), sortedJournals.end(), [](const Journal& a, const Journal& b) { // 按热度和评分排序
        if (a.views != b.views) {
            return a.views > b.views;
        }
        else {
            return a.rating > b.rating;
        }
        });

    cout << "Recommended journals:" << endl; // 输出推荐日志
    for (const auto& journal : sortedJournals) { // 遍历排序后的日志列表
        cout << "Name: " << journal.name << endl; // 输出日志名称
        cout << "Views: " << journal.views << endl; // 输出浏览次数
        cout << "Rating: " << journal.rating << endl; // 输出评分
        cout << endl; // 输出空行
    }
}

void sortJournalsByDestination() { // 按目的地排序日志
    string destination; // 目的地字符串
    cout << "Enter destination to sort by: "; // 提示输入目的地
    getline(cin, destination); // 读取目的地

    vector<Journal> destinationJournals; // 存储匹配目的地的日志列表
    for (const auto& journal : journals) { // 遍历日志列表
        if (journal.destination == destination) { // 如果目的地匹配
            destinationJournals.push_back(journal); // 添加到列表
        }
    }

    sort(destinationJournals.begin(), destinationJournals.end(), [](const Journal& a, const Journal& b) { // 按热度和评分排序
        if (a.views != b.views) {
            return a.views > b.views;
        }
        else {
            return a.rating > b.rating;
        }
        });

    cout << "Journals sorted by destination:" << endl; // 输出按目的地排序的日志
    for (const auto& journal : destinationJournals) { // 遍历排序后的日志列表
        cout << "Name: " << journal.name << endl; // 输出日志名称
        cout << "Views: " << journal.views << endl; // 输出浏览次数
        cout << "Rating: " << journal.rating << endl; // 输出评分
        cout << endl; // 输出空行
    }
}

void searchJournalsByContent() { // 根据内容搜索日志
    string searchTerm; // 搜索字符串
    cout << "Enter search term: "; // 提示输入搜索字符串
    getline(cin, searchTerm); // 读取搜索字符串

    for (const auto& journal : journals) { // 遍历日志列表
        if (journal.content.find(searchTerm) != string::npos) { // 如果内容中包含搜索字符串
            cout << "Name: " << journal.name << endl; // 输出日志名称
            cout << "Content: " << journal.content << endl; // 输出日志内容
            cout << endl; // 输出空行
        }
    }
}

void saveJournalToFile(const Journal& journal, const string& filePath) { // 将日志保存到文件
    ofstream file(filePath, ios::app); // 以追加模式打开文件
    if (file.is_open()) { // 如果文件打开成功
        file << "Name: " << journal.name << endl; // 写入日志名称
        file << "Content: " << journal.content << endl; // 写入日志内容
        file << "Views: " << journal.views << endl; // 写入浏览次数
        file << "Rating: " << journal.rating << endl; // 写入评分
        file << "Ratings Count: " << journal.ratingsCount << endl; // 写入评分次数
        file << "Destination: " << journal.destination << endl; // 写入目的地
        file << "-------------------------" << endl; // 添加分割线
        file.close(); // 关闭文件
        cout << "Journal saved to " << filePath << endl; // 输出保存成功信息
    }
    else { // 如果文件打开失败
        cerr << "Unable to open file for writing." << endl; // 输出错误信息
    }
}

// 最小堆的操作函数

// 下沉操作，用于维持堆的性质
void heapifyDown(vector<pair<double, int>>& heap, int size, int i) {
    int minIndex = i; // 初始化最小值索引为当前索引
    int l = 2 * i + 1; // 左子节点索引
    int r = 2 * i + 2; // 右子节点索引
    if (l < size && heap[l].first < heap[minIndex].first) { // 如果左子节点存在且小于当前最小值
        minIndex = l; // 更新最小值索引为左子节点索引
    }
    if (r < size && heap[r].first < heap[minIndex].first) { // 如果右子节点存在且小于当前最小值
        minIndex = r; // 更新最小值索引为右子节点索引
    }
    if (minIndex != i) { // 如果最小值索引不等于当前索引
        swap(heap[i], heap[minIndex]); // 交换当前节点和最小值节点
        heapifyDown(heap, size, minIndex); // 递归调整堆
    }
}

// 上浮操作，用于维持堆的性质
void heapifyUp(vector<pair<double, int>>& heap, int i) {
    while (i > 0 && heap[(i - 1) / 2].first > heap[i].first) { // 如果当前节点不是根节点且父节点大于当前节点
        swap(heap[i], heap[(i - 1) / 2]); // 交换当前节点和父节点
        i = (i - 1) / 2; // 更新当前节点索引为父节点索引
    }
}

// 插入元素到堆中
void pushHeap(vector<pair<double, int>>& heap, int& size, pair<double, int> value) {
    heap.push_back(value); // 将元素加入堆末尾
    size++; // 堆大小加1
    heapifyUp(heap, size - 1); // 调整堆，保持最小堆性质
}

// 从堆中取出最小元素
pair<double, int> popHeap(vector<pair<double, int>>& heap, int& size) {
    if (size == 0) { // 如果堆为空
        return make_pair(numeric_limits<double>::max(), -1); // 返回一个无穷大的数值对
    }
    pair<double, int> root = heap[0]; // 获取堆顶元素
    heap[0] = heap[size - 1]; // 将堆尾元素移到堆顶
    size--; // 堆大小减1
    heapifyDown(heap, size, 0); // 调整堆，保持最小堆性质
    return root; // 返回堆顶元素
}

// Dijkstra算法实现
vector<Edge> dijkstra(const vector<vector<Edge>>& adjList, const map<string, Point>& points, const string& startPointName, const string& endPointName, bool useTime) {
    int src = points.at(startPointName).id; // 起始点的编号
    int dest = points.at(endPointName).id; // 目标点的编号
    int n = adjList.size(); // 图中节点的数量
    vector<double> dist(n, numeric_limits<double>::max()); // 从起始点到各节点的距离/时间
    vector<int> prev(n, -1); // 最短路径的前驱节点
    vector<pair<double, int>> heap; // 最小堆用于Dijkstra算法
    int heapSize = 0;

    dist[src] = 0; // 起始点到自身的距离为0
    pushHeap(heap, heapSize, { 0, src }); // 将起始点加入优先队列

    // Dijkstra算法核心部分
    while (heapSize > 0) { // 当堆不为空时
        int u = popHeap(heap, heapSize).second; // 获取当前距离起始点最近的节点

        // 遍历当前节点的所有邻居
        for (const auto& edge : adjList[u]) {
            int v = edge.dest.id; // 邻居节点的编号
            double weight = useTime ? edge.time : edge.distance; // 根据useTime判断权重类型

            // 松弛操作：如果通过当前节点u到节点v的距离/时间更短，则更新距离/时间，并将v加入队列
            if (dist[u] + weight < dist[v]) { // 如果通过当前节点u到节点v的距离/时间更短
                dist[v] = dist[u] + weight; // 更新距离/时间
                prev[v] = u; // 更新前驱节点
                pushHeap(heap, heapSize, { dist[v], v }); // 将节点v加入堆中
            }
        }
    }

    // 构造最短路径
    vector<Edge> path; // 存储最短路径的边
    int current = dest; // 当前节点为目标节点
    while (current != -1) { // 如果当前节点不是起始节点
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

void planRouteAndLog() { // 路径规划并生成日志
    ifstream file("inside_path.csv"); // 打开CSV文件
    string line; // 用于存储每一行数据的字符串
    map<string, Point> points; // 存储点的映射
    int pointCount = 0; // 点的计数器
    vector<vector<Edge>> adjList; // 邻接表表示图

    // 读取并丢弃第一行（表头）
    getline(file, line);

    // 逐行读取CSV文件内容
    while (getline(file, line)) {
        stringstream ss(line); // 创建字符串流
        string point1, point2, distance, congestion; // 用于存储每列数据的字符串
        getline(ss, point1, ','); // 读取第一列（起始点）
        getline(ss, point2, ','); // 读取第二列（目标点）
        getline(ss, distance, ','); // 读取第三列（距离）
        getline(ss, congestion, ','); // 读取第四列（拥堵程度）

        // 提取点的类型
        string type1 = point1.substr(0, point1.find_first_of("0123456789"));
        string type2 = point2.substr(0, point2.find_first_of("0123456789"));

        // 如果点1不在映射中，则添加
        if (points.find(point1) == points.end()) {
            points[point1] = { pointCount++, point1, type1 }; // 创建Point结构体并赋值
            adjList.resize(pointCount); // 调整邻接表大小
        }

        // 如果点2不在映射中，则添加
        if (points.find(point2) == points.end()) {
            points[point2] = { pointCount++, point2, type2 }; // 创建Point结构体并赋值
            adjList.resize(pointCount); // 调整邻接表大小
        }

        Point p1 = points[point1]; // 获取点1的结构体
        Point p2 = points[point2]; // 获取点2的结构体
        double dist = stod(distance); // 将距离字符串转换为double类型
        double time = dist / (stod(congestion) * idealSpeed); // 计算时间

        // 创建边结构体并赋值
        Edge edge1 = { p2, dist, time };
        Edge edge2 = { p1, dist, time };
        adjList[p1.id].push_back(edge1); // 将边添加到邻接表
        adjList[p2.id].push_back(edge2); // 将边添加到邻接表
    }

    // 输入当前位置名称
    string startPointName;
    cout << "Enter the name of the starting point: "; // 提示输入起始点名称
    cin >> startPointName; // 读取起始点名称
    if (points.find(startPointName) == points.end()) { // 如果起始点不在映射中
        cerr << "Error: Starting point '" << startPointName << "' does not exist." << endl; // 输出错误信息
        return; // 终止函数执行
    }

    int strategy; // 路线策略
    // 输入多个目标地点名称
    vector<string> targetPoints; // 存储目标地点的向量
    string targetPointName; // 目标地点名称
    cout << "Enter the names of the target points (enter 'done' to finish): "; // 提示输入目标地点
    while (cin >> targetPointName && targetPointName != "done") { // 读取目标地点名称，直到输入'done'
        if (points.find(targetPointName) == points.end()) { // 如果目标地点不在映射中
            cerr << "Error: Target point '" << targetPointName << "' does not exist." << endl; // 输出错误信息
            return; // 终止函数执行
        }
        targetPoints.push_back(targetPointName); // 将目标地点添加到向量
    }

    // 输入路线策略
    cout << "Enter 0 for shortest path strategy or 1 for shortest time strategy: "; // 提示输入路线策略
    cin >> strategy; // 读取路线策略
    if (strategy != 0 && strategy != 1) { // 如果策略不是0或1
        cerr << "Error: Invalid strategy. Enter 0 for shortest path or 1 for shortest time." << endl; // 输出错误信息
        return; // 终止函数执行
    }

    // 规划最优游学路线
    vector<Edge> finalPath; // 存储最终路径的边
    string currentPoint = startPointName; // 当前节点设置为起始点
    double totalDistance = 0.0; // 总距离初始化为0
    while (!targetPoints.empty()) { // 当目标地点不为空时
        double minDistance = numeric_limits<double>::max(); // 最小距离初始化为最大值
        string nextPoint; // 下一个目标地点
        vector<Edge> shortestPath; // 最短路径

        for (const string& target : targetPoints) { // 遍历所有目标地点
            vector<Edge> path = dijkstra(adjList, points, currentPoint, target, strategy == 1); // 使用Dijkstra算法计算路径
            double pathDistance = path.back().distance; // 获取路径距离
            if (pathDistance < minDistance) { // 如果路径距离小于最小距离
                minDistance = pathDistance; // 更新最小距离
                nextPoint = target; // 更新下一个目标地点
                shortestPath = path; // 更新最短路径
            }
        }

        if (!shortestPath.empty()) { // 如果最短路径不为空
            finalPath.insert(finalPath.end(), shortestPath.begin() + 1, shortestPath.end()); // 将最短路径添加到最终路径中
            totalDistance += minDistance; // 更新总距离
            currentPoint = nextPoint; // 更新当前节点
            targetPoints.erase(remove(targetPoints.begin(), targetPoints.end(), nextPoint), targetPoints.end()); // 从目标地点中移除已到达的目标
        }
    }

    // 输出最终的游学路线
    cout << (strategy == 0 ? "Shortest path" : "Fastest path") << " for the tour:" << endl; // 根据策略输出路径类型
    stringstream pathStream; // 创建字符串流用于路径日志
    for (size_t i = 0; i < finalPath.size(); ++i) { // 遍历最终路径的每一条边
        cout << finalPath[i].dest.name << " (" << (strategy == 0 ? "distance: " : "time: ") << finalPath[i].distance << ")" << endl; // 输出边信息
        pathStream << finalPath[i].dest.name << " (" << (strategy == 0 ? "distance: " : "time: ") << finalPath[i].distance << ")"; // 添加边信息到字符串流
        if (i != finalPath.size() - 1) { // 如果不是最后一条边
            pathStream << " -> "; // 添加箭头
        }
    }
    cout << "Total " << (strategy == 0 ? "distance: " : "time: ") << totalDistance << endl; // 输出总距离或总时间

    // 创建日志并保存
    Journal journal; // 创建日志对象
    journal.name = startPointName; // 修改日志名称为起始地点
    journal.content = "Route: " + startPointName + " -> " + pathStream.str(); // 设置日志内容
    journal.views = 0; // 日志初始浏览次数为0
    journal.rating = 0.0; // 日志初始评分为0.0
    journal.ratingsCount = 0; // 日志初始评分人数为0

    // 设置日志的目的地为所有目标地点的字符串表示形式
    journal.destination = pathStream.str(); // 设置日志目的地

    journals.push_back(journal); // 将日志添加到日志列表

    saveJournals("journals.txt"); // 保存日志到文件
    cout << "Route logged successfully." << endl; // 输出日志保存成功信息
}


int main() { // 主函数
    // 加载已有日志
    loadJournals("journals.txt"); // 从文件加载日志

    int choice; // 用户选择的选项
    do { // 循环显示菜单并处理用户选择
        cout << "\n菜单:\n"; // 输出菜单
        cout << "1. 加载日志\n"; // 菜单选项1: 加载日志
        cout << "2. 保存日志\n"; // 菜单选项2: 保存日志
        cout << "3. 显示日志数量\n"; // 菜单选项3: 显示日志数量
        cout << "4. 浏览和查询日志\n"; // 菜单选项4: 浏览和查询日志
        cout << "5. 评分日志\n"; // 菜单选项5: 评分日志
        cout << "6. 推荐日志\n"; // 菜单选项6: 推荐日志
        cout << "7. 按目的地排序日志\n"; // 菜单选项7: 按目的地排序日志
        cout << "8. 按内容搜索日志\n"; // 菜单选项8: 按内容搜索日志
        cout << "9. 规划路径并生成日志\n"; // 菜单选项9: 规划路径并生成日志
        cout << "10. 退出\n"; // 菜单选项10: 退出程序
        cout << "请输入你的选择: "; // 提示用户输入选择
        cin >> choice; // 读取用户选择
        cin.ignore(); // 忽略输入缓冲区的换行符

        switch (choice) { // 根据用户选择执行不同的操作
        case 1: // 选项1: 加载日志
            loadJournals("journals.txt"); // 从文件加载日志
            break;
        case 2: // 选项2: 保存日志
            saveJournals("journals.txt"); // 将日志保存到文件
            break;
        case 3: // 选项3: 显示日志数量
            displayJournalCount(); // 显示日志数量
            break;
        case 4: // 选项4: 浏览和查询日志
            browseAndQueryJournals(); // 浏览和查询日志
            break;
        case 5: // 选项5: 评分日志
            rateJournal(); // 评分日志
            break;
        case 6: // 选项6: 推荐日志
            recommendJournals(); // 推荐日志
            break;
        case 7: // 选项7: 按目的地排序日志
            sortJournalsByDestination(); // 按目的地排序日志
            break;
        case 8: // 选项8: 按内容搜索日志
            searchJournalsByContent(); // 按内容搜索日志
            break;
        case 9: // 选项9: 规划路径并生成日志
            planRouteAndLog(); // 规划路径并生成日志
            break;
        case 10: // 选项10: 退出程序
            cout << "Exiting..." << endl; // 输出退出信息
            break;
        default: // 处理无效的选择
            cout << "Invalid choice. Please try again." << endl; // 提示无效选择
        }
    } while (choice != 10); // 如果选择不是10，则继续循环

    return 0; // 返回0，表示程序成功结束
}

