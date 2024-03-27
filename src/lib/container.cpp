#include "container.h"

container::container(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(100, 450);

    topMenu = new TopMenu(this);
    connect(topMenu, SIGNAL(onFocus(bool)),this,SLOT(handleEmit(bool)));
    hotSearch = new HotSearch(this);
    connect(topMenu, SIGNAL(onSettPopup(bool)),this,SLOT(showSettPopup(bool)));
    connect(topMenu, SIGNAL(onHandle(QString)),this,SLOT(emitHandle(QString)));
    settMenu = new SettMenu(this);
    connect(topMenu, SIGNAL(onDownInfo(bool)),this,SLOT(handleDownInfo(bool)));
    downInfo = new DownInfo(this);
}
bool container::handleEmit(bool flag){
    if(flag){
        hotSearch->show();
    }else{
        hotSearch->hide();
    }
}
bool container::showSettPopup(bool flag){
    if(flag){
        settMenu->show();
    }else{
        settMenu->hide();
    }
}
bool container::handleDownInfo(bool flag){
    if(flag){
        downInfo->show();
    }else{
        downInfo->hide();
    }
}
QString container::emitHandle(QString str){
    emit mainHandle(str);
}
container::~container() {
}