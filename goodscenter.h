#ifndef GOODSCENTER_H
#define GOODSCENTER_H
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
#include <map>
using namespace std;

namespace Ui {
class GoodsCenter;
}

class GoodsCenter : public QWidget
{
    Q_OBJECT

public:
    explicit GoodsCenter(QWidget *parent = nullptr);
    ~GoodsCenter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GoodsCenter *ui;
};

#endif // GOODSCENTER_H
