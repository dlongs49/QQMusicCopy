//
// Created by dinglong on 2023/1/2.
//

#include "mainwindow.h"
#include <iostream>
#include <QFile>
#include <QString>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    this->resize(1200, 660); // 窗口大小
    QFile file("C:\\Users\\dillonl\\Desktop\\QT\\demo-2\\qss\\style.css");
//    QFile file(":/qss/style.css");

    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QString style = this->styleSheet();
        style += QLatin1String(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
    for(int i = 0; i < 4; i++){
        tlabel[i] = new QLabel(this);
        tlabel[i]->setContentsMargins(0,0,0,0);
        tlabel[i]->setFrameStyle(QFrame::NoFrame);
    }
    for(int i = 0; i < 4; i++){
        list[i] = new QListWidget(this);
        list[i]->setStyleSheet("QListWidget{background:#f0f;border:none;}");
        list[i]->setMaximumWidth(210);
    }

    tlabel[0]->setText("在线音乐");
    tlabel[1]->setText("我的音乐");
    tlabel[2]->setText("创建的歌单");
    tlabel[3]->setText("收藏的歌单");

    vlayout = new QVBoxLayout(this);
    vlayout->addWidget(list[0]);
    vlayout->addWidget(tlabel[0]);
    vlayout->addWidget(list[1]);
    vlayout->addWidget(tlabel[1]);
    vlayout->addWidget(list[2]);
    vlayout->addWidget(tlabel[2]);
    vlayout->addWidget(list[3]);
    vlayout->addWidget(tlabel[3]);
    vlayout->addStretch();
    vlayout->setContentsMargins(0,0,0,0);

    sarea = new QScrollArea(this);
    sarea->setMinimumWidth(230);
    sarea->setMaximumWidth(210);
    sarea->setMinimumHeight(600);
    sarea->setMaximumHeight(600);
    sarea->setLayout(vlayout);

    widget = new QWidget(this);
    widget->setLayout(vlayout);
    sarea->setWidget(widget);

//    layout = new QHBoxLayout(this);
//    layout->setContentsMargins(0,0,0,0);
//    layout->addWidget(sarea);

//    QHBoxLayout *layouts=new QHBoxLayout;
//    layouts->setParent(this); // 设置在父级之上
//    layouts->setDirection(QHBoxLayout::RightToLeft);
//    ql_2 = new QLabel("123");
//    ql_2->setStyleSheet("QLabel{background:#f0f;}");
//    ql_2->setParent(this);
//    layouts->addWidget(ql_2);
//    layouts->addStretch(2);
//    this->setLayout(layouts);



//    b1.setParent(this);
//    b1.setFixedSize(150, 40);
//    b1.move(100, 100);
//    b1.setText("按钮一");
//    b2 = new QPushButton(this);
//    b2->setParent(this);
//    b2->move(600, 200);
//    b2->setText("按钮二");
//    connect(&b1, &QPushButton::pressed, this, &MainWindow::customClick);
//    ql_1 = new QLabel();
//    ql_1->setParent(this);
//    ql_1->setGeometry(1,1,200,200);
//
//    qm_1 = new QMovie("C:\\Users\\dillonl\\Desktop\\QT\\demo-2\\hu.png");
//    ql_1->setMovie(qm_1);
//    ql_1->setScaledContents(true); // 根据比例填充图片
//    qm_1->start();
//    ql_1->setStyleSheet("border-radius:40px;");
//    ql_1->setPixmap(QPixmap::fromImage(qm_1));
    /* &b1：信号发送者，指针类型
     * &QPushButton: 处理的信号 发送着的类名::信号名字
     * this：信号接收者
     * &MainWindow::close: 槽函数，信号处理函数
     */
}

//void MainWindow::customClick() {
//    if (isFullScreen() == 1) {
//        // this->showMinimized(); // 最小化
//        this->showNormal(); // 恢复原屏
//    } else {
//        this->showFullScreen(); // 最大化
//    }
//    std::cout << isFullScreen() << std::endl;
//}

MainWindow::~MainWindow() {
}


