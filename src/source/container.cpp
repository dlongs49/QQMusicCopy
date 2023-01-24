//
// Created by dinglong on 2023/1/23 20:06
//
#include "../header/container.h"
container::container(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet("QWidget{background:#f0f}");
    label = new QLabel(this);
    label->setText("");
}
container::~container() {
}