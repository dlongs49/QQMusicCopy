//
// Created by dinglong on 2024/4/13 12:22
//

#include "houseSinger.h"

HouseSinger::HouseSinger(QWidget *parent) : QWidget(parent){
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    // 更多qq音乐客户端对应的页面 https://y.qq.com/m/client/config/url.pc.json?pcachetime=1712844941
    //对应的qq页面  https://y.qq.com/wk_v17/#/musicroom/recommend
    this->setFixedSize(820, 1000);
    widget = new QWidget(this);
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, 820, 500);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);

    singerTop();
    singerList();
    widget->setLayout(layout);
}

void HouseSinger::singerTop(){

};
void HouseSinger::singerList(){

};