//
// Created by visir on 2024/5/30.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "user.h"

int loggedInUser = -1;// 当前登录的用户ID，-1表示没有用户登录
// 定义用户结构体，包含id、密码、姓名和指向下一个用户的指针
struct User {
    int account;
    std::string password;
    std::string name;
    User* next;
};
User* users[TABLE_SIZE] = {nullptr}; // 哈希表，初始化为null

// 从CSV文件中加载用户数据的函数

// 哈希函数，将用户ID映射到一个数组的索引
int hashFunction(int id) {
    return id % TABLE_SIZE;
}

// 注册新用户的函数
void registerUser() {
    User* newUser = new User; // 动态创建一个新的用户节点
    std::cout << "请输入ID: ";
    std::cin >> newUser->account; // 输入用户账号
    std::cout << "请输入密码: ";
    std::cin >> newUser->password; // 输入用户密码
    std::cout << "请输入姓名: ";
    std::cin >> newUser->name; // 输入用户姓名
    int index = hashFunction(newUser->account); // 计算哈希值
    newUser->next = users[index]; // 将新用户节点添加到链表的头部
    users[index] = newUser; // 更新头节点
}

// 用户登录的函数
void loginUser() {
    int id;
    std::string password;
    std::cout << "请输入ID: ";
    std::cin >> id; // 输入用户ID
    std::cout << "请输入密码: ";
    std::cin >> password; // 输入用户密码
    int index = hashFunction(id); // 计算哈希值
    for (User* user = users[index]; user != nullptr; user = user->next) { // 遍历链表
        if (user->account == id && user->password == password) { // 如果找到匹配的用户
            std::cout << "登录成功!\n";
            loggedInUser = id; // 更新当前登录的用户ID
            return;
        }
    }
    std::cout << "无效的ID或密码!\n"; // 如果没有找到匹配的用户，打印错误消息
}

// 用户注销的函数
void logoutUser() {
    if (loggedInUser != -1) { // 如果有用户登录
        std::cout << "用户已注销!\n";
        loggedInUser = -1; // 更新当前登录的用户ID为-1，表示没有用户登录
    } else {
        std::cout << "当前没有用户登录!\n"; // 如果没有用户登录，打印错误消息
    }
}

// 获取当前登录用户信息的函数
void getUserInfo() {
    if (loggedInUser != -1) { // 如果有用户登录
        int index = hashFunction(loggedInUser); // 计算哈希值
        for (User* user = users[index]; user != nullptr; user = user->next) { // 遍历链表
            if (user->account == loggedInUser) { // 如果找到匹配的用户
                std::cout << "用户ID: " << user->account << "\n"; // 打印用户ID
                std::cout << "用户姓名: " << user->name << "\n"; // 打印用户姓名
                return;
            }
        }
    } else {
        std::cout << "当前没有用户登录!\n"; // 如果没有用户登录，打印错误消息
    }
}




void loadUsersFromCSV() {
    std::ifstream file("C:\\Users\\visir\\Desktop\\shujvjiegou\\usertest.csv");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string accountStr, passwordStr, usernameStr;

            // 从流中读取每个字段
            std::getline(ss, accountStr, ','); // 读取 account
            std::getline(ss, passwordStr, ','); // 读取 password
            std::getline(ss, usernameStr);      // 读取 username

            // 将 account 字符串转换为整数
            int account = std::stoi(accountStr);

            // 创建 User 对象并初始化
            User* newUser = new User();
            newUser->account = account;
            newUser->password = passwordStr;
            newUser->name = usernameStr;

            // 计算哈希索引
            int index = hashFunction(account);

            // 将新用户插入到哈希表的链表中
            newUser->next = users[index];
            users[index] = newUser;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}


void printHashTable() {//测试用，打印哈希表看看有没有错误
    for (int i = 0; i < TABLE_SIZE; ++i) {
        User* current = users[i];
        while (current != nullptr) {
            std::cout << "Index: " << i << ", Account: " << current->account
                      << ", Password: " << current->password
                      << ", Name: " << current->name << std::endl;
            current = current->next; // 移动到链表的下一个节点
        }
    }
}

int log_user() {
    loadUsersFromCSV();
//    printHashTable();
    int choice;
    while (true) {

        if (loggedInUser == -1) { // 如果没有用户登录
            std::cout << "1. 注册\n2. 登录\n3. 退出\n请输入你的选择: ";
            std::cin >> choice; // 输入选择
            switch (choice) {
                case 1:
                    registerUser(); // 注册新用户
                    break;
                case 2:
                    loginUser(); // 用户登录
                    break;
                case 3:
                    return 0; // 退出程序
                default:
                    std::cout << "无效的选择!\n"; // 如果输入的选择无效，打印错误消息
            }
        } else { // 如果有用户登录
            std::cout << "1. 注销\n2. 查看用户信息\n3. 退出\n请输入你的选择: ";
            std::cin >> choice; // 输入选择
            switch (choice) {
                case 1:
                    logoutUser(); // 用户注销
                    break;
                case 2:
                    getUserInfo(); // 获取当前登录用户信息
                    break;
                case 3:
                    return 0; // 退出程序
                    break;
                default:
                    std::cout << "无效的选择!\n"; // 如果输入的选择无效，打印错误消息
            }
        }
    }

    return 1;
}


