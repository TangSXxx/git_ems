#include "login.h"
#include "ui_login.h"

#include <QPainter>
#include <QPixmap>
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
     this->setWindowTitle("登录界面");
//    QPainter *painter = new QPainter(this);

//        QPixmap pic = QPixmap(":/res/electric.jpg");
//        //pic = pic.scaled(this->width(),this->height());

//        painter->drawPixmap(0,0,this->width(),this->height(),pic);
        QPalette pal =this->palette();
        pal.setBrush(QPalette::Background,QBrush(QPixmap(":/res/backtee.jpg")));
        setPalette(pal);

}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    login2 * lg=new login2();
    lg->show();
}
