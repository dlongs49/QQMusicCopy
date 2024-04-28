//
// Created by dinglong on 2023/1/23 19:06
//

#include "rightMenu.h"

rightMenu::rightMenu(QWidget *parent) : QWidget(parent) {

    loadQSS();
    tools = new Tools();

    this->setFixedSize(210, 800);

    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);
    widget->setLayout(layout);


    logoLabel = new QLabel;
    logoLabel->setFixedSize(90,25);
    logoLabel->setScaledContents(true);
    QPixmap logoImg(":/resource/images/logo.png");
    logoLabel->setPixmap(logoImg);
    layout->addSpacing(20);
    layout->addWidget(logoLabel,0,Qt::AlignHCenter);
    layout->addSpacing(20);

    containerBox = new QWidget;
    containerBox->setFixedSize(190,800);
    containerLayout = new QVBoxLayout;
    containerLayout->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    containerBox->setLayout(containerLayout);

    scrollArea = new QScrollArea();
    scrollArea->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, this->width(), 300);
    scrollArea->setWidget(containerBox);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);

    onlineMusic();
    myMusic();
}

// 在线音乐
void rightMenu::onlineMusic() {

    title = new QLabel;
    title->setObjectName("title");
    title->setText("在线音乐");
    containerLayout->addWidget(title);
    containerLayout->addSpacing(6);

    QStringList list = {"推荐", "乐馆", "视频", "雷达"};
    for (int i = 0; i < list.size(); ++i) {
        onlineItem[i] = new QWidget;
        onlineItem[i]->setFixedSize(containerBox->width()-10, 38);
        onlineItem[i]->setObjectName("item");
        onlineItem[i]->setCursor(Qt::PointingHandCursor);

        itemLayout = new QHBoxLayout;
        itemLayout->setAlignment(Qt::AlignLeft);
        onlineItem[i]->setLayout(itemLayout);

        iconLabel = new QLabel;
        iconLabel->setObjectName("iconLabel");
        iconLabel->setFont(tools->aliIcon());
        iconLabel->setText(QChar(0xea85));

        menuTitle = new QLabel;
        menuTitle->setObjectName("menuTitle");
        menuTitle->setText(list[i]);

        itemLayout->addWidget(iconLabel);
        itemLayout->setSpacing(4);
        itemLayout->addWidget(menuTitle);
        itemLayout->setSpacing(6);
        containerLayout->addWidget(onlineItem[i]);
        containerLayout->addSpacing(2);
    }
    containerLayout->addSpacing(10);
}

// 我的音乐
void rightMenu::myMusic() {

    title = new QLabel;
    title->setObjectName("title");
    title->setText("我的音乐");
    containerLayout->addWidget(title);
    containerLayout->addSpacing(6);

    QStringList list = {"喜欢", "最近播放", "本地和下载", "已购音乐", "试听列表"};
    for (int i = 0; i < list.size(); ++i) {
        myMusicItem[i] = new QWidget;
        myMusicItem[i]->setFixedSize(containerBox->width() - 10, 38);
        myMusicItem[i]->setObjectName("item");
        myMusicItem[i]->setCursor(Qt::PointingHandCursor);

        itemLayout = new QHBoxLayout;
        itemLayout->setAlignment(Qt::AlignLeft);
        myMusicItem[i]->setLayout(itemLayout);

        iconLabel = new QLabel;
        iconLabel->setObjectName("iconLabel");
        iconLabel->setFont(tools->aliIcon());
        iconLabel->setText(QChar(0xea85));

        menuTitle = new QLabel;
        menuTitle->setText("menuTitle");
        menuTitle->setText(list[i]);

        itemLayout->addWidget(iconLabel);
        itemLayout->setSpacing(4);
        itemLayout->addWidget(menuTitle);
        itemLayout->setSpacing(6);
        containerLayout->addWidget(myMusicItem[i]);
        containerLayout->addSpacing(2);
    }
}

// 我的歌单
void rightMenu::myPlaySongs() {}

void rightMenu::loadQSS() {
    QFile qss(":/resource/qss/style.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}

rightMenu::~rightMenu() {
}