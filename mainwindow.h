#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase> // 数据库基本操作
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include "storeWidget.h"
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_citybar_clicked();

    void on_citybar_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QString cityname;
    storeWidget *store;
    vector<RegionInfo*> regionInfo; // 各区信息
    vector<pair<string,float>> regionweight; // 各区权重
};

#endif // MAINWINDOW_H
