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
    widget->setFixedWidth(210);
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, 210, 500);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);

    onlineMusic();
    myMusic();
    widget->setLayout(layout);
}

// 在线音乐
void rightMenu::onlineMusic() {

    title = new QLabel;
    title->setFixedWidth(this->width() - 20);
    title->setObjectName("title");
    title->setText("在线音乐");
    layout->addWidget(title);
    layout->addSpacing(8);

    QStringList list = {"推荐", "乐馆", "视频", "雷达"};
    for (int i = 0; i < list.size(); ++i) {
        onlineItem[i] = new QWidget;
        onlineItem[i]->setFixedSize(this->width() - 20, 38);
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
        layout->addWidget(onlineItem[i]);
        layout->addSpacing(3);
    }
    layout->addSpacing(10);
}

// 我的音乐
void rightMenu::myMusic() {
    containerBox = new QWidget(widget);
    containerLayout = new QVBoxLayout;
    containerBox->setLayout(containerLayout);

    title = new QLabel;
    title->setFixedWidth(this->width() - 20);
    title->setObjectName("title");
    title->setText("我的音乐");
    layout->addWidget(title);
    layout->addSpacing(8);

    QStringList list = {"喜欢", "最近播放", "本地和下载", "已购音乐", "试听列表"};
    for (int i = 0; i < list.size(); ++i) {
        myMusicItem[i] = new QWidget;
        myMusicItem[i]->setFixedSize(this->width() - 20, 38);
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
        layout->addWidget(myMusicItem[i]);
        layout->addSpacing(3);
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