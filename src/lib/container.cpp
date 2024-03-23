//
// Created by dinglong on 2023/1/23 20:06
//
#include "container.h"

container::container(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(100, 450);
    topMenu = new TopMenu(this);
}

container::~container() {
}