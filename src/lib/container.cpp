#include "container.h"

container::container(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(100, 450);

    topMenu = new TopMenu(this);
    connect(topMenu, SIGNAL(onFocus(bool)),this,SLOT(handleEmit(bool)));
    hotSearch = new HotSearch(this);

//    settMenu = new SettMenu(this);
}
bool container::handleEmit(bool flag){
    if(flag){
        hotSearch->show();
    }else{
        hotSearch->hide();
    }
}
container::~container() {
}