//
// Created by dinglong on 2023/1/23 20:06
//
#include "container.h"

container::container(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(100, 450);
    layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addSpacing(35);
    widget = new QWidget(this);
    lWidget = new QWidget(this);
    lWidget->setMinimumSize(500, 75);
    lWidget->setStyleSheet("QWidget{background:#ff0}");
    lLayout = new QHBoxLayout;
    lLayout->setAlignment(Qt::AlignLeft);
    lLayout->setMargin(0);
    lLabel = new QLabel;
    rLabel = new QLabel;
    refresh = new QLabel;
    lLabel->setFixedSize(26,26);
    rLabel->setFixedSize(26,26);
    refresh->setFixedSize(20,20);
    QPixmap lPixmap(":/resource/images/left_arrow.png");
    QPixmap rPixmap(":/resource/images/right_arrow.png");
    QPixmap refreshPix(":/resource/images/refresh.png");
    lLabel->setScaledContents(true);
    rLabel->setScaledContents(true);
    refresh->setScaledContents(true);
    lLabel->setPixmap(lPixmap);
    rLabel->setPixmap(rPixmap);
    refresh->setPixmap(refreshPix);
    lLabel->setStyleSheet("padding:4px;");
    rLabel->setStyleSheet("padding:4px;");
    lLayout->addWidget(lLabel);
    lLayout->addSpacing(8);
    lLayout->addWidget(rLabel);
    lLayout->addSpacing(14);
    lLayout->addWidget(refresh);

    rWidget = new QWidget(this);
    rWidget->setMinimumSize(700, 75);
    rWidget->setStyleSheet("QWidget{background:#0f0}");
    widget->setStyleSheet("QWidget{background:#f00}");
    layout->addWidget(lWidget);
    layout->addWidget(rWidget);
    widget->setLayout(layout);

//    QLineEdit *input = new QLineEdit;
//    input->setEchoMode(QLineEdit::Normal);
//    input->setPlaceholderText("搜索音乐");
    QWidget *sWidget = new QWidget(this);
    sWidget->setMaximumSize(185, 32);
//    sWidget->setProperty("class", "searchBox");
    sWidget->setStyleSheet("QWidget{background:#e3e3e3;border-radius:15px;}");
    QHBoxLayout *sLayout = new QHBoxLayout();
    QLabel *simgLabel = new QLabel();
    QPixmap raImg(":/resource/images/search.png");
    simgLabel->setPixmap(raImg);
    simgLabel->setMaximumSize(40, 15);
    simgLabel->setScaledContents(true);
    simgLabel->setStyleSheet("QLabel{margin-left:15px;margin-right:10px;}");
//    simgLabel->setStyleSheet("QLabel{background:#f00}");
    sLayout->addWidget(simgLabel);
    QLabel *txtLabel = new QLabel();
    txtLabel->setProperty("class", "packHolder");
    txtLabel->setText("搜索音乐");
    sLayout->addWidget(txtLabel);
    sWidget->setLayout(sLayout);
    sLayout->setSpacing(0);
    sLayout->setMargin(0);
    lLayout->addWidget(sWidget);
    lLayout->setSpacing(0);
    lLayout->setMargin(0);
    lWidget->setLayout(lLayout);
    QLabel *rimgLabel = new QLabel();
    QPixmap rasImg(":/resource/images/musicn.png");
    rimgLabel->setPixmap(rasImg);
    rimgLabel->setMaximumSize(14, 14);
    rimgLabel->setScaledContents(true);
    lLayout->addWidget(rimgLabel);
//
//    QHBoxLayout *rlayout = new QHBoxLayout(this);
}

container::~container() {
}