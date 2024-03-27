#include "container.h"

container::container(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(100, 450);

    topMenu = new TopMenu(this);
    connect(topMenu, SIGNAL(onFocus(bool)),this,SLOT(handleEmit(bool)));
    hotSearch = new HotSearch(this);
    connect(topMenu, SIGNAL(onSettPopup(bool)),this,SLOT(showSettPopup(bool)));
    settMenu = new SettMenu(this);
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
container::~container() {
}