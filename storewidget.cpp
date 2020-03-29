#include "storewidget.h"
#include "ui_storewidget.h"
#include "averageinfo.h"

storeWidget::storeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::storeWidget)
{
    ui->setupUi(this);
    this->setFixedSize(730,625);
    this->setWindowTitle("市各区货运量分配");
    averageinfo = new AverageInfo(info);
    ui->linstore->setAlignment(Qt::AlignCenter);
    connect(averageinfo,SIGNAL(OverInput()),this,SLOT(receive_finish())); // 连接函数
}

storeWidget::~storeWidget()
{
    delete ui;
}

void storeWidget::setCityName(string cityname,vector<pair<string,float>>regionweight,vector<RegionInfo*> regionInfo)
{
    this->cityname = cityname;
    for(int i = 0;i < regionweight.size();i++){
        this->regionweight.push_back(regionweight[i]);
        this->regionInfo.push_back(regionInfo[i]);
    }
}

void storeWidget::on_storebtn_clicked()
{
    storeNum = ui->linstore->text().toInt();// 获取输入的开店数
    averageinfo->getValues(regionweight);
    averageinfo->show();
}

void storeWidget::receive_finish()
{
    ui->average->clear();// 先清空
    ui->total->clear();
    ui->average->setAlignment(Qt::AlignCenter);
    ui->total->setAlignment(Qt::AlignCenter);

    regionTotal.clear();
    // 插入文本信息
    ui->average->insertPlainText("各区平均货运量如下\n");
    for(int i = 0;i<regionweight.size();i++){
        ui->average->insertPlainText(QString::fromStdString(regionweight[i].first+":\t")
                                     + QString::number(info[i]) + "\n");
    }

    ui->total->insertPlainText("各区总量展示如下\n");
    for(int i = 0;i < regionweight.size();i++){
        int total_each = storeNum*regionweight[i].second*info[i];
        ui->total->insertPlainText(QString::fromStdString(regionweight[i].first+":\t")
                                     +QString::number(total_each) + "\n");
        regionTotal.insert(pair<string,float>(regionweight[i].first,total_each));
    }

    // 计算最佳理想位置
    float x0 = 0,y0 = 0;
    float total = 0;
    for(int i = 0;i < regionInfo.size();i++){
        map<string,float>::iterator it = regionTotal.find(regionInfo[i]->name);
        if(it == regionTotal.end()){
            assert(0);
        }
        else{
            total += (*it).second;
            x0 += regionInfo[i]->region_longtitude * (*it).second;
            y0 += regionInfo[i]->region_latitude * (*it).second;
        }
    }
    x0 = x0 / total;
    y0 = y0 / total;
    ui->bestplace->setText(QString("%1,%2").arg(x0).arg(y0));
}


void storeWidget::on_pushButton_clicked()
{
    goodCenter = new GoodsCenter();
    goodCenter->show();
}
