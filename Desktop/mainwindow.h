#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customClass.h"
#include "qmybattery.h"
#include <QtSql>
#include <QDataWidgetMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QIcon setIconColor(QIcon icon, QColor color);

private slots:

    void on_SystemOverviewButton_clicked();

    void on_ConditionMonitorButton_clicked();

    void on_PCSManageButton_clicked();

    void on_EMSManageButton_clicked();

    void on_SystemDefenseButton_clicked();

    void on_OtherDeviceButton_clicked();

    void on_DataStatisticsButton_clicked();

    void on_UserManageButton_clicked();



    void on_SystemOverviewButton_toggled(bool checked);

    void on_ConditionMonitorButton_toggled(bool checked);

    void on_PCSManageButton_toggled(bool checked);

    void on_EMSManageButton_toggled(bool checked);

    void on_SystemDefenseButton_toggled(bool checked);

    void on_OtherDeviceButton_toggled(bool checked);

    void on_DataStatisticsButton_toggled(bool checked);

    void on_UserManageButton_toggled(bool checked);


    void on_PowerGrid_toggled(bool checked);
    void on_STS_toggled(bool checked);
    void on_PCS_toggled(bool checked);
    void on_DCDC_toggled(bool checked);
    void on_Battery_toggled(bool checked);
    void on_Mppt_toggled(bool checked);
    void on_Current_toggled(bool checked);
    void on_SolarPower_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    CustomSqlQueryModel *qryModel;//定义数据库模型，引入数据库中的数据
    CustomSqlQueryModel *FPControlQryMdl;//定义数据库模型，引入数据库中的数据
    CustomSqlQueryModel *CurrentWarnQryModel; //当前报警数据
    CustomSqlQueryModel *CurrentWarnQryModel2; //桌面当前报警数据
    CustomSqlQueryModel *PCSWorkIndexModel;//PCS工作参数信息
    CustomSqlQueryModel *BMSWorkIndexModel;//PCS保护参数信息
    CustomSqlQueryModel *SPWorkAirConditionModel;//系统防护工作参数空调
    CustomSqlQueryModel *SPWorkAirConditionModel1;//系统防护工作参数空调1
    CustomSqlQueryModel *SPWorkThermoHygroMeterModel;//系统防护工作参数温湿度器
    CustomSqlQueryModel *SPWorkPressureModuleModel;//系统防护工作参数均压模块
    CustomSqlQueryModel *SPWorkGrid_sideMetersModel;//系统防护工作参数电网侧电表
    CustomSqlQueryModel *STSIndexModel;//STS工作参数
    CustomSqlQueryModel *STSIndex1Model;//STS功率参数
    CustomSqlQueryModel *DCDCIndexModel;//DCDC功率参数
    CustomSqlQueryModel *MPPTIndexModel;//MPPT功率参数
    CustomSqlQueryModel *CurrentWarnModel;//当前警告
    CustomSqlQueryModel *HistoryWarnModel;//历史警告
    QSqlDatabase DB;//定义数据库端口

    void openTable(); //打开数据库

};
#endif // MAINWINDOW_H
