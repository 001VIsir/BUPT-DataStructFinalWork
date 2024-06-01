// 定义一个宏，防止头文件被多次包含
#ifndef SEARCHPLACE_H
#define SEARCHPLACE_H

// 包含Qt框架中定义的一些基本组件和功能
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QTextCodec>
#include <QButtonGroup>
#include <QDebug>

// 假设Ui::searchplace是一个由Qt的UI设计器生成的命名空间，包含创建用户界面所需的类和对象
namespace Ui {
class searchplace;
}

// 定义一个简单的结构体Place，用于存储地点的相关信息
struct Place {
    int id;           // 地点的唯一标识符
    QString name;     // 地点的名称
    QString type;     // 地点的类型
    int popularity;   // 地点的受欢迎程度
    double score;     // 地点的评分
};

// 定义一个枚举类SortField，用于指定排序的字段
enum class SortField {
    Popularity,      // 按受欢迎程度排序
    Score            // 按评分排序
};

// 定义searchplace类，继承自QWidget
class searchplace : public QWidget
{
    Q_OBJECT   // 宏，用于启用Qt的信号和槽机制

public:
    // 构造函数，带有可选的父QWidget参数
    explicit searchplace(QWidget *parent = nullptr);
    // 析构函数
    ~searchplace();

    // 从文件中读取地点信息，填充到QList<Place>中
    void readPlacesFromFile(QList<Place>& places);
    // 搜索地点，根据关键词、类型和排序标志返回符合条件的地点列表
    QList<Place> searchPlaces(const QList<Place>& places, const QString& keyword, const QString& type, int flag);
    // 对地点列表进行排序
    void sortPlaces(QList<Place>& places, int flag);
    // 检查给定的类型是否有效
    bool isValidType(const QList<Place>& places, const QString& type);
    // 查询并排序地点
    void queryAndSortPlaces(QList<Place>& places);

    // Ui::searchplace的指针，用于访问由Qt UI设计器生成的界面元素
    Ui::searchplace *ui;
    // 存储地点信息的列表
    QList<Place> places;

private slots:  // Qt的槽函数，用于响应信号
    // 定义槽函数，响应按钮点击事件
    void on_key_clicked();
    void on_name_clicked();
    void on_pushButton_clicked();

private:
    // QButtonGroup的实例，用于管理一组按钮的单选行为
    QButtonGroup *block1 = new QButtonGroup(this);
};

// 结束头文件的宏定义
#endif // SEARCHPLACE_H
