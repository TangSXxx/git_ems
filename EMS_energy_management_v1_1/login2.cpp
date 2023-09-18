#include "login2.h"
#include "ui_login2.h"
#include<mainwindow.h>
#include<QMessageBox>
login2::login2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login2)
{
    ui->setupUi(this);
     this->setWindowTitle("登录界面");
    QPalette pal =this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/res/electric.jpg")));
    setPalette(pal);
}

login2::~login2()
{
    delete ui;
}

void login2::on_pushButton_sure_clicked()
{
    if((ui->comboBox->currentText()=="高级用户" &&ui->lineEdit_spassword->text()=="4321")||(ui->comboBox->currentText()=="一般用户" &&ui->lineEdit_spassword->text()=="1234"))
    {
        this->close();

        MainWindow *wid=new MainWindow();
        wid->show();
    }
    else{
            QMessageBox::warning(this,tr("登陆失败"),tr("用户密码错误！"),QMessageBox::Ok);
            ui->lineEdit_spassword->clear();
            ui->lineEdit_spassword->setFocus();
    }
}
