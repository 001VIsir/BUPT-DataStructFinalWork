#include "loginwindow.h" // 包含loginwindow类的声明
#include "ui_loginwindow.h" // 包含由Qt Designer生成的loginwindow界面的声明

// loginwindow类的构造函数
loginwindow::loginwindow(QWidget *parent) :
    QWidget(parent), // 调用QWidget的构造函数，设置父组件
    ui(new Ui::loginwindow) // 创建由Qt Designer生成的界面对象
{
    ui->setupUi(this); // 设置界面
    // 连接登录按钮的clicked信号到loginwindow类的loginUser槽函数
    connect(ui->loginButton, &QPushButton::clicked, this, &loginwindow::loginUser);
}

// loginwindow类的析构函数
loginwindow::~loginwindow()
{
    delete ui; // 释放由Qt Designer生成的界面对象所占用的内存
}

// addUser函数用于添加新用户
void loginwindow::addUser(int account, QString password, QString name) {
    User* xinlaide = new User(); // 创建新的User对象
    xinlaide->account = account; // 设置账号
    xinlaide->password = password; // 设置密码
    xinlaide->name = name; // 设置用户名
    int index = hashFunction(account); // 计算哈希索引
    xinlaide->next = users[index]; // 设置链表的下一个节点
    users[index] = xinlaide; // 将新用户添加到链表头部
//    QDebug debug = qDebug();
//    debug << index;
}

// loginUser函数是登录按钮的槽函数
void loginwindow::loginUser()
{
    printf_hash();
    // 从QLineEdit控件中获取用户输入的账号和密码
    int id = ui->input_account->text().toInt();
    QString password = ui->input_password->text();

    // 计算账号的哈希索引
    int index = hashFunction(id);
    // 遍历查找匹配的用户
    for (User* user = users[index]; user != nullptr; user = user->next) {
        if (user->password == password) {
            // 如果密码匹配，则登录成功
            loggedInUser = id;
            QDebug debug = qDebug();
            debug << users[index];
            debug << user->password;
            // 创建并显示新窗口feature_list
            feature_List = new feature_list();
            feature_List->show();
            // this->close(); // 注释掉的代码，用于关闭当前窗口
            return;
        }
    }
    // 如果没有找到匹配的用户，则显示登录失败的警告
    QMessageBox::warning(this, "Login", "登录失败");
}

void loginwindow::printf_hash(){
    for (User* user = users[23]; user != nullptr; user = user->next) {
            QDebug debug = qDebug();
            debug << user->password;
            // 创建并显示新窗口feature_list
            // this->close(); // 注释掉的代码，用于关闭当前窗口
            return;

    }
}
// loadUsersFromCSV函数用于从CSV文件中加载用户数据
void loginwindow::loadUsersFromCSV() {
    // close(); // 注释掉的代码，用于关闭当前窗口

    QFile file("C:\\Users\\visir\\Desktop\\shujvjiegou\\usertest.csv");

    // 尝试以只读模式打开文件
    if (!file.open(QIODevice::ReadOnly)) {
        // 处理文件打开失败的情况
        QMessageBox::warning(this, "Login", "打开不了数据集");
        close(); // 关闭当前窗口
    }
    QTextStream in(&file); // 创建文本流
    // 逐行读取文件内容
    while (!in.atEnd()) {
        QString line = in.readLine();
        // 使用逗号分隔字符串，获取账号、密码和姓名
        QString accountStr = line.section(',', 0, 0);
        QString password = line.section(',', 1, 1);
        QString name = line.section(',', 2, 2);
        int account = accountStr.toInt(); // 将账号字符串转换为整数
        User* newUser = new User(); // 创建新的User对象
        newUser->account = account; // 设置账号
        newUser->password = password; // 设置密码
        newUser->name = name; // 设置姓名
//        QDebug debug = qDebug();
//        debug << newUser->account;
//        debug << newUser->password;
//        debug << newUser->name;
        // 计算哈希索引并添加新用户到链表
        int index = hashFunction(account);
        newUser->next = users[index];
        users[index] = newUser;
    }

    file.close(); // 关闭文件
}

// hashFunction函数用于计算账号的哈希索引
int loginwindow::hashFunction(int id){
    return id % 100; // 返回账号除以100的余数作为索引
}

// on_quit_clicked槽函数，响应退出按钮的点击事件
void loginwindow::on_quit_clicked()
{
    close(); // 关闭当前窗口
}

// on_sign_up_clicked槽函数，响应注册按钮的点击事件
void loginwindow::on_sign_up_clicked()
{
    // 创建logup窗口并显示，将当前窗口作为父窗口传递
    logup *logUp = new logup();
    logUp->show();
}
