//
// Created by dinglong on 2023/1/2.
//

#include "../header/mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    this->resize(1200, 660); // 窗口大小
    //阴影的宽度
//    this->setContentsMargins(35, 35, 35, 35);
//    //无边框
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    layout = new QHBoxLayout(this);
    right_menu = new rightMenu(this);
    container_ = new container(this);
    layout->addWidget(right_menu);
    layout->addWidget(container_);
    right_menu->setStyleSheet("QWidget{background:#ff0}");
}

MainWindow::~MainWindow() {
}


