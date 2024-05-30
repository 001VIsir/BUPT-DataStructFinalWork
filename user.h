#ifndef SHUJVJIEGOU_USER_H
#define SHUJVJIEGOU_USER_H
extern int loggedInUser; // 当前登录的用户ID，-1表示没有用户登录
void registerUser();
void loginUser();
void logoutUser();
void getUserInfo();
int log_user();


#endif //SHUJVJIEGOU_USER_H