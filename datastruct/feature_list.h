#ifndef FEATURE_LIST_H
#define FEATURE_LIST_H

#include <QWidget>
#include <searchplace.h>
namespace Ui {
class feature_list;
}

class feature_list : public QWidget
{
    Q_OBJECT

public:
    explicit feature_list(QWidget *parent = nullptr);
    ~feature_list();

private slots:
    void on_search_clicked();

    void on_quit_clicked();

private:
    Ui::feature_list *ui;
        searchplace *searchPlace;

};

#endif // FEATURE_LIST_H
