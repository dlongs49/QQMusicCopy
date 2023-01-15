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
    QString fileUrl = "C:\\Users\\dillonl\\Desktop\\QT\\demo-2";
    readQssStyle(); // 样式文件引入读取

    for (int i = 0; i < 4; i++) {
        tlabel[i] = new QLabel(this);
        tlabel[i]->setContentsMargins(0, 0, 0, 0);
        tlabel[i]->setFrameStyle(QFrame::NoFrame);
    }
    for (int i = 0; i < 4; i++) {
        list[i] = new QListWidget(this);
        list[i]->setMaximumWidth(210);
        list[i]->setProperty("class","menuItem");
        list[i]->setCursor(QCursor(Qt::PointingHandCursor));
    }

    tlabel[0]->setText("在线音乐");
    tlabel[1]->setText("我的音乐");
    tlabel[2]->setText("创建的歌单");
    tlabel[3]->setText("收藏的歌单");

    vlayout = new QVBoxLayout(this);
//    vlayout->addWidget(list[0]); qq音乐 logo放置处
    vlayout->addWidget(tlabel[0]);
    vlayout->addWidget(list[0]);
    vlayout->addWidget(tlabel[1]);
    vlayout->addWidget(list[1]);
    vlayout->addWidget(tlabel[2]);
    vlayout->addWidget(list[2]);
    vlayout->addWidget(tlabel[3]);
    vlayout->addStretch();
    vlayout->setContentsMargins(0, 0, 0, 0);

    sarea = new QScrollArea(this);
    sarea->setMinimumWidth(230);
    sarea->setMaximumWidth(210);
    sarea->setMinimumHeight(600);
    sarea->setMaximumHeight(600);
    sarea->setLayout(vlayout);

    widget = new QWidget(this);
    widget->setLayout(vlayout);
    sarea->setWidget(widget);


    recommend = new QListWidgetItem();
    recommend->setIcon(QIcon(QPixmap(fileUrl+"\\static\\images\\nav_music.png").scaled(60,60)));
    recommend->setText("推荐");
    recommend->setSizeHint(QSize(4,30));
    list[0]->addItem(recommend);

}
// 样式
void MainWindow::readQssStyle(){
    QFile file("C:\\Users\\dillonl\\Desktop\\QT\\demo-2\\qss\\style.css");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QString style = this->styleSheet();
        style += QLatin1String(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
}
//void MainWindow::setCursor(QCursor){
//    setCursor(Qt::ArrowCursor);
//}
MainWindow::~MainWindow() {
}


