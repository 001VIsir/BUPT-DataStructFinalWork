//
// Created by visir on 2024/5/30.
//
#include <iostream>
#include <string>
#include "user.h"

// 定义用户结构体，包含id、密码、姓名和指向下一个用户的指针
struct User {
    int id;
    std::string password;
    std::string name;
    User* next;
};

const int TABLE_SIZE = 100; // 哈希表的大小
User* users[TABLE_SIZE] = {nullptr}; // 哈希表，初始化为null
int loggedInUser = -1; // 当前登录的用户ID，-1表示没有用户登录


// 哈希函数，将用户ID映射到一个数组的索引
int hashFunction(int id) {
    return id % TABLE_SIZE;
}

// 注册新用户的函数
void registerUser() {
    User* newUser = new User; // 动态创建一个新的用户节点
    std::cout << "请输入ID: ";
    std::cin >> newUser->id; // 输入用户ID
    std::cout << "请输入密码: ";
    std::cin >> newUser->password; // 输入用户密码
    std::cout << "请输入姓名: ";
    std::cin >> newUser->name; // 输入用户姓名
    int index = hashFunction(newUser->id); // 计算哈希值
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
        if (user->id == id && user->password == password) { // 如果找到匹配的用户
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
            if (user->id == loggedInUser) { // 如果找到匹配的用户
                std::cout << "用户ID: " << user->id << "\n"; // 打印用户ID
                std::cout << "用户姓名: " << user->name << "\n"; // 打印用户姓名
                return;
            }
        }
    } else {
        std::cout << "当前没有用户登录!\n"; // 如果没有用户登录，打印错误消息
    }
}

int log_user() {
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
//                    loggedInUser = 0;
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
//                    loggedInUser = -1;
                    break;
                case 2:
                    getUserInfo(); // 获取当前登录用户信息
                    break;
                case 3:
//                    loggedInUser = -1;
                    return 0; // 退出程序
                    break;
                default:
                    std::cout << "无效的选择!\n"; // 如果输入的选择无效，打印错误消息
            }
        }
    }

    return 1;
}
