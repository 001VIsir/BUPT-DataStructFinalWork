#ifndef SHUJVJIEGOU_USER_H
#define SHUJVJIEGOU_USER_H
#define TABLE_SIZE 100 // 哈希表的大小

extern int loggedInUser; // 当前登录的用户ID，-1表示没有用户登录

void registerUser();
void loginUser();
void logoutUser();
void getUserInfo();
void getUsercsv();
int log_user();

//extern int loggedInUser; // 当前登录的用户ID，-1表示没有用户登录
#endif //SHUJVJIEGOU_USER_H