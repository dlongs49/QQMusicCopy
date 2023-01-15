//
// Created by dinglong on 2023/1/2.
//

#ifndef DEMO_2_MAINWINDOW_H
#define DEMO_2_MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QMovie>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout> // 水平布局组件
#include <QVBoxLayout> // 垂直布局组件
#include <QListWidget> // 列表
#include <QScrollArea> // 滚动容器
#include <QSpacerItem>
#include <QWidget>
#include <QListWidgetItem>
#include <QCursor>
class MainWindow : public QMainWindow{
    Q_OBJECT;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QHBoxLayout *layout;
    QListWidget *list[4];
    QLabel *tlabel[4];
    QVBoxLayout *vlayout;
    QScrollArea *sarea;
    QWidget *widget;
    QListWidgetItem *recommend;
//    void setCursor(const QCursor &);

    QPushButton b1;
    QPushButton *b2;
    QMovie *qm_1;
    QLabel *ql_1;
    QLabel *ql_2;
    QPixmap *qp_1;
    void readQssStyle();
    void customClick();
};
#endif //DEMO_2_MAINWINDOW_H
