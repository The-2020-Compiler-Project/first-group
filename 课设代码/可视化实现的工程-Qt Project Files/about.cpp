#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&About::close);
}

About::~About()
{
    delete ui;
}
