#ifndef SHUJVJIEGOU_USER_H
#define SHUJVJIEGOU_USER_H
#define TABLE_SIZE 100 // ��ϣ��Ĵ�С

extern int loggedInUser; // ��ǰ��¼���û�ID��-1��ʾû���û���¼

void registerUser();
void loginUser();
void logoutUser();
void getUserInfo();
void getUsercsv();
int log_user();

//extern int loggedInUser; // ��ǰ��¼���û�ID��-1��ʾû���û���¼
#endif //SHUJVJIEGOU_USER_H