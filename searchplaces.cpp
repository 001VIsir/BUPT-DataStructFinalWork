#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

struct Place {
    int id;
    std::string name;
    std::string type;
    int popularity;
    double score;
};

// 枚举类型，用于指定排序的依据
enum class SortField {
    Popularity,
    Score
};

// 函数原型
bool readPlacesFromFile(const std::string& filename, std::vector<Place>& places);
void printPlaces(const std::vector<Place>& places);
std::vector<Place> searchPlaces(const std::vector<Place>& places, const std::string& keyword, const std::string& type);
void sortPlaces(std::vector<Place>& places, SortField sortField);
bool isValidType(const std::vector<Place>& places, const std::string& type);
void queryAndSortPlaces(const std::vector<Place>& places);

// 从文件中读取地点数据
bool readPlacesFromFile(const std::string& filename, std::vector<Place>& places) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法打开文件" << std::endl;
        return false;
    }

    std::string line;
    getline(file, line); // 读取并丢弃标题行

    while (getline(file, line)) {
        std::stringstream ss(line);
        Place place;

        std::string field;
        getline(ss, field, ',');
        place.id = std::stoi(field);

        getline(ss, place.name, ',');
        getline(ss, place.type, ',');

        getline(ss, field, ',');
        place.popularity = std::stoi(field);

        getline(ss, field, ',');
        place.score = std::stod(field);

        places.push_back(place);
    }

    if (!file.eof()) {
        std::cout << "在读取文件时出现错误" << std::endl;
        return false;
    }

    file.close();
    return true;
}

// 打印地点数据
void printPlaces(const std::vector<Place>& places) {
    for (const auto& place : places) {
        std::cout << "ID: " << place.id << ", Name: " << place.name << ", Type: " << place.type
            << ", Popularity: " << place.popularity << ", Score: " << place.score << std::endl;
    }
}

// 查询地点
std::vector<Place> searchPlaces(const std::vector<Place>& places, const std::string& keyword, const std::string& type) {
    std::vector<Place> result;
    for (const auto& place : places) {
        if (place.name.find(keyword) != std::string::npos && place.type == type) {
            result.push_back(place);
        }
    }
    return result;
}

// 自定义排序算法（基于冒泡排序）
void bubbleSort(std::vector<Place>& places, SortField sortField) {
    bool swapped;
    for (size_t i = 0; i < places.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < places.size() - i - 1; j++) {
            bool condition = false;
            if (sortField == SortField::Popularity) {
                condition = places[j].popularity < places[j + 1].popularity;
            }
            else if (sortField == SortField::Score) {
                condition = places[j].score < places[j + 1].score;
            }
            if (condition) {
                std::swap(places[j], places[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 排序地点
void sortPlaces(std::vector<Place>& places, SortField sortField) {
    bubbleSort(places, sortField);
}

// 验证类型是否存在
bool isValidType(const std::vector<Place>& places, const std::string& type) {
    std::unordered_set<std::string> types;
    for (const auto& place : places) {
        types.insert(place.type);
    }
    return types.find(type) != types.end();
}

// 查询并排序地点
void queryAndSortPlaces(const std::vector<Place>& places) {
    std::string keyword, type;
    std::cout << "请输入查询关键词: ";
    std::cin >> keyword;
    std::cout << "请输入查询类别: ";
    std::cin >> type;

    // 验证输入的类型是否存在
    if (!isValidType(places, type)) {
        std::cout << "错误：输入的类别不存在。" << std::endl;
        return;
    }

    // 查询地点
    std::vector<Place> searchResult = searchPlaces(places, keyword, type);
    if (searchResult.empty()) {
        std::cout << "没有找到匹配的地点。" << std::endl;
        return;
    }

    // 用户选择排序依据
    int sortChoice;
    std::cout << "请选择排序依据（0: Popularity, 1: Score）: ";
    std::cin >> sortChoice;
    if (sortChoice != 0 && sortChoice != 1) {
        std::cout << "错误：无效的排序选择。" << std::endl;
        return;
    }
    SortField sortField = (sortChoice == 0) ? SortField::Popularity : SortField::Score;

    // 排序地点
    sortPlaces(searchResult, sortField);

    // 打印排序后的地点数据
    std::cout << "排序后的地点数据：" << std::endl;
    printPlaces(searchResult);
}

int main() {
    std::vector<Place> places;

    std::string filename = "newplaces.csv"; // 假设数据存储在newplaces.csv文件中

    // 从文件中读取地点数据
    if (readPlacesFromFile(filename, places)) {
        std::cout << "成功读取 " << places.size() << " 个地点数据。" << std::endl;
        queryAndSortPlaces(places);
    }
    else {
        std::cout << "读取文件失败。" << std::endl;
    }

    return 0;
}

