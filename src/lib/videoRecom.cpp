//
// Created by dinglong on 2024/4/16 11:51
//

#include "videoRecom.h"

VideoRecom::VideoRecom(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();

    // qq音乐精选接口 http://u6.y.qq.com/cgi-bin/musics.fcg?_=1712662759896&sign=zzcd87edc7qul46ovmthfs0znwytvxsfm6kmwd0777b5b

    this->setFixedSize(820, 1350);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    bannerTop();
    newest();
    hotList();
    latestIssue();
    classPrefe();
    widget->setLayout(layout);


}

void VideoRecom::bannerTop() {

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(widget->width() - 20, 178);
    containerBox->installEventFilter(this);
    containerBox->setObjectName("selectedBox");

    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(contentLayout);

    scrollBox = new QWidget(containerBox);
    scrollBox->setFixedSize(containerBox->width() - 60, containerBox->height());
    scrollBox->setObjectName("bannerBox");

    bannerLayout = new QHBoxLayout;
    bannerLayout->setSpacing(0);
    bannerLayout->setMargin(0);
    bannerLayout->setAlignment(Qt::AlignLeft);

    bannerBox = new QWidget(scrollBox);
    bannerBox->setLayout(bannerLayout);
    animation[0] = new QPropertyAnimation(bannerBox, "geometry");
    animation[0]->setDuration(300);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6483999.jpg"
            << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6484203.jpg"
            << "https://y.qq.com/music/common/upload/ocs/2681676c054da54091a9f000208e81bf.png"
            << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6482174.jpg";
    for (int i = 0; i < imgList.size(); ++i) {
        int item_w = (scrollBox->width()/2)-10;
        bannerItem[i] = new QWidget;
        bannerItem[i]->installEventFilter(this);
        bannerItem[i]->setObjectName("bannerItem");
        bannerItem[i]->setFixedSize(item_w, containerBox->height());
        bannerImgLayout = new QVBoxLayout;
        bannerImgLayout->setSpacing(0);
        bannerImgLayout->setMargin(0);
        bannerImgLayout->setAlignment(Qt::AlignTop);

        bannerImg = new QLabel(bannerItem[i]);
        bannerImg->setCursor(Qt::PointingHandCursor);
        bannerImg->setScaledContents(true);
        bannerImg->setObjectName("bannerImg");
        bannerImg->setProperty("index", i);
        bannerImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        bannerImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 16));
        bannerImg->setFixedSize(item_w, containerBox->height());

        bannerImgLayout->addWidget(bannerImg);
        bannerItem[i]->setLayout(bannerImgLayout);
        bannerLayout->addWidget(bannerItem[i]);
        if (i != imgList.size() - 1) {
            bannerLayout->addSpacing(20);
        }
    }

    contentLayout->addWidget(arrowBox(0, "left"));
    contentLayout->addWidget(scrollBox);
    contentLayout->addWidget(arrowBox(0, "right"));
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
}

