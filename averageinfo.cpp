#include "averageinfo.h"
#include "ui_averageinfo.h"

/*
AverageInfo::AverageInfo(QWidget *parent) :info()
    QWidget(parent),
    ui(new Ui::AverageInfo)
{
    ui->setupUi(this);
}*/
AverageInfo::AverageInfo(vector<int> &information,QWidget *parent) :
    QWidget(parent),ui(new Ui::AverageInfo),info(information)
{
    ui->setupUi(this);
    this->setFixedSize(590,500);
    this->setWindowTitle("每个店平均货运量");
}

AverageInfo::~AverageInfo()
{
    delete ui;
}

void AverageInfo::getValues(vector<pair<string,float>>regionweight)
{
    QFormLayout *layout = new QFormLayout();
    layout->setHorizontalSpacing(40);
    for(int i = 0;i < regionweight.size();i++){
        QLabel *label = new QLabel("\t\t" + QString::fromStdString(regionweight[i].first));
        QLineEdit *p = new QLineEdit();
        p->setAlignment(Qt::AlignCenter);
        p->setFixedSize(QSize(150,30)); // 指定大小
        layout->addRow(label,p);
        lineNum.push_back(p); // 后续判断数据是否为空时用到
    }
   // layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

void AverageInfo::on_pushButton_clicked()  // 表格填好后点击确认事件
{
    for(int i = 0;i < lineNum.size();i++){
        if(lineNum[i]->text().size() == 0){
            QMessageBox::warning(this,"warning","字段不为空!");
            return;
        }
        info.push_back(lineNum[i]->text().toInt());
    }
    this->close();
    emit OverInput();
}







