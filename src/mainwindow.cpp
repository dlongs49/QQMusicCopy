//
// Created by dinglong on 2023/1/2.
//

#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    const int w = 1036;
    const int h = 660;
    this->resize(w, h); // 窗口大小
    //阴影的宽度
//    this->setContentsMargins(35, 35, 35, 35);
//    //无边框
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setContentsMargins(0,0,0,0);
    widget = new QWidget(this);
    widget->setMinimumSize(w, h);
    layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    right_menu = new rightMenu();
    container_ = new container();
    layout->addWidget(right_menu);
    layout->addWidget(container_);
    widget->setLayout(layout);

}

MainWindow::~MainWindow() {
}


