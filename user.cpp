//
// Created by visir on 2024/5/30.
//
#include <iostream>
#include <string>
#include "user.h"

// �����û��ṹ�壬����id�����롢������ָ����һ���û���ָ��
struct User {
    int id;
    std::string password;
    std::string name;
    User* next;
};

const int TABLE_SIZE = 100; // ��ϣ��Ĵ�С
User* users[TABLE_SIZE] = {nullptr}; // ��ϣ����ʼ��Ϊnull
int loggedInUser = -1; // ��ǰ��¼���û�ID��-1��ʾû���û���¼


// ��ϣ���������û�IDӳ�䵽һ�����������
int hashFunction(int id) {
    return id % TABLE_SIZE;
}

// ע�����û��ĺ���
void registerUser() {
    User* newUser = new User; // ��̬����һ���µ��û��ڵ�
    std::cout << "������ID: ";
    std::cin >> newUser->id; // �����û�ID
    std::cout << "����������: ";
    std::cin >> newUser->password; // �����û�����
    std::cout << "����������: ";
    std::cin >> newUser->name; // �����û�����
    int index = hashFunction(newUser->id); // �����ϣֵ
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
        if (user->id == id && user->password == password) { // ����ҵ�ƥ����û�
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
            if (user->id == loggedInUser) { // ����ҵ�ƥ����û�
                std::cout << "�û�ID: " << user->id << "\n"; // ��ӡ�û�ID
                std::cout << "�û�����: " << user->name << "\n"; // ��ӡ�û�����
                return;
            }
        }
    } else {
        std::cout << "��ǰû���û���¼!\n"; // ���û���û���¼����ӡ������Ϣ
    }
}

int log_user() {
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
//                    loggedInUser = 0;
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
//                    loggedInUser = -1;
                    break;
                case 2:
                    getUserInfo(); // ��ȡ��ǰ��¼�û���Ϣ
                    break;
                case 3:
//                    loggedInUser = -1;
                    return 0; // �˳�����
                    break;
                default:
                    std::cout << "��Ч��ѡ��!\n"; // ��������ѡ����Ч����ӡ������Ϣ
            }
        }
    }

    return 1;
}
