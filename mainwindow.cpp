#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->linecity->setAlignment(Qt::AlignCenter);
    this->setFixedSize(790,650);
    this->setWindowTitle("市运货量");
    // 数据库使用
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("lab");
    db.setUserName("lab");
    db.setPassword("123");
    if(!db.open())
    {
        qDebug()<<"数据库连接失败"<<endl;
    }
    else
    {
        qDebug()<<"连接成功"<<endl;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool mycompator(pair<string,float>&a,pair<string,float>&b)
{
    if(a.second < b.second){
        return true;
    }
    return false;
}

void MainWindow::on_citybar_clicked()
{
    QString text = ui->linecity->text();
    if(text.size() == 0){
        QMessageBox::warning(this,"Warning","请输入城市名!");
        return;
    }
    if(text.size() > 0) {
        cityname = QString(text);
        QSqlQuery query;
        QString str = QString("select * from cityInfo where cityName = '%1'").arg(cityname);
        query.exec(str);

        regionInfo.clear(); // 信息清空，重新记录
        regionweight.clear();
        ui->regionShow->clear(); // 首先需要清空
        ui->regionWeight->clear();
        ui->regionShow->insertPlainText(cityname + "各地区因素分析表展示如下\n\n");
        QString regionName,regionPopulation,regionIncome,regionDensity;
        float totalIncome = 0,totalDensity = 0; // 用于计算权重
        while(query.next()) // 各区信息展示
        {
            regionName = query.value(1).toString();
            regionPopulation = query.value(2).toString();
            regionIncome = query.value(3).toString();
            regionDensity = query.value(4).toString();
            ui->regionShow->insertPlainText(regionName + "\n");
            ui->regionShow->insertPlainText("区人口   \t" + regionPopulation + "\n");
            ui->regionShow->insertPlainText("区人均收入\t" + regionIncome + "\n");
            ui->regionShow->insertPlainText("区人口密度\t" + regionDensity + "\n\n");

            RegionInfo *p = new RegionInfo(query.value(1).toString().toStdString(),query.value(2).toFloat(),
                                           query.value(3).toFloat(),query.value(4).toFloat(),query.value(5).toFloat(),
                                           query.value(6).toFloat());
            regionInfo.push_back(p); // 存储信息
            totalIncome += query.value(3).toFloat();
            totalDensity += query.value(4).toFloat();
        }

        for(size_t i = 0;i < regionInfo.size();i++){
            float weight = (regionInfo[i]->income / totalIncome)*0.6 +
                    (regionInfo[i]->density / totalDensity)*0.4;
            regionweight.push_back(pair<string,float>(regionInfo[i]->name,weight));
        }
        sort(regionweight.begin(),regionweight.end(),mycompator); // 按照从小到大的顺序排列
        ui->regionWeight->insertPlainText(cityname + "各区权重展示如下（从小到大）\n\n");
        for(size_t i = 0;i < regionweight.size();i++){
            ui->regionWeight->insertPlainText(QString::fromStdString(regionweight[i].first) + "\t"
                                              + QString::number(regionweight[i].second) + "\n");
        }
    }
    else {
       QMessageBox::warning(this,tr("警告"),tr("城市不能为空!"));
    }   
}

void MainWindow::on_citybar_2_clicked() // 输入总的开店数（打开新的页面）
{
    store = new storeWidget();
    store->setCityName(cityname.toStdString(),regionweight,regionInfo);
    store->show();
}





