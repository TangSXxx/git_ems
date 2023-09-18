#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <QPalette>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include<QLineEdit>
#include<QIcon>
#include<QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QPalette pal =this->palette();
//    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/res/mainback.jpg")));
//    setPalette(pal);


    //显示实时时间的函数
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, [=]() {
        QDateTime datetime = QDateTime::currentDateTime();
        ui->Time->setText(datetime.toString("yyyy-MM-dd \n hh:mm:ss"));
    });


    //设置时段控制的参数 //fff
    ui->TimeControlTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->TimeControlTable->horizontalHeader()->setMinimumHeight(50);            //设置表头行高
    ui->TimeControlTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color:black;font-weight:bold;}");       //设置表头字体格式
    ui->TimeControlTable->setAlternatingRowColors(true);
    ui->TimeControlTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TimeControlTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //设置48时段控制的参数
    ui->FTimeControlTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->FTimeControlTable->horizontalHeader()->setMinimumHeight(50);            //设置表头行高
    ui->FTimeControlTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color:black;font-weight:bold;}");       //设置表头字体格式
    ui->FTimeControlTable->setAlternatingRowColors(true);
    ui->FTimeControlTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->FTimeControlTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //当前报警数据表格
    ui->CurrentWarnTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->CurrentWarnTable->horizontalHeader()->setMinimumHeight(50);            //设置表头行高
    ui->CurrentWarnTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color:black;font-weight:bold;}");       //设置表头字体格式
    ui->CurrentWarnTable->setAlternatingRowColors(true);
    ui->CurrentWarnTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->CurrentWarnTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //当前报警数据表格
 /*   ui->CurrentWarnTable2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->CurrentWarnTable2->horizontalHeader()->setMinimumHeight(50);            //设置表头行高
    ui->CurrentWarnTable2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color:black;font-weight:bold;}");    */   //设置表头字体格式
    //ui->CurrentWarnTable2->setAlternatingRowColors(true);
