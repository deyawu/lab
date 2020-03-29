#ifndef STOREWIDGET_H
#define STOREWIDGET_H

#include <iostream>
#include <QMainWindow>
#include <QSqlDatabase> // 数据库基本操作
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <map>
#include "averageinfo.h"
#include "goodscenter.h"

using namespace std;

namespace Ui {
class storeWidget;
}

struct RegionInfo{
    string name;
    float population;
    float income;
    float density;
    float region_longtitude;
    float region_latitude;
    RegionInfo(){}
    RegionInfo(string n,float p,float i,float d,float longtitude,float latitude) {
        name = n;
        population = p;
        income = i;
        density = d;
        region_longtitude = longtitude;
        region_latitude = latitude;
    }
};

class storeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit storeWidget(QWidget *parent = nullptr);
    ~storeWidget();
   void setCityName(string cityname,vector<pair<string,float>>regionweight,vector<RegionInfo*> regionInfo);
   void displayRegions();

private slots:
   void on_storebtn_clicked();
   void receive_finish();

   void on_pushButton_clicked();

private:
    Ui::storeWidget *ui;
    string cityname; // 城市名称
    int storeNum; // 开店数量
    vector<int> info; // 存储各区的平均配送量
    vector<pair<string,float>>regionweight; // 各区权重
    map<string,float> regionTotal; // 各区总运输量
    vector<RegionInfo*> regionInfo; // 各区信息

    AverageInfo *averageinfo; // 对象指针
    GoodsCenter *goodCenter; // 对象指针

};

#endif // STOREWIDGET_H
