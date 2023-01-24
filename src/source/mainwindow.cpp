//
// Created by dinglong on 2023/1/2.
//

#include "../header/mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    this->resize(1200, 660); // 窗口大小
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    layout = new QHBoxLayout(this);
    right_menu = new rightMenu(this);
    layout->addWidget(right_menu);
}

MainWindow::~MainWindow() {
}