//    ui->CurrentWarnTable2->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->CurrentWarnTable2->setSelectionMode(QAbstractItemView::SingleSelection);





    openTable();//打开数据库文件





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openTable()
{
    //打开数据库
    DB = QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
    DB.setDatabaseName("demodb.db3"); //设置数据库名称

    if (!DB.open())   //打开数据库
    {
        QMessageBox::warning(this, "错误", "打开数据库失败", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    //时段控制表格输入参数设置
    qryModel=new CustomSqlQueryModel(this);
    FPControlQryMdl = new CustomSqlQueryModel(this);
    CurrentWarnQryModel = new CustomSqlQueryModel(this);
    CurrentWarnQryModel2 = new CustomSqlQueryModel(this);

    qryModel->setQuery("SELECT NumberList, StartTime, EndTime, Power, NumberList2, StartTime2, EndTime2, Power2 FROM PeriodControl");
    FPControlQryMdl->setQuery("SELECT TimePeriod, Power, TimePeriod2, Power2, TimePeriod3, Power3, TimePeriod4, Power4 FROM FPeriodControl");
    CurrentWarnQryModel->setQuery("SELECT Data, Time, Describe FROM CurrentWarnTable");
    CurrentWarnQryModel2->setQuery("SELECT Describe FROM CurrentWarnTable");
    //时段控制数据库模型
    qryModel->setHeaderData(0,Qt::Horizontal,"序号");
    qryModel->setHeaderData(1,Qt::Horizontal,"起始时分");
    qryModel->setHeaderData(2,Qt::Horizontal,"结束时分");
    qryModel->setHeaderData(3,Qt::Horizontal,"功率(KW)");
    qryModel->setHeaderData(4,Qt::Horizontal,"序号");
    qryModel->setHeaderData(5,Qt::Horizontal,"起始时分");
    qryModel->setHeaderData(6,Qt::Horizontal,"结束时分");
    qryModel->setHeaderData(7,Qt::Horizontal,"功率(KW)");

    //48时段控制数据库模型
    FPControlQryMdl->setHeaderData(0,Qt::Horizontal,"时间段");
    FPControlQryMdl->setHeaderData(1,Qt::Horizontal,"功率");
    FPControlQryMdl->setHeaderData(2,Qt::Horizontal,"时间段");
    FPControlQryMdl->setHeaderData(3,Qt::Horizontal,"功率");
    FPControlQryMdl->setHeaderData(4,Qt::Horizontal,"时间段");
    FPControlQryMdl->setHeaderData(5,Qt::Horizontal,"功率");
    FPControlQryMdl->setHeaderData(6,Qt::Horizontal,"时间段");
    FPControlQryMdl->setHeaderData(7,Qt::Horizontal,"功率");

    //当前报警数据库模型表头设定
    CurrentWarnQryModel->setHeaderData(0,Qt::Horizontal,"日期");
    CurrentWarnQryModel->setHeaderData(1,Qt::Horizontal,"时间");
    CurrentWarnQryModel->setHeaderData(2,Qt::Horizontal,"报警描述");

    //桌面当前报警数据表格
//    CurrentWarnQryModel2->setHeaderData(1,Qt::Horizontal,"时间");
//    CurrentWarnQryModel2->setHeaderData(2,Qt::Horizontal,"报警描述");

    //建立与ui的联系，
    ui->FTimeControlTable->setModel(FPControlQryMdl);
    ui->TimeControlTable->setModel(qryModel);
    ui->CurrentWarnTable->setModel(CurrentWarnQryModel);
    ui->CurrentWarnTable2->setModel(CurrentWarnQryModel2);

}


//void MainWindow::on_userManage_toggled(bool checked)
//{
//    if(checked)
//    {
//        ui->userManage->setIconSize(QSize(55,55));       //按下时放大icon大小
//        ui->userManage->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
//        ui->userManage->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
//    }
//    else
//    {
//        ui->userManage->setIconSize(QSize(50,50));
//        ui->userManage->setFont(QFont("宋体",17,QFont::Bold));
//        ui->userManage->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
//    }
//}


void MainWindow::on_SystemOverviewButton_clicked()
{
    ui->MainUI->setCurrentIndex(0);
}

void MainWindow::on_ConditionMonitorButton_clicked()
{
    ui->MainUI->setCurrentIndex(1);
}

void MainWindow::on_PCSManageButton_clicked()
{
    ui->MainUI->setCurrentIndex(2);
}

void MainWindow::on_EMSManageButton_clicked()
{
    ui->MainUI->setCurrentIndex(3);
}

void MainWindow::on_SystemDefenseButton_clicked()
{
    ui->MainUI->setCurrentIndex(4);
}

void MainWindow::on_OtherDeviceButton_clicked()
{
    ui->MainUI->setCurrentIndex(5);
}

void MainWindow::on_DataStatisticsButton_clicked()
{
    ui->MainUI->setCurrentIndex(6);
}

void MainWindow::on_UserManageButton_clicked()
{
    ui->MainUI->setCurrentIndex(7);
}

//void MainWindow::on_DataStatisticButton_clicked()
//{
//    ui->MainUI->setCurrentIndex(8);
//}

//void MainWindow::on_UserManageButton_clicked()
//{
//    ui->MainUI->setCurrentIndex(9);
//}

void MainWindow::on_SystemOverviewButton_toggled(bool checked)
{
        if(checked)
        {
            ui->SystemOverviewButton->setIconSize(QSize(55,55));       //按下时放大icon大小
            ui->SystemOverviewButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
            ui->SystemOverviewButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
        }
        else
        {
            ui->SystemOverviewButton->setIconSize(QSize(50,50));
            ui->SystemOverviewButton->setFont(QFont("宋体",17,QFont::Bold));
            ui->SystemOverviewButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
        }
}

void MainWindow::on_ConditionMonitorButton_toggled(bool checked)
{
    if(checked)
    {
        ui->ConditionMonitorButton->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->ConditionMonitorButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->ConditionMonitorButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->ConditionMonitorButton->setIconSize(QSize(50,50));
        ui->ConditionMonitorButton->setFont(QFont("宋体",17,QFont::Bold));
        ui->ConditionMonitorButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_PCSManageButton_toggled(bool checked)
{
    if(checked)
    {
        ui->PCSManageButton->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->PCSManageButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->PCSManageButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->PCSManageButton->setIconSize(QSize(50,50));
        ui->PCSManageButton->setFont(QFont("宋体",17,QFont::Bold));
        ui->PCSManageButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_EMSManageButton_toggled(bool checked)
{
    if(checked)
    {
        ui->EMSManageButton->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->EMSManageButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->EMSManageButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->EMSManageButton->setIconSize(QSize(50,50));
        ui->EMSManageButton->setFont(QFont("宋体",17,QFont::Bold));
        ui->EMSManageButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_SystemDefenseButton_toggled(bool checked)
{
    if(checked)
    {
        ui->SystemDefenseButton->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->SystemDefenseButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->SystemDefenseButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->SystemDefenseButton->setIconSize(QSize(50,50));
        ui->SystemDefenseButton->setFont(QFont("宋体",17,QFont::Bold));
        ui->SystemDefenseButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_OtherDeviceButton_toggled(bool checked)
{
    if(checked)
    {
        ui->OtherDeviceButton->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->OtherDeviceButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->OtherDeviceButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->OtherDeviceButton->setIconSize(QSize(50,50));
        ui->OtherDeviceButton->setFont(QFont("宋体",17,QFont::Bold));
        ui->OtherDeviceButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_DataStatisticsButton_toggled(bool checked)
{
    if(checked)
    {
        ui->DataStatisticsButton->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->DataStatisticsButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->DataStatisticsButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->DataStatisticsButton->setIconSize(QSize(50,50));
        ui->DataStatisticsButton->setFont(QFont("宋体",17,QFont::Bold));
        ui->DataStatisticsButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_UserManageButton_toggled(bool checked)
{
    if(checked)
    {
        ui->UserManageButton->setIconSize(QSize(55,55));       //按下时放大icon大小
        ui->UserManageButton->setFont(QFont("宋体",19,QFont::Bold));        //按下时更改字体格式：Qfont对象 字体 大小 加粗
        ui->UserManageButton->setStyleSheet("QToolButton{background-color:rgb(0, 85, 127);color: rgb(255, 255, 255);}");
    }
    else
    {
        ui->UserManageButton->setIconSize(QSize(50,50));
        ui->UserManageButton->setFont(QFont("宋体",17,QFont::Bold));
        ui->UserManageButton->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

QIcon MainWindow::setIconColor(QIcon icon, QColor color)
{
    QPixmap pixmap = icon.pixmap(QSize(161,141));
        QPainter painter(&pixmap);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(pixmap.rect(), color);
        QIcon colorIcon = QIcon(pixmap);
        return colorIcon;


}

void MainWindow::on_PowerGrid_toggled(bool checked)
{
    if(checked)
    {
        ui->PowerGrid->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->PowerGrid->setIcon(setIconColor(ui->PowerGrid->icon(), QColor(130, 130, 130)));
        ui->PowerGrid->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->PowerGrid->setIconSize(QSize(161,141));
        ui->PowerGrid->setIcon(setIconColor(ui->PowerGrid->icon(), QColor(255, 255, 255)));
        ui->PowerGrid->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_STS_toggled(bool checked)
{
    if(checked)
    {
        ui->STS->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->STS->setIcon(setIconColor(ui->STS->icon(), QColor(130, 130, 130)));
        ui->STS->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->STS->setIconSize(QSize(161,141));
        ui->STS->setIcon(setIconColor(ui->STS->icon(), QColor(255, 255, 255)));
        ui->STS->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}


void MainWindow::on_PCS_toggled(bool checked)
{
    if(checked)
    {
        ui->PCS->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->PCS->setIcon(setIconColor(ui->PCS->icon(), QColor(130, 130, 130)));
        ui->PCS->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->PCS->setIconSize(QSize(161,141));
        ui->PCS->setIcon(setIconColor(ui->PCS->icon(), QColor(255, 255, 255)));
        ui->PCS->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}



void MainWindow::on_DCDC_toggled(bool checked)
{
    if(checked)
    {
        ui->DCDC->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->DCDC->setIcon(setIconColor(ui->DCDC->icon(), QColor(130, 130, 130)));
        ui->DCDC->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->DCDC->setIconSize(QSize(161,141));
        ui->DCDC->setIcon(setIconColor(ui->DCDC->icon(), QColor(255, 255, 255)));
        ui->DCDC->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}


void MainWindow::on_Battery_toggled(bool checked)
{
    if(checked)
    {
        ui->Battery->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->Battery->setIcon(setIconColor(ui->Battery->icon(), QColor(130, 130, 130)));
        ui->Battery->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->Battery->setIconSize(QSize(161,141));
        ui->Battery->setIcon(setIconColor(ui->Battery->icon(), QColor(255, 255, 255)));
        ui->Battery->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_Mppt_toggled(bool checked)
{
    if(checked)
    {
        ui->Mppt->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->Mppt->setIcon(setIconColor(ui->Mppt->icon(), QColor(130, 130, 130)));
        ui->Mppt->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->Mppt->setIconSize(QSize(161,141));
        ui->Mppt->setIcon(setIconColor(ui->Mppt->icon(), QColor(255, 255, 255)));
        ui->Mppt->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}


void MainWindow::on_Current_toggled(bool checked)
{
    if(checked)
    {
        ui->Current->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->Current->setIcon(setIconColor(ui->Current->icon(), QColor(130, 130, 130)));
        ui->Current->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->Current->setIconSize(QSize(161,141));
        ui->Current->setIcon(setIconColor(ui->Current->icon(), QColor(255, 255, 255)));
        ui->Current->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

void MainWindow::on_SolarPower_toggled(bool checked)
{
    if(checked)
    {
        ui->SolarPower->setIconSize(QSize(151,131));       //按下时放大icon大小
        ui->SolarPower->setIcon(setIconColor(ui->SolarPower->icon(), QColor(130, 130, 130)));
        ui->SolarPower->setStyleSheet("QToolButton{background-color:transparent;color: rgb(130, 130, 130);}");
    }
    else
    {
        ui->SolarPower->setIconSize(QSize(161,141));
        ui->SolarPower->setIcon(setIconColor(ui->SolarPower->icon(), QColor(255, 255, 255)));
        ui->SolarPower->setStyleSheet("QToolButton{background-color:transparent;color: rgb(255, 255, 255);}");
    }
}

