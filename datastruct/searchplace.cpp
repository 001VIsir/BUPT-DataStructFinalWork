#include "searchplace.h" // 包含searchplace类的声明
#include "ui_searchplace.h" // 包含由Qt Designer生成的界面类声明

// searchplace类的构造函数，用于初始化窗口
searchplace::searchplace(QWidget *parent) :
    QWidget(parent), // 调用基类QWidget的构造函数，设置父窗口
    ui(new Ui::searchplace) // 创建由Qt Designer生成的界面对象
{
    ui->setupUi(this); // 通过界面对象设置窗口界面
    readPlacesFromFile(places); // 从文件中读取地点信息
    ui->tableWidget->setRowCount(places.size()); // 设置表格行数以匹配地点数量

    // 遍历places列表，将地点信息添加到表格中
    for (int i = 0; i < places.size(); ++i) {
        const auto& place = places[i];
        // 创建QDebug对象，用于调试输出
        QDebug debug = qDebug();
        // 输出地点的受欢迎程度，调试信息
        debug << place.popularity;

        // 为表格的每个单元格设置地点信息
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(place.id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(place.name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(place.type));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(place.popularity)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(place.score)));
    }
    // 设置默认选中的排序按钮为按受欢迎程度排序
    ui->popularityButton->setChecked(true);
}

// searchplace类的析构函数，用于释放资源
searchplace::~searchplace()
{
    delete ui; // 删除由Qt Designer生成的界面对象，释放内存
}

// 从文件中读取地点信息并填充到QList<Place>中
void searchplace::readPlacesFromFile(QList<Place>& places) {
    QFile file("C:\\Users\\visir\\Desktop\\shujvjiegou\\newplaces.csv"); // 创建文件对象，指定文件路径

    // 尝试以只读和文本模式打开文件，如果失败则弹出警告框
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Warning", "Cannot open file");
    }

    QTextStream in(&file); // 创建文本流，关联到文件
    // 注释掉的代码，如果需要可以取消注释以设置编码为UTF-8
    // in.setCodec(QTextCodec::codecForName("UTF-8"));
    in.readLine(); // 读取并丢弃标题行

    // 逐行读取文件内容
    while (!in.atEnd()) {
        QString line = in.readLine(); // 读取一行数据
        // 使用逗号分隔字符串，获取id、name、type、popularity和score字段
        QString id = line.section(',', 0, 0);
        QString name = line.section(',', 1, 1);
        QString type = line.section(',', 2, 2);
        QString popularity = line.section(',', 3, 3);
        QString score = line.section(',', 4, 4);
        QString commend = line.section(',', 5, 5);
        Place place; // 创建Place结构体实例

        // 将字符串转换为相应的数据类型并赋值给place结构体
        // 这里存在代码错误，应直接使用id、popularity和score的值
        // QString field;
        // place.id = field.toInt(); // 错误的赋值，应使用id.toInt()
        place.id = id.toInt(); // 正确使用id的值
        place.name = name; // 赋值名称
        place.type = type; // 赋值类型
        place.popularity = popularity.toInt(); // 赋值受欢迎程度
        place.score = score.toDouble(); // 赋值评分
        places.push_back(place); // 将地点信息添加到列表中
    }

    file.close(); // 关闭文件
    return; // 函数返回
}

// 根据关键字、类型和排序标志搜索地点
QList<Place> searchplace::searchPlaces(const QList<Place>& places, const QString& keyword, const QString& type, int flag) {
    QList<Place> result; // 创建结果列表
    // 遍历地点列表
    for (const auto& place : places) {
        // 根据flag的值，搜索名称或类型匹配关键字的地点
        if (flag == 1 && place.name == keyword) {
            result.push_back(place); // 如果名称匹配，添加到结果列表
        } else if (place.type == keyword) {
            result.push_back(place); // 如果类型匹配，添加到结果列表
        }
    }
    return result; // 返回搜索结果
}

// 对地点列表进行排序
void searchplace::sortPlaces(QList<Place>& places, int flag) {
    // 使用std::sort进行排序，根据flag的值选择按受欢迎程度或评分排序
    std::sort(places.begin(), places.end(), [flag](const Place& a, const Place& b) {
        if (flag == 1) {
            // 如果flag为1，按受欢迎程度排序
            return a.popularity > b.popularity;
        } else {
            // 否则按评分排序
            return a.score > b.score;
        }
    });
}

// 检查给定的类型是否在地点列表中有效
bool isValidType(const QList<Place>& places, const QString& type) {
    for (const auto& place : places) {
        // 如果在列表中找到匹配的类型，则返回true
        if (place.type == type) {
            return true;
        }
    }
    // 如果没有找到匹配的类型，则返回false
    return false;
}

// 查询并排序地点信息
void searchplace::queryAndSortPlaces(QList<Place>& places) {
    // 创建searchplace对象a是不必要的，可能是一个错误
    searchplace a;
    QString keyword = ui->input->text(); // 获取用户输入的关键字
    if (keyword.isEmpty()) {
        // 如果关键字为空，则弹出警告框并返回
        QMessageBox::warning(this, "Warning", "请输入关键字");
        return;
    }
    QString type = "Type"; // 假设类型是固定的

    // 检查类型是否有效，如果无效则显示警告并返回
    // if (!isValidType(places, type)) {
    //     QMessageBox::warning(nullptr, "Warning", "Invalid type");
    //     return;
    // }

    int flag = 0; // 初始化搜索标志
    // 根据用户选择的搜索方式设置flag的值
    if (ui->key->isChecked()) {
        flag = 1; // 如果选中了某个特定的键，则设置flag为1
    } else if (ui->name->isChecked()) {
        flag = 0; // 如果选中了名称，则设置flag为0
    }

    QList<Place> searchResult; // 搜索结果列表
    searchResult = searchPlaces(places, keyword, type, flag); // 执行搜索

    if (searchResult.empty()) {
        // 如果搜索结果为空，清空表格并显示警告
        ui->tableWidget->setRowCount(0);
        QMessageBox::warning(this, "Login", "没查到 嘿嘿");
        return;
    }

    // 设置排序标志
    int flag2 = 0;
    if (ui->popularityButton->isChecked()) {
        flag2 = 1; // 如果选中了按受欢迎程度排序，则设置flag2为1
    } else if (ui->scoreButton->isChecked()) {
        flag2 = 0; // 如果选中了按评分排序，则设置flag2为0
    }

    sortPlaces(searchResult, flag2); // 对搜索结果进行排序

    // 更新表格以显示排序后的搜索结果
    ui->tableWidget->setRowCount(searchResult.size());
    for (int i = 0; i < searchResult.size(); ++i) {
        const auto& place = searchResult[i];
        // 为表格的每个单元格设置地点信息
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(place.id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(place.name));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(place.type));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(place.popularity)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(place.score)));
    }
}

// 槽函数，响应按钮点击事件，用于刷新搜索结果
void searchplace::on_key_clicked()
{
    queryAndSortPlaces(places);
}

// 槽函数，响应另一个按钮点击事件，同样用于刷新搜索结果
void searchplace::on_name_clicked()
{
    queryAndSortPlaces(places);
}

// 槽函数，响应按钮点击事件，用于关闭窗口
void searchplace::on_pushButton_clicked()
{
    close(); // 关闭当前窗口
}