// 最新
void VideoRecom::newest() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(this->width() - 20);
    containerLayout = new QVBoxLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerBox->setLayout(containerLayout);


    titleLayout = new QHBoxLayout;
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);
    titleBox = new QWidget(containerBox);
    titleBox->setLayout(titleLayout);

    titLeftLayout = new QHBoxLayout;
    titLeftLayout->setSpacing(0);
    titLeftLayout->setMargin(0);
    titLeftLayout->setAlignment(Qt::AlignLeft);

    title = new QLabel;
    title->setObjectName("title");
    title->setText("最新");

    moreRightLayout = new QHBoxLayout;
    moreRightLayout->setSpacing(0);
    moreRightLayout->setMargin(0);
    moreRightLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    rightMoreBox = new QLabel;
    rightMoreBox->setFixedWidth(45);
    rightMoreBox->setObjectName("rightMoreBox");
    rightMoreBox->setCursor(Qt::PointingHandCursor);
    rightMoreBox->setLayout(moreRightLayout);

    moreTitle = new QLabel;
    moreTitle->setObjectName("moreTit");
    moreTitle->setText("更多");
    moreRightLayout->addWidget(moreTitle);
    moreRightLayout->addSpacing(5);

    arrowTitle = new QLabel;
    arrowTitle->setObjectName("arrowMore");
    arrowTitle->setFont(tools->aliIcon());
    arrowTitle->setText(QChar(0xe601));
    arrowTitle->setFixedSize(14, 22);
    moreRightLayout->addWidget(arrowTitle);


    titleLayout->addWidget(title);
    titleLayout->addWidget(rightMoreBox);
    titleLayout->addSpacing(20);
    containerLayout->addWidget(titleBox);

    contentBox = new QWidget(containerBox);
    contentBox->setFixedSize(containerBox->width(), 205);
    contentBox->installEventFilter(this);
    contentBox->setObjectName("newestBox");
    containerLayout->addSpacing(6);
    containerLayout->addWidget(contentBox);

    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    contentBox->setLayout(contentLayout);

    bannerBox = new QWidget(contentBox);
    bannerBox->setFixedSize(contentBox->width() - 60, contentBox->height());
    bannerBox->setObjectName("bannerBox");

    bannerLayout = new QHBoxLayout;
    bannerLayout->setSpacing(0);
    bannerLayout->setMargin(0);
    bannerLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[1] = new QWidget(bannerBox);
    wrapconBox[1]->setLayout(bannerLayout);
    animation[1] = new QPropertyAnimation(wrapconBox[1], "geometry");
    animation[1]->setDuration(300);


    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QfX3MU2dzluKMUOBEjz0h6g/300"
            << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QY8gA4UrJxhxQ9BBHZHDyFQ/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqojSibubibse2uIWSaZhZ39n1F1CQCXVuMGdw/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqoglWn5x5ITgE8KljTdMrDCyBpia0Jkn6BDg/300?n=1"
            << "https://qpic.y.qq.com/music_cover/I2ZdwiaF8XY3CVB1y18cmH6dVjiaC6hprhowF1emvMrTFIxCibB04GH5A/300?n=1"
            << "https://qpic.y.qq.com/music_cover/4pmnRu5sL5QbtO8OS8NKJTN5qBpjx5XMS8vhm4hcZSN7PEHPQ68C0Q/300?n=1";
    for (int i = 0; i < imgList.size(); ++i) {
        int item_w = (bannerBox->width()/3) - 12;
        newestItem[i] = new QWidget(contentBox);
        newestItem[i]->setFixedWidth(item_w);
        newestItem[i]->setObjectName("bannerItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(newestItem[i]);
        itemImg->setFixedSize(item_w, 142);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("newestImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 12));

        maskBox = new QWidget(itemImg);
        maskBox->setFixedSize(itemImg->width(), itemImg->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(itemImg);
        playBox->setFixedSize(51, 51);
        playBox->setObjectName("playBox");
        playBox->setFont(tools->aliIcon());
        playBox->setText(QChar(0xea85));
        playBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        int p_w = (itemImg->width() / 2) - (playBox->width() / 2);
        int p_h = (itemImg->height() / 2) - (playBox->height() / 2);
        playBox->move(p_w, p_h);
        playBox->setVisible(false);

        playCountBox = new QWidget(itemImg);
        playCountBox->setObjectName("playCountBox");
        playCountLayout = new QHBoxLayout;
        playCountLayout->setMargin(0);
        playCountLayout->setSpacing(0);
        playCountLayout->setAlignment(Qt::AlignCenter);
        playCountBox->setLayout(playCountLayout);
        playCountBox->setVisible(false);

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe633));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText("203.6万");
        playCount->setFixedSize(playCount->sizeHint());
        playCount->setAlignment(Qt::AlignCenter);

        playCountLayout->addWidget(playSicon);
        playCountLayout->addSpacing(3);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width() + 26;
        playCountBox->setGeometry(itemImg->width() - sc - 10, itemImg->height() - 30, sc, 22);


        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        QString txt = tools->textElps("贺峻霖全新单曲《缘故》正式上线正式上线正式上线 ", itemImg->width()-6, title->font());
        title->setText(txt);
        title->setAlignment(Qt::AlignTop);

        author = new QLabel;
        author->setCursor(Qt::PointingHandCursor);
        author->setObjectName("author");
        author->setText("弦子");
        author->setFixedSize(author->sizeHint());
        author->setAlignment(Qt::AlignTop);

        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(author);
        newestItem[i]->setLayout(itemLayout);
        bannerLayout->addWidget(newestItem[i]);
        bannerLayout->setSpacing(20);
    }

    contentLayout->addWidget(arrowBox(1, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(1, "right"));

    layout->addWidget(containerBox);
    layout->addSpacing(20);
}

// 热门
void VideoRecom::hotList() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(this->width() - 20);
    containerLayout = new QVBoxLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerBox->setLayout(containerLayout);


    titleLayout = new QHBoxLayout;
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);
    titleBox = new QWidget(containerBox);
    titleBox->setLayout(titleLayout);

    titLeftLayout = new QHBoxLayout;
    titLeftLayout->setSpacing(0);
    titLeftLayout->setMargin(0);
    titLeftLayout->setAlignment(Qt::AlignLeft);

    title = new QLabel;
    title->setObjectName("title");
    title->setText("热门");

    moreRightLayout = new QHBoxLayout;
    moreRightLayout->setSpacing(0);
    moreRightLayout->setMargin(0);
    moreRightLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    rightMoreBox = new QLabel;
    rightMoreBox->setFixedWidth(45);
    rightMoreBox->setObjectName("rightMoreBox");
    rightMoreBox->setCursor(Qt::PointingHandCursor);
    rightMoreBox->setLayout(moreRightLayout);

    moreTitle = new QLabel;
    moreTitle->setObjectName("moreTit");
    moreTitle->setText("更多");
    moreRightLayout->addWidget(moreTitle);
    moreRightLayout->addSpacing(5);

    arrowTitle = new QLabel;
    arrowTitle->setObjectName("arrowMore");
    arrowTitle->setFont(tools->aliIcon());
    arrowTitle->setText(QChar(0xe601));
    arrowTitle->setFixedSize(14, 22);
    moreRightLayout->addWidget(arrowTitle);


    titleLayout->addWidget(title);
    titleLayout->addWidget(rightMoreBox);
    titleLayout->addSpacing(20);
    containerLayout->addWidget(titleBox);

    contentBox = new QWidget(containerBox);
    contentBox->setFixedSize(containerBox->width(), 205);
    contentBox->installEventFilter(this);
    contentBox->setObjectName("hotBox");
    containerLayout->addSpacing(6);
    containerLayout->addWidget(contentBox);

    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    contentBox->setLayout(contentLayout);

    bannerBox = new QWidget(contentBox);
    bannerBox->setFixedSize(contentBox->width() - 60, contentBox->height());
    bannerBox->setObjectName("bannerBox");

    bannerLayout = new QHBoxLayout;
    bannerLayout->setSpacing(0);
    bannerLayout->setMargin(0);
    bannerLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[2] = new QWidget(bannerBox);
    wrapconBox[2]->setLayout(bannerLayout);
    animation[2] = new QPropertyAnimation(wrapconBox[1], "geometry");
    animation[2]->setDuration(300);


    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QfX3MU2dzluKMUOBEjz0h6g/300"
            << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QY8gA4UrJxhxQ9BBHZHDyFQ/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqojSibubibse2uIWSaZhZ39n1F1CQCXVuMGdw/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqoglWn5x5ITgE8KljTdMrDCyBpia0Jkn6BDg/300?n=1"
            << "https://qpic.y.qq.com/music_cover/I2ZdwiaF8XY3CVB1y18cmH6dVjiaC6hprhowF1emvMrTFIxCibB04GH5A/300?n=1"
            << "https://qpic.y.qq.com/music_cover/4pmnRu5sL5QbtO8OS8NKJTN5qBpjx5XMS8vhm4hcZSN7PEHPQ68C0Q/300?n=1";
    for (int i = 0; i < imgList.size(); ++i) {
        int item_w = (bannerBox->width()/3) - 12;
        hotItem[i] = new QWidget(contentBox);
        hotItem[i]->setFixedWidth(item_w);
        hotItem[i]->setObjectName("bannerItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(hotItem[i]);
        itemImg->setFixedSize(item_w, 142);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("hotImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 12));

        maskBox = new QWidget(itemImg);
        maskBox->setFixedSize(itemImg->width(), itemImg->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(itemImg);
        playBox->setFixedSize(51, 51);
        playBox->setObjectName("playBox");
        playBox->setFont(tools->aliIcon());
        playBox->setText(QChar(0xea85));
        playBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        int p_w = (itemImg->width() / 2) - (playBox->width() / 2);
        int p_h = (itemImg->height() / 2) - (playBox->height() / 2);
        playBox->move(p_w, p_h);
        playBox->setVisible(false);

        playCountBox = new QWidget(itemImg);
        playCountBox->setObjectName("playCountBox");
        playCountLayout = new QHBoxLayout;
        playCountLayout->setMargin(0);
        playCountLayout->setSpacing(0);
        playCountLayout->setAlignment(Qt::AlignCenter);
        playCountBox->setLayout(playCountLayout);
        playCountBox->setVisible(false);

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe633));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText("203.6万");
        playCount->setFixedSize(playCount->sizeHint());
        playCount->setAlignment(Qt::AlignCenter);

        playCountLayout->addWidget(playSicon);
        playCountLayout->addSpacing(3);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width() + 26;
        playCountBox->setGeometry(itemImg->width() - sc - 10, itemImg->height() - 30, sc, 22);


        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        QString txt = tools->textElps("贺峻霖全新单曲《缘故》正式上线正式上线正式上线 ", itemImg->width()-6, title->font());
        title->setText(txt);
        title->setAlignment(Qt::AlignTop);

        author = new QLabel;
        author->setCursor(Qt::PointingHandCursor);
        author->setObjectName("author");
        author->setText("弦子");
        author->setFixedSize(author->sizeHint());
        author->setAlignment(Qt::AlignTop);

        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(author);
        hotItem[i]->setLayout(itemLayout);
        bannerLayout->addWidget(hotItem[i]);
        bannerLayout->setSpacing(20);
    }

    contentLayout->addWidget(arrowBox(1, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(1, "right"));

    layout->addWidget(containerBox);
    layout->addSpacing(20);
}

// 最新发行
void VideoRecom::latestIssue() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(this->width() - 20);

    containerLayout = new QVBoxLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerBox->setLayout(containerLayout);


    titleLayout = new QHBoxLayout;
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);
    titleBox = new QWidget(containerBox);
    titleBox->setLayout(titleLayout);

    titLeftLayout = new QHBoxLayout;
    titLeftLayout->setSpacing(0);
    titLeftLayout->setMargin(0);
    titLeftLayout->setAlignment(Qt::AlignLeft);

    leftTitBox = new QWidget;
    leftTitBox->setLayout(titLeftLayout);

    title = new QLabel;
    title->setObjectName("title");
    title->setText("最新发行");
    titLeftLayout->addWidget(title);
    titLeftLayout->addSpacing(10);

    latestNavLayout = new QHBoxLayout;
    latestNavLayout->setSpacing(0);
    latestNavLayout->setMargin(0);

    latestNavBox = new QWidget;
    titLeftLayout->addWidget(latestNavBox);
    QStringList nav = {"最新", "内地", "港台", "欧美", "韩国", "日本"};
    for (int i = 0; i < nav.size(); ++i) {
        latestNavItem[i] = new QLabel;
        latestNavItem[i]->setCursor(Qt::PointingHandCursor);
        latestNavItem[i]->setObjectName("latestNavItem");
        latestNavItem[i]->setText(nav[i]);
        latestNavLayout->addWidget(latestNavItem[i]);
        latestNavLayout->addSpacing(30);
        latestNavBox->setLayout(latestNavLayout);
    }
    titLeftLayout->addWidget(latestNavBox);

    moreRightLayout = new QHBoxLayout;
    moreRightLayout->setSpacing(0);
    moreRightLayout->setMargin(0);
    moreRightLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    rightMoreBox = new QLabel;
    rightMoreBox->setFixedWidth(45);
    rightMoreBox->setObjectName("rightMoreBox");
    rightMoreBox->setCursor(Qt::PointingHandCursor);
    rightMoreBox->setLayout(moreRightLayout);

    moreTitle = new QLabel;
    moreTitle->setObjectName("moreTit");
    moreTitle->setText("更多");
    moreRightLayout->addWidget(moreTitle);
    moreRightLayout->addSpacing(5);

    arrowTitle = new QLabel;
    arrowTitle->setObjectName("arrowMore");
    arrowTitle->setFont(tools->aliIcon());
    arrowTitle->setText(QChar(0xe601));
    arrowTitle->setFixedSize(14, 22);
    moreRightLayout->addWidget(arrowTitle);


    titleLayout->addWidget(leftTitBox);
    titleLayout->addWidget(rightMoreBox);
    titleLayout->addSpacing(20);
    containerLayout->addWidget(titleBox);

    contentBox = new QWidget(containerBox);
    contentBox->setFixedSize(containerBox->width(), 230);
    contentBox->installEventFilter(this);
    contentBox->setObjectName("latestBox");

    containerLayout->addSpacing(6);
    containerLayout->addWidget(contentBox);

    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    contentBox->setLayout(contentLayout);

    bannerBox = new QWidget(contentBox);
    bannerBox->setFixedSize(contentBox->width() - 60, contentBox->height());
    bannerBox->setObjectName("bannerBox");

    bannerLayout = new QHBoxLayout;
    bannerLayout->setSpacing(0);
    bannerLayout->setMargin(0);
    bannerLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[3] = new QWidget(bannerBox);
    wrapconBox[3]->setLayout(bannerLayout);
    animation[3] = new QPropertyAnimation(wrapconBox[3], "geometry");
    animation[3]->setDuration(300);


    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QfX3MU2dzluKMUOBEjz0h6g/300"
            << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QY8gA4UrJxhxQ9BBHZHDyFQ/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqojSibubibse2uIWSaZhZ39n1F1CQCXVuMGdw/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqoglWn5x5ITgE8KljTdMrDCyBpia0Jkn6BDg/300?n=1"
            << "https://qpic.y.qq.com/music_cover/I2ZdwiaF8XY3CVB1y18cmH6dVjiaC6hprhowF1emvMrTFIxCibB04GH5A/300?n=1"
            << "https://qpic.y.qq.com/music_cover/4pmnRu5sL5QbtO8OS8NKJTN5qBpjx5XMS8vhm4hcZSN7PEHPQ68C0Q/300?n=1";
    for (int i = 0; i < imgList.size(); ++i) {
        latestItem[i] = new QWidget(contentBox);
        latestItem[i]->setFixedWidth(170);
        latestItem[i]->setObjectName("latestItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(latestItem[i]);
        itemImg->setFixedSize(170, 170);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("latestImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 12));

        maskBox = new QWidget(itemImg);
        maskBox->setFixedSize(itemImg->width(), itemImg->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(itemImg);
        playBox->setObjectName("playBox");
        playBox->setVisible(false);
        playBox->setFixedSize(40, 30);
        QPixmap playPix(":/resource/images/play.png");
        playBox->setPixmap(playPix);
        playBox->setScaledContents(true);
        playBox->move(10, itemImg->height() - 40);

        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        QString titleTxt = tools->textElps("华语摇滚|川流不息", itemImg->width()-20, title->font());
        title->setText(titleTxt);

        exTitle = new QLabel;
        exTitle->setObjectName("exTitle");
        QString txt = tools->textElps("GAT周延/威尔Will.T", itemImg->width()-20, exTitle->font());
        exTitle->setText(txt);

        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(exTitle);
        latestItem[i]->setLayout(itemLayout);
        bannerLayout->addWidget(latestItem[i]);
        bannerLayout->setSpacing(20);
    }

    contentLayout->addWidget(arrowBox(3, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(3, "right"));

    layout->addWidget(containerBox);
    layout->addSpacing(30);
}

// 分类专区
void VideoRecom::classPrefe() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(this->width() - 20);
    containerLayout = new QVBoxLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerBox->setLayout(containerLayout);


    titleLayout = new QHBoxLayout;
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);
    titleBox = new QWidget(containerBox);
    titleBox->setLayout(titleLayout);

    title = new QLabel;
    title->setObjectName("title");
    title->setText("分类专区");
    titleLayout->addWidget(title);
    containerLayout->addWidget(titleBox);

    contentBox = new QWidget(containerBox);
    contentBox->setFixedSize(containerBox->width(), 230);
    contentBox->installEventFilter(this);
    contentBox->setObjectName("classPrefeBox");
    containerLayout->addSpacing(6);
    containerLayout->addWidget(contentBox);

    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    contentBox->setLayout(contentLayout);

    bannerBox = new QWidget(contentBox);
    bannerBox->setFixedSize(contentBox->width() - 60, contentBox->height());
    bannerBox->setObjectName("bannerBox");

    bannerLayout = new QHBoxLayout;
    bannerLayout->setSpacing(0);
    bannerLayout->setMargin(0);
    bannerLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[4] = new QWidget(bannerBox);
    wrapconBox[4]->setLayout(bannerLayout);
    animation[4] = new QPropertyAnimation(wrapconBox[4], "geometry");
    animation[4]->setDuration(300);


    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://y.gtimg.cn/music/common/upload/category_area/4522613.jpg"
            << "https://y.gtimg.cn/music/common/upload/category_area/4370381.png"
            << "https://y.gtimg.cn/music/common/upload/category_area/4522642.jpg"
            << "https://y.gtimg.cn/music/common/upload/category_area/4104860.jpg"
            << "https://y.gtimg.cn/music/common/upload/category_area/4427772.jpg"
            // << "https://y.gtimg.cn/music/common/upload/category_area/2447186.jpg"
            // << "https://y.gtimg.cn/music/common/upload/category_area/1348191.jpg"
            << "https://y.gtimg.cn/music/common/upload/category_area/4461729.png";
    for (int i = 0; i < imgList.size(); ++i) {
        classItem[i] = new QWidget(contentBox);
        classItem[i]->setFixedWidth(170);
        classItem[i]->setObjectName("classPrefeItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(classItem[i]);
        itemImg->setFixedSize(170, 170);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("classPrefeImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 12));

        maskBox = new QWidget(itemImg);
        maskBox->setFixedSize(itemImg->width(), itemImg->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);


        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        title->setText("杜比全景声");

        exTitle = new QLabel;
        exTitle->setObjectName("exTitle");
        QString txt = tools->textElps("高解析度音乐，如临现场，栩栩如生", itemImg->width()-20, exTitle->font());
        exTitle->setText(txt);

        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(exTitle);
        classItem[i]->setLayout(itemLayout);
        bannerLayout->addWidget(classItem[i]);
        bannerLayout->setSpacing(20);
    }

    contentLayout->addWidget(arrowBox(4, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(4, "right"));

    layout->addWidget(containerBox);
}

QPixmap *VideoRecom::getImage(QString url) {
    manager = new QNetworkAccessManager;
    reply = manager->get(QNetworkRequest(QUrl(url)));
    loop = new QEventLoop();
    connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
    loop->exec();
    QByteArray imgData = reply->readAll();
    coverImg = new QPixmap;
    coverImg->loadFromData(imgData);
    return coverImg;
}

// 左右箭头部件
QLabel *VideoRecom::arrowBox(int i, QString type) {
    if (type == "left") {
        QLabel *leftArrow = new QLabel;
        leftArrow->setObjectName("leftArrow" + QString::number(i));
        leftArrow->setProperty("class", "leftArrow");
        leftArrow->installEventFilter(this);
        leftArrow->setFixedSize(30, 38);
        leftArrow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        leftArrow->setCursor(Qt::PointingHandCursor);
        leftArrow->setFont(tools->aliIcon());
        leftArrow->setText(QChar(0xea84));
        leftArrow->setVisible(false);
        QSizePolicy policy_lf = leftArrow->sizePolicy();
        policy_lf.setRetainSizeWhenHidden(true);
        leftArrow->setSizePolicy(policy_lf);
        return leftArrow;
    }
    if (type == "right") {
        QLabel *rightArrow = new QLabel;
        rightArrow->setObjectName("rightArrow" + QString::number(i));
        rightArrow->setProperty("class", "rightArrow");
        rightArrow->installEventFilter(this);
        rightArrow->setFixedSize(30, 38);
        rightArrow->setCursor(Qt::PointingHandCursor);
        rightArrow->setFont(tools->aliIcon());
        rightArrow->setText(QChar(0xe63e));
        rightArrow->setVisible(false);
        QSizePolicy policy = rightArrow->sizePolicy();
        policy.setRetainSizeWhenHidden(true);
        rightArrow->setSizePolicy(policy);
        return rightArrow;
    }
}

// 左右箭头切换隐藏
void VideoRecom::showArrow(QObject *o, QEvent *e, int i) {
    QLabel *leftArrow = o->findChild<QLabel *>("leftArrow" + QString::number(i));
    QLabel *rightArrow = o->findChild<QLabel *>("rightArrow" + QString::number(i));
    if (e->type() == QEvent::Enter) {
        if (leftArrow != NULL && rightArrow != NULL) {
            leftArrow->setVisible(true);
            rightArrow->setVisible(true);
        }
    }
    if (e->type() == QEvent::Leave) {
        if (leftArrow != NULL && rightArrow != NULL) {
            leftArrow->setVisible(false);
            rightArrow->setVisible(false);
        }
    }
}

// 轮播图切换
void VideoRecom::toggleItem(QWidget *itemBox, QString objName, QEvent *e) {
    QLabel *box = itemBox->findChild<QLabel *>(objName);
    QWidget *mask = itemBox->findChild<QWidget *>("maskBox");
    QLabel *play_box = itemBox->findChild<QLabel *>("playBox");
    QWidget *play_count = itemBox->findChild<QWidget *>("playCountBox");


    QPropertyAnimation *animation = new QPropertyAnimation(box, "geometry");
    animation->setDuration(150);

    if (e->type() == QEvent::Enter) {
        animation->setStartValue(QRect(0, 10, box->width(), box->height()));
        animation->setEndValue(QRect(0, 0, box->width(), box->height()));
        animation->start();
        if (play_box) {
            play_box->setVisible(true);
        }
        if (mask) {
            mask->setVisible(true);
        }
        if (play_count) {
            play_count->setVisible(false);
        }
    }
    if (e->type() == QEvent::Leave) {
        animation->setStartValue(QRect(0, 0, box->width(), box->height()));
        animation->setEndValue(QRect(0, 10, box->width(), box->height()));
        animation->start();
        if (play_box) {
            play_box->setVisible(false);
        }
        if (mask) {
            mask->setVisible(false);
        }
        if (play_count) {
            play_count->setVisible(true);
        }
    }
}


bool VideoRecom::eventFilter(QObject *o, QEvent *e) {
    // 左右箭头交互
    if (o->objectName() == "selectedBox") {
        showArrow(o, e, 0);
    }
    if (o->objectName() == "newestBox") {
        showArrow(o, e, 1);
    }
    if (o->objectName() == "hotBox") {
        showArrow(o, e, 2);
    }
    if (o->objectName() == "latestBox") {
        showArrow(o, e, 3);
    }
    if (o->objectName() == "classPrefeBox") {
        showArrow(o, e, 4);
    }
    if (o->objectName() == "newestImg") {
        int i = o->property("index").toInt();
        toggleItem(newestItem[i], "newestImg", e);
    }
    if (o->objectName() == "hotImg") {
        int i = o->property("index").toInt();
        toggleItem(hotItem[i], "hotImg", e);
    }

    if (o->objectName() == "latestImg") {
        int i = o->property("index").toInt();
        toggleItem(latestItem[i], "latestImg", e);
    }
    if (o->objectName() == "classPrefeImg") {
        int i = o->property("index").toInt();
        toggleItem(classItem[i], "classPrefeImg", e);
    }

    return QWidget::eventFilter(o, e);

}

void VideoRecom::loadQSS() {
    QFile qss(":/resource/qss/videoRecom.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}