#ifndef AVERAGEINFO_H
#define AVERAGEINFO_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase> // 数据库基本操作
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QCloseEvent>
using namespace std;


namespace Ui {
class AverageInfo;
}

class AverageInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AverageInfo(vector<int> &information,QWidget *parent=nullptr);
    ~AverageInfo();
    //void closeEvent(QCloseEvent *event);
    void getValues(vector<pair<string,float>>regionweight);

signals:
    void OverInput(); // 点击ok按钮表明输入完成。

private slots:
    void on_pushButton_clicked();

private:
    Ui::AverageInfo *ui;
    vector<int> &info; // 存储各区平均货运量
    vector<QLineEdit*> lineNum;
};

#endif // AVERAGEINFO_H
