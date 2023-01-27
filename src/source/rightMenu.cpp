//
// Created by dinglong on 2023/1/23 19:06
//

#include "../header/rightMenu.h"
#include <iostream>
#include <QFile>
#include <QString>

using namespace std;

rightMenu::rightMenu(QWidget *parent) : QWidget(parent) {
    this->setMaximumWidth(210);
    cout << this->height() << endl;
    this->setMinimumHeight(this->height());
    this->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
    this->setAutoFillBackground(false);
    readQssStyle(); // 样式文件引入读取
    for (int i = 0; i < 4; i++) {
        tlabel[i] = new QLabel(this);
        tlabel[i]->setContentsMargins(0, 0, 0, 0);
        tlabel[i]->setFrameStyle(QFrame::NoFrame);
        tlabel[i]->setProperty("class", "menuTitle");
    }
    for (int i = 0; i < 4; i++) {
        list[i] = new QListWidget(this);

        list[i]->setMaximumWidth(182);
        list[i]->setContentsMargins(0, 0, 0, 0);
        list[i]->setProperty("class", "menuItem");
        list[i]->setCursor(QCursor(Qt::PointingHandCursor));
    }

    tlabel[0]->setText("在线音乐");
    tlabel[1]->setText("我的音乐");
    tlabel[2]->setText("创建的歌单");
    tlabel[3]->setText("收藏的歌单");


    QVBoxLayout *outLayout = new QVBoxLayout(this);
    // Logo放置处
    QLabel *label = new QLabel(this);
    outLayout->setSpacing(0);
    outLayout->setMargin(0);
//    label->setMaximumSize(320,100);
    QPixmap pixmap(":/resource/images/logo.png");
    label->setPixmap(pixmap);

//    label->setScaledContents(true); // 图片尺寸随之 label 的大小而变化
    label->setProperty("class","logo");
    connect(this, SIGNAL(clicked()), this, SLOT(customClick()));
    outLayout->addWidget(label);
    vlayout = new QVBoxLayout();
    vlayout->addWidget(tlabel[0]);
    vlayout->addWidget(list[0]);
    vlayout->addWidget(tlabel[1]);
    vlayout->addWidget(list[1]);
    vlayout->addWidget(tlabel[2]);
    vlayout->addWidget(list[2]);
    vlayout->addWidget(tlabel[3]);
    vlayout->addWidget(list[3]);
    vlayout->addStretch();
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    sarea = new QScrollArea(this);
    widget = new QWidget();
    widget->setMinimumWidth(this->width() - 20); // 这里拿到父级的宽度 减去 10像素(10px是滚动条的宽度)
    widget->setLayout(vlayout);
    sarea->setWidget(widget);
    outLayout->addWidget(sarea);


    onlineMusic();
    myMusic();
    createSongList();
    facoriteSonglist();
}

void rightMenu::customClick() {
    cout << isFullScreen() << endl;
    if (isFullScreen() == 1) {
        this->showNormal();
    } else {
        this->setWindowFlags(Qt::Window);
        this->showFullScreen();
    }
}
void rightMenu::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}
// 样式
void rightMenu::readQssStyle() {
    QFile file(":/resource/qss/style.qss");
    file.open(QIODevice::ReadOnly);
    if (file.isOpen()) {
        QString style = this->styleSheet();
        style += QLatin1String(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
}

// 在线音乐
void rightMenu::onlineMusic() {
    recommend = new QListWidgetItem();
    recommend->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    recommend->setText("推荐");
    list[0]->addItem(recommend);
//    recommend->setSizeHint(QSize(0,30)); // 高度设置  qss已设置，留存
//    list[0]->setFocusPolicy(Qt::NoFocus); // 取消选中虚线 焦点消失  qss已设置，留存
    list[0]->setMaximumHeight(174);


    QListWidgetItem *musicShop = new QListWidgetItem();
    musicShop->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    musicShop->setText("音乐馆");
    list[0]->addItem(musicShop);

    QListWidgetItem *video = new QListWidgetItem();
    video->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    video->setText("视频");
    list[0]->addItem(video);

    QListWidgetItem *radioStation = new QListWidgetItem();
    radioStation->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    radioStation->setText("电台");
    list[0]->addItem(radioStation);
}

// 我的音乐
void rightMenu::myMusic() {
    QListWidgetItem *myLove = new QListWidgetItem();
    myLove->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    myLove->setText("我喜欢");
    list[1]->addItem(myLove);
    list[1]->setMinimumHeight(210);


    QListWidgetItem *localDownLoad = new QListWidgetItem();
    localDownLoad->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    localDownLoad->setText("本地和下载");
    list[1]->addItem(localDownLoad);

    QListWidgetItem *recenPlay = new QListWidgetItem();
    recenPlay->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    recenPlay->setText("最近播放");
    list[1]->addItem(recenPlay);

    QListWidgetItem *auditionList = new QListWidgetItem();
    auditionList->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    auditionList->setText("试听列表");
    list[1]->addItem(auditionList);


    QListWidgetItem *purchasedMusic = new QListWidgetItem();
    purchasedMusic->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    purchasedMusic->setText("已购音乐");
    list[1]->addItem(purchasedMusic);
}

// 创建的歌单
void rightMenu::createSongList() {
    QListWidgetItem *myLove = new QListWidgetItem();
    myLove->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    myLove->setText("我的歌单");
    list[2]->addItem(myLove);
    list[2]->setMaximumHeight(70);
}

// 收藏的歌单
void rightMenu::facoriteSonglist() {
    QListWidgetItem *myCollection = new QListWidgetItem();
    myCollection->setIcon(QIcon(QPixmap(":/resource/icon/nav_music.png").scaled(60, 60)));
    myCollection->setText("我的收藏");
    list[3]->addItem(myCollection);
    list[3]->setMaximumHeight(70);
}

rightMenu::~rightMenu() {
}