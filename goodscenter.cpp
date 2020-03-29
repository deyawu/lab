#include "goodscenter.h"
#include "ui_goodscenter.h"

GoodsCenter::GoodsCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoodsCenter)
{
    ui->setupUi(this);
}

GoodsCenter::~GoodsCenter()
{
    delete ui;
}

bool mycompare(pair<string,float> &a,pair<string,float>& b){
    return a.second > b.second;
}

void GoodsCenter::on_pushButton_clicked()
{
    if(abs(ui->spinbox_s->value() + ui->spinbox_traffic->value() + ui->spinbox_rent->value() - 1) < 0.0001){
        vector<pair<string,float>> spots;
        float values1=0,values2=0,values3=0;
        float weight_s = ui->spinbox_s->value(),weight_traffic = ui->spinbox_traffic->value(),
                weight_rent = ui->spinbox_rent->value(); // 获取权值
        if(ui->spot1->text().size() != 0){
            if(ui->spot1_s->text().size() == 0 || ui->spot1_rent->text().size() == 0 || ui->spot1_traffic->text().size() == 0){
                QMessageBox::warning(this,"warning","字段不能为空!");
            }
            else{
                values1 = ui->spot1_s->text().toFloat() * weight_s + ui->spot1_rent->text().toFloat() * weight_rent
                        + ui->spot1_traffic->text().toFloat() * weight_traffic;
                spots.push_back(pair<string,float>(ui->spot1->text().toStdString(),values1));
                ui->spot1_score->setText(QString("%1").arg(values1));
            }
        }
        if(ui->spot2->text().size() != 0){
            if(ui->spot2_s->text().size() == 0 || ui->spot2_rent->text().size() == 0 || ui->spot2_traffic->text().size() == 0){
                QMessageBox::warning(this,"warning","字段不能为空!");
            }
            else{
                values2 = ui->spot2_s->text().toFloat() * weight_s + ui->spot2_rent->text().toFloat() * weight_rent
                        + ui->spot2_traffic->text().toFloat() * weight_traffic;
                spots.push_back(pair<string,float>(ui->spot2->text().toStdString(),values2));
                ui->spot2_score->setText(QString("%1").arg(values2));
            }
        }
        if(ui->spot3->text().size() != 0){
            if(ui->spot3_s->text().size() == 0 || ui->spot3_rent->text().size() == 0 || ui->spot3_traffic->text().size() == 0){
                QMessageBox::warning(this,"warning","字段不能为空!");
            }
            else{
                values3 = ui->spot3_s->text().toFloat() * weight_s + ui->spot3_rent->text().toFloat() * weight_rent
                        + ui->spot3_traffic->text().toFloat() * weight_traffic;
                spots.push_back(pair<string,float>(ui->spot3->text().toStdString(),values3));
                ui->spot3_score->setText(QString("%1").arg(values3));
            }
        }
        if(spots.size() == 0){
             QMessageBox::warning(this,"warning","候选地点不能为空!");
        }
        else{
            sort(spots.begin(),spots.end(),mycompare); // 按照分数值进行排序,默认分数值最大的在前
            ui->idealCenter->setText(QString::fromStdString(spots[0].first));
        }
    }
    else{
        QMessageBox::warning(this,"warning","权值之和不为1!");
    }
}



