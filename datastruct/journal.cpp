#include "journal.h"
#include "ui_journal.h"

journal::journal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::journal)
{
    ui->setupUi(this);
}

journal::~journal()
{
    delete ui;
}
