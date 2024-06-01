#include "feature_list.h"
#include "ui_feature_list.h"

feature_list::feature_list(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::feature_list)
{
    ui->setupUi(this);
}

feature_list::~feature_list()
{
    delete ui;
}

void feature_list::on_search_clicked()
{

    searchPlace = new searchplace();
    searchPlace->show();
}


void feature_list::on_quit_clicked()
{
    close();
}

