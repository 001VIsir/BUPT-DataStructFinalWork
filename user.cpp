//
// Created by visir on 2024/5/30.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "user.h"

int loggedInUser = -1;// ��ǰ��¼���û�ID��-1��ʾû���û���¼
// �����û��ṹ�壬����id�����롢������ָ����һ���û���ָ��
struct User {
    int account;
    std::string password;
    std::string name;
    User* next;
};
User* users[TABLE_SIZE] = {nullptr}; // ��ϣ����ʼ��Ϊnull

// ��CSV�ļ��м����û����ݵĺ���

// ��ϣ���������û�IDӳ�䵽һ�����������
int hashFunction(int id) {
    return id % TABLE_SIZE;
}

// ע�����û��ĺ���
void registerUser() {
    User* newUser = new User; // ��̬����һ���µ��û��ڵ�
    std::cout << "������ID: ";
    std::cin >> newUser->account; // �����û��˺�
    std::cout << "����������: ";
    std::cin >> newUser->password; // �����û�����
    std::cout << "����������: ";
    std::cin >> newUser->name; // �����û�����
    int index = hashFunction(newUser->account); // �����ϣֵ
    newUser->next = users[index]; // �����û��ڵ���ӵ������ͷ��
    users[index] = newUser; // ����ͷ�ڵ�
}

// �û���¼�ĺ���
void loginUser() {
    int id;
    std::string password;
    std::cout << "������ID: ";
    std::cin >> id; // �����û�ID
    std::cout << "����������: ";
    std::cin >> password; // �����û�����
    int index = hashFunction(id); // �����ϣֵ
    for (User* user = users[index]; user != nullptr; user = user->next) { // ��������
        if (user->account == id && user->password == password) { // ����ҵ�ƥ����û�
            std::cout << "��¼�ɹ�!\n";
            loggedInUser = id; // ���µ�ǰ��¼���û�ID
            return;
        }
    }
    std::cout << "��Ч��ID������!\n"; // ���û���ҵ�ƥ����û�����ӡ������Ϣ
}

// �û�ע���ĺ���
void logoutUser() {
    if (loggedInUser != -1) { // ������û���¼
        std::cout << "�û���ע��!\n";
        loggedInUser = -1; // ���µ�ǰ��¼���û�IDΪ-1����ʾû���û���¼
    } else {
        std::cout << "��ǰû���û���¼!\n"; // ���û���û���¼����ӡ������Ϣ
    }
}

// ��ȡ��ǰ��¼�û���Ϣ�ĺ���
void getUserInfo() {
    if (loggedInUser != -1) { // ������û���¼
        int index = hashFunction(loggedInUser); // �����ϣֵ
        for (User* user = users[index]; user != nullptr; user = user->next) { // ��������
            if (user->account == loggedInUser) { // ����ҵ�ƥ����û�
                std::cout << "�û�ID: " << user->account << "\n"; // ��ӡ�û�ID
                std::cout << "�û�����: " << user->name << "\n"; // ��ӡ�û�����
                return;
            }
        }
    } else {
        std::cout << "��ǰû���û���¼!\n"; // ���û���û���¼����ӡ������Ϣ
    }
}




void loadUsersFromCSV() {
    std::ifstream file("C:\\Users\\visir\\Desktop\\shujvjiegou\\usertest.csv");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string accountStr, passwordStr, usernameStr;

            // �����ж�ȡÿ���ֶ�
            std::getline(ss, accountStr, ','); // ��ȡ account
            std::getline(ss, passwordStr, ','); // ��ȡ password
            std::getline(ss, usernameStr);      // ��ȡ username

            // �� account �ַ���ת��Ϊ����
            int account = std::stoi(accountStr);

            // ���� User ���󲢳�ʼ��
            User* newUser = new User();
            newUser->account = account;
            newUser->password = passwordStr;
            newUser->name = usernameStr;

            // �����ϣ����
            int index = hashFunction(account);

            // �����û����뵽��ϣ���������
            newUser->next = users[index];
            users[index] = newUser;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}


void printHashTable() {//�����ã���ӡ��ϣ������û�д���
    for (int i = 0; i < TABLE_SIZE; ++i) {
        User* current = users[i];
        while (current != nullptr) {
            std::cout << "Index: " << i << ", Account: " << current->account
                      << ", Password: " << current->password
                      << ", Name: " << current->name << std::endl;
            current = current->next; // �ƶ����������һ���ڵ�
        }
    }
}

int log_user() {
    loadUsersFromCSV();
//    printHashTable();
    int choice;
    while (true) {

        if (loggedInUser == -1) { // ���û���û���¼
            std::cout << "1. ע��\n2. ��¼\n3. �˳�\n���������ѡ��: ";
            std::cin >> choice; // ����ѡ��
            switch (choice) {
                case 1:
                    registerUser(); // ע�����û�
                    break;
                case 2:
                    loginUser(); // �û���¼
                    break;
                case 3:
                    return 0; // �˳�����
                default:
                    std::cout << "��Ч��ѡ��!\n"; // ��������ѡ����Ч����ӡ������Ϣ
            }
        } else { // ������û���¼
            std::cout << "1. ע��\n2. �鿴�û���Ϣ\n3. �˳�\n���������ѡ��: ";
            std::cin >> choice; // ����ѡ��
            switch (choice) {
                case 1:
                    logoutUser(); // �û�ע��
                    break;
                case 2:
                    getUserInfo(); // ��ȡ��ǰ��¼�û���Ϣ
                    break;
                case 3:
                    return 0; // �˳�����
                    break;
                default:
                    std::cout << "��Ч��ѡ��!\n"; // ��������ѡ����Ч����ӡ������Ϣ
            }
        }
    }

    return 1;
}


