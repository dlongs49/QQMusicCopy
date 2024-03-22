//
// Created by dinglong on 2023/1/23 20:06
//
#include "container.h"

container::container(QWidget *parent) : QWidget(parent) {
    this->setMinimumSize(100, 450);
    layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addSpacing(35);

    widget = new QWidget(this);
    lWidget = new QWidget(this);
    lWidget->setMinimumSize(500, 75);
    lLayout = new QHBoxLayout;
    lLayout->setAlignment(Qt::AlignLeft);
    lLayout->setMargin(0);
    lLabel = new QLabel;
    rLabel = new QLabel;
    refresh = new QLabel;
    lLabel->setFixedSize(26, 26);
    rLabel->setFixedSize(26, 26);
    refresh->setFixedSize(20, 20);
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
    lLayout->addSpacing(20);

//    widget->setStyleSheet("QWidget{background:#f00}");

    widget->setLayout(layout);




    sLayout = new QHBoxLayout;
    sLayout->setSpacing(0);
    sLayout->setMargin(0);
    sWidget = new QWidget(this);
    int search_w = 130;
    sWidget->setFixedSize(search_w, 32);
    sWidget->setObjectName("searchBox");
    simgLabel = new QLabel;
    QPixmap searchIcon(":/resource/images/search.png");
    simgLabel->setPixmap(searchIcon);
    simgLabel->setFixedSize(16, 18);
    simgLabel->setScaledContents(true);
    simgLabel->setContentsMargins(0, 2, 0, 0);
    txtLabel = new QLabel;
    txtLabel->setObjectName("packHolder");
    txtLabel->setText("搜索音乐");
    searInput = new QLineEdit;
    searInput->setObjectName("searInput");
    searInput->setEchoMode(QLineEdit::Normal);
    searInput->setFixedSize(search_w-30,30);
    sLayout->addWidget(searInput);
    sLayout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//    sLayout->addWidget(simgLabel);
//    sLayout->setSpacing(4);
//    sLayout->addWidget(txtLabel);
    sWidget->setLayout(sLayout);



    rimgLabel = new QLabel;
    QPixmap rasImg(":/resource/images/listen_music.png");
    rimgLabel->setPixmap(rasImg);
    rimgLabel->setFixedSize(22, 22);
    rimgLabel->setScaledContents(true);
    lLayout->addWidget(sWidget);
    lLayout->addSpacing(10);
    lLayout->addWidget(rimgLabel);
    lLayout->setSpacing(0);
    lLayout->setMargin(0);
    lWidget->setLayout(lLayout);


    rWidget = new QWidget(this);
    rWidget->setMinimumSize(700, 75);





    layout->addWidget(lWidget);
    layout->addWidget(rWidget);






//    rWidget->setStyleSheet("QWidget{background:#0f0}");
//
//    QHBoxLayout *rlayout = new QHBoxLayout(this);
}

container::~container() {
}