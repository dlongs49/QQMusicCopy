//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"

Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();


    this->setFixedSize(820, 2000);
    widget = new QWidget(this);
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignRight);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, 820, 500);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);
    handleMenu = new HandleMenu(scrollArea);


    RecommTop();
    RecommTrea();
    RecommListen();
    RecommRoam();
    RecommHeartbeat();
    RecommProgram();
    widget->setLayout(layout);


}

void Recommend::RecommTop() {
    recomOutBox = new QWidget(widget);
    recomOutBox->setFixedWidth(810);
    recomOutBox->setFixedHeight(246);
    recomOutLayout = new QVBoxLayout;
    recomOutLayout->setSpacing(0);
    recomOutLayout->setMargin(0);
    recomOutBox->setLayout(recomOutLayout);
    title = new QLabel;
    title->setObjectName("title");
    title->setText("嘿，冰消叶散，今日为你推荐");
    recomOutLayout->addWidget(title);


    recomBox = new QWidget(recomOutBox);
    recomBox->setFixedSize(recomOutBox->width(), 218);
    recomBox->installEventFilter(this);
    recomBox->setObjectName("recomBox");
    recomOutLayout->addSpacing(6);
    recomOutLayout->addWidget(recomBox);

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setFixedSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    recomConLayout = new QHBoxLayout;
    recomConLayout->setSpacing(0);
    recomConLayout->setMargin(0);
    recomConLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[0] = new QWidget(recomScrollBox);
    wrapconBox[0]->setLayout(recomConLayout);
    animation[0] = new QPropertyAnimation(wrapconBox[0], "geometry");
    animation[0]->setDuration(300);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "http://y.qq.com/n3/wk_v20/entry/bg6.dab9cba46.png?max_age=2592000"
            << "https://y.gtimg.cn/music/photo_new/T002R300x300M000003MvqCa0Fq3Mq_2.jpg"
            << "http://y.qq.com/music/photo_new/T002R300x300M000000J15TK3Afzlb_5.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M0000008mjyX38ncsg_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000003ldyaV1pgN3M_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000000cpBaV2uDCBC_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000003yGUXR2isN9F_2.jpg?max_age=2592000";
    for (int i = 0; i < imgList.size(); ++i) {
        recomItemBox[i] = new QWidget(recomBox);
        if (i == 0) {
            recomItemBox[0]->setFixedWidth(356);
        } else {
            recomItemBox[i]->setFixedWidth(160);
        }
        recomItemLayout = new QVBoxLayout;
        recomItemLayout->setSpacing(0);
        recomItemLayout->setMargin(0);
        recomItemLayout->setAlignment(Qt::AlignTop);

        recomImgBox = new QLabel(recomItemBox[i]);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("recomImgBox");
        recomImgBox->setProperty("index", i);
        recomImgBox->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 6));
        if (i == 0) {
            recomImgBox->setFixedSize(406, 160);

            guessLayout = new QVBoxLayout;
            guessLayout->setAlignment(Qt::AlignVCenter);
            guessTit = new QLabel;
            guessTit->setStyleSheet("font-size:20px");
            guessTit->setText("晚上好");
            guessSubTit = new QLabel;
            guessSubTit->setText("尝试来点音\n乐提提神吧");
            playBox = new QLabel;
            playBox->setFixedSize(40, 30);
            QPixmap playPix(":/resource/images/play.png");
            playBox->setPixmap(playPix);
            playBox->setScaledContents(true);
            guessLayout->addWidget(guessTit);
            guessLayout->addWidget(guessSubTit);
            guessLayout->addSpacing(5);
            guessLayout->addWidget(playBox);
            recomImgBox->setLayout(guessLayout);
        } else {
            recomImgBox->setFixedSize(160, 160);

            maskBox = new QWidget(recomImgBox);
            maskBox->setFixedSize(recomImgBox->width(), recomImgBox->height());
            maskBox->setObjectName("maskBox");
            maskBox->setVisible(false);

            playBox = new QLabel(recomImgBox);
            playBox->setObjectName("playBox");
            playBox->setVisible(false);
            playBox->setFixedSize(40, 30);
            QPixmap playPix(":/resource/images/play.png");
            playBox->setPixmap(playPix);
            playBox->setScaledContents(true);
            playBox->move(10, recomImgBox->height() - 40);
        }

        recomTit = new QLabel;
        recomTit->setCursor(Qt::PointingHandCursor);
        recomTit->setObjectName("recomTit");
        recomTit->setText("一生无悔-高安/杭娇");
        recomTit->setFixedSize(recomTit->sizeHint().width(), recomTit->sizeHint().height());
        recomSubTit = new QLabel;
        recomSubTit->setCursor(Qt::PointingHandCursor);
        recomSubTit->setObjectName("recomTit");
        recomSubTit->setText("每日三十首");
        recomSubTit->setFixedSize(recomSubTit->sizeHint().width(), recomSubTit->sizeHint().height());


        recomItemLayout->addSpacing(10);
        recomItemLayout->addWidget(recomImgBox);
        recomItemLayout->addSpacing(6);
        recomItemLayout->addWidget(recomTit);
        recomItemLayout->addSpacing(3);
        recomItemLayout->addWidget(recomSubTit);
        recomItemBox[i]->setLayout(recomItemLayout);
        recomConLayout->addWidget(recomItemBox[i]);
        if (i != imgList.size() - 1) {
            recomConLayout->addSpacing(20);
        }
    }

    recomLayout->addWidget(arrowBox(0, "left"));
    recomLayout->addWidget(recomScrollBox);
    recomLayout->addWidget(arrowBox(0, "right"));

    layout->addWidget(recomOutBox);
    layout->addSpacing(30);
}

void Recommend::RecommTrea() {
    recomOutBox = new QWidget(widget);
    recomOutBox->setFixedWidth(810);
    recomOutLayout = new QVBoxLayout;
    recomOutLayout->setSpacing(0);
    recomOutLayout->setMargin(0);
    recomOutBox->setLayout(recomOutLayout);
    title = new QLabel;
    title->setObjectName("title");
    title->setText("你的歌单宝藏库");
    recomOutLayout->addWidget(title);

    recomBox = new QWidget(recomOutBox);
    recomBox->setFixedSize(recomOutBox->width(), 460);
    recomBox->installEventFilter(this);
    recomBox->setObjectName("treaBox");
    recomOutLayout->addSpacing(6);
    recomOutLayout->addWidget(recomBox);

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setFixedSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    treaLayout = new QGridLayout;
    treaLayout->setSpacing(0);
    treaLayout->setMargin(0);
    treaLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[1] = new QWidget(recomScrollBox);
    wrapconBox[1]->setLayout(treaLayout);
    animation[1] = new QPropertyAnimation(wrapconBox[1], "geometry");
    animation[1]->setDuration(300);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004IQrYm2aq13C_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002RFvQa0KZgWT_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000001xEQO00PY9o4_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000003ytZCh3LYLkh_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000001rM9vP1z3OJl_1.jpg?max_age=2592000"
            << "http://y.gtimg.cn/music/photo_new/T002R500x500M000002KhpvO2onL52_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002jL3lo4QydNE_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002iWYEP1NsXim_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004SVT961IWY2U_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000000Cynhk1pfdmC_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004SMH8t4336xW_1.jpg?max_age=25920000";
    for (int i = 0; i < imgList.size(); ++i) {
        treaItemBox[i] = new QWidget(recomBox);
        treaItemBox[i]->setFixedWidth(160);
        recomItemLayout = new QVBoxLayout;
        recomItemLayout->setSpacing(0);
        recomItemLayout->setMargin(0);
        recomItemLayout->setAlignment(Qt::AlignTop);

        recomImgBox = new QLabel(treaItemBox[i]);
        recomImgBox->setFixedSize(160, 160);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("treaImgBox");
        recomImgBox->setProperty("index", i);
        recomImgBox->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 6));

        maskBox = new QWidget(recomImgBox);
        maskBox->setFixedSize(recomImgBox->width(), recomImgBox->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(recomImgBox);
        playBox->setObjectName("playBox");
        playBox->setVisible(false);
        playBox->setFixedSize(40, 30);
        QPixmap playPix(":/resource/images/play.png");
        playBox->setPixmap(playPix);
        playBox->setScaledContents(true);
        playBox->move(10, recomImgBox->height() - 40);

        playCount = new QLabel(recomImgBox);
        playCount->setFixedWidth(recomImgBox->width() - 10);
        playCount->setText("5580亿");
        playCount->setAlignment(Qt::AlignRight);
        playCount->setObjectName("playCount");
        playCount->move(0, recomImgBox->height() - 25);

        recomTit = new QLabel;
        recomTit->setCursor(Qt::PointingHandCursor);
        recomTit->setObjectName("recomTit");
        recomTit->setText("抖音最火BGM，根本停不下来");
        recomTit->setWordWrap(true);
        recomTit->setAlignment(Qt::AlignTop);
        recomTit->setFixedHeight(38);


        recomItemLayout->addSpacing(10);
        recomItemLayout->addWidget(recomImgBox);
        recomItemLayout->addSpacing(6);
        recomItemLayout->addWidget(recomTit);
        treaItemBox[i]->setLayout(recomItemLayout);
        int r = floor(i / 6) + 1;
        int c = (i % 6) + 1;
        treaLayout->addWidget(treaItemBox[i], r, c);
        treaLayout->setSpacing(25);
    }

    recomLayout->addWidget(arrowBox(1, "left"));
    recomLayout->addWidget(recomScrollBox);
    recomLayout->addWidget(arrowBox(1, "right"));

    layout->addWidget(recomOutBox);
    layout->addSpacing(30);
}

void Recommend::RecommListen() {
    recomOutBox = new QWidget(widget);
    recomOutBox->setFixedWidth(810);
    recomOutLayout = new QVBoxLayout;
    recomOutLayout->setSpacing(0);
    recomOutLayout->setMargin(0);
    recomOutBox->setLayout(recomOutLayout);

    titLayout = new QHBoxLayout;
    titLayout->setSpacing(0);
    titLayout->setMargin(0);
    titLayout->setAlignment(Qt::AlignLeft);
    titleBox = new QWidget(recomOutBox);
    titleBox->setLayout(titLayout);
    title = new QLabel;
    title->setObjectName("title");
    title->setText("大家都在听");
    titLayout->addWidget(title);
    titLayout->addSpacing(10);

    QLabel *titPlay = new QLabel(titleBox);
    titPlay->setCursor(Qt::PointingHandCursor);
    titPlay->setObjectName("tit_playBox");
    titPlay->setFixedSize(40, 30);
    titPlay->setFont(tools->aliIcon());
    titPlay->setText(QChar(0xea83));
    titPlay->setAlignment(Qt::AlignCenter);
    titLayout->addWidget(titPlay);
    recomOutLayout->addWidget(titleBox);


    recomBox = new QWidget(recomOutBox);
    recomBox->setFixedSize(recomOutBox->width(), 200);
    recomBox->installEventFilter(this);
    recomBox->setObjectName("listenBox");
    recomOutLayout->addSpacing(15);
    recomOutLayout->addWidget(recomBox);

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setMinimumSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    gridLayout = new QGridLayout;
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);
    gridLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[2] = new QWidget(recomScrollBox);
    wrapconBox[2]->setLayout(gridLayout);
    animation[2] = new QPropertyAnimation(wrapconBox[2], "geometry");
    animation[2]->setDuration(300);
    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000";
    for (int i = 0; i < imgList.size(); ++i) {
        everyItemBox[i] = new QWidget(recomBox);
        everyItemBox[i]->installEventFilter(this);
        everyItemBox[i]->setFixedSize(240, 66);
        everyItemBox[i]->setObjectName("everyItemBox");
        everyItemBox[i]->setProperty("index", i);
        listenLayout = new QHBoxLayout;
        listenLayout->setSpacing(0);
        listenLayout->setMargin(0);
        listenLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

        recomImgBox = new QLabel(everyItemBox[i]);
        recomImgBox->setFixedSize(50, 50);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("everyImgBox");
        // 先提取网络图片 再处理圆角 Tools
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 6));

        maskBox = new QWidget(recomImgBox);
        maskBox->setFixedSize(recomImgBox->width(), recomImgBox->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(recomImgBox);
        playBox->setObjectName("listenPlay");
        playBox->setVisible(false);
        playBox->setFont(tools->aliIcon());
        playBox->setText(QChar(0xea83));
        playBox->move(17, 17);

        rightLayout = new QVBoxLayout;
        rightLayout->setMargin(0);
        rightLayout->setSpacing(0);
        rightBox = new QWidget(everyItemBox[i]);
        rightBox->setFixedSize(everyItemBox[i]->width() - 76, recomImgBox->height());
        rightBox->setLayout(rightLayout);

        songsLayout = new QHBoxLayout;
        songsLayout->setMargin(0);
        songsLayout->setSpacing(0);
        songsLayout->setAlignment(Qt::AlignVCenter);
        songsLabel = new QLabel;
        songsLabel->setLayout(songsLayout);
        rightLayout->addWidget(songsLabel);

        recomTit = new QLabel;
        recomTit->setObjectName("songsTit");
        QString recomTxt = tools->textElps("五彩湖泊五彩湖泊五彩湖泊五彩湖泊", 110, recomTit->font());
        recomTit->setText(recomTxt);
        recomTit->setFixedSize(recomTit->sizeHint().width(), recomTit->sizeHint().height());
        songsLayout->addWidget(recomTit);

        idenLabel = new QLabel;
        idenLabel->setObjectName("idenLabel");
        idenLabel->setFixedSize(34, 14);
        QPixmap idenPix(":/resource/images/sound.png");
        idenLabel->setPixmap(idenPix);
        idenLabel->setScaledContents(true);
        songsLayout->addSpacing(5);
        songsLayout->addWidget(idenLabel);

        authorLabel = new QLabel;
        authorLabel->setCursor(Qt::PointingHandCursor);
        authorLabel->setObjectName("authorTit");
        authorLabel->setText("衫和" + QString::number(i));
        rightLayout->addWidget(authorLabel);

        floatLayout = new QHBoxLayout;
        floatLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        floatBox = new QWidget(rightBox);
        floatBox->setObjectName("floatBox");
        floatBox->setVisible(false);
        floatBox->setFixedHeight(rightBox->height());
        floatBox->move(rightBox->width() - 100, 0);
        floatBox->setLayout(floatLayout);

        loveBox = new QLabel;
        loveBox->setCursor(Qt::PointingHandCursor);
        loveBox->setObjectName("loveBox");
        loveBox->setFont(tools->aliIcon());
        loveBox->setText(QChar(0xe86f));
        floatLayout->addWidget(loveBox);
        floatLayout->addSpacing(10);

        moreBox = new QLabel;
        moreBox->setCursor(Qt::PointingHandCursor);
        moreBox->setObjectName("moreBox");
        moreBox->setFont(tools->aliIcon());
        moreBox->setText(QChar(0xe60f));
        floatLayout->addWidget(moreBox);
        floatLayout->addWidget(moreBox);


        listenLayout->addSpacing(8);
        listenLayout->addWidget(recomImgBox);
        listenLayout->addSpacing(10);
        listenLayout->addWidget(rightBox);
        everyItemBox[i]->setLayout(listenLayout);
        int r = floor(i / 6) + 1;
        int c = (i % 6) + 1;
        gridLayout->addWidget(everyItemBox[i], r, c);
        gridLayout->setHorizontalSpacing(10);
    }

    recomLayout->addWidget(arrowBox(2, "left"));
    recomLayout->addWidget(recomScrollBox);
    recomLayout->addWidget(arrowBox(2, "right"));

    layout->addWidget(recomOutBox);
    layout->addSpacing(30);
}

void Recommend::RecommRoam() {
    recomOutBox = new QWidget(widget);
    recomOutBox->setFixedWidth(810);
    recomOutLayout = new QVBoxLayout;
    recomOutLayout->setSpacing(0);
    recomOutLayout->setMargin(0);
    recomOutBox->setLayout(recomOutLayout);
    title = new QLabel;
    title->setObjectName("title");
    title->setText("歌单遨游指南");
    recomOutLayout->addWidget(title);

    recomBox = new QWidget(recomOutBox);
    recomBox->setFixedSize(recomOutBox->width(), 220);
    recomBox->installEventFilter(this);
    recomBox->setObjectName("roamBox");
    recomOutLayout->addSpacing(6);
    recomOutLayout->addWidget(recomBox);

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setFixedSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    recomConLayout = new QHBoxLayout;
    recomConLayout->setSpacing(0);
    recomConLayout->setMargin(0);
    recomConLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[3] = new QWidget(recomScrollBox);
    wrapconBox[3]->setLayout(recomConLayout);
    animation[3] = new QPropertyAnimation(wrapconBox[3], "geometry");
    animation[3]->setDuration(300);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004IQrYm2aq13C_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002RFvQa0KZgWT_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000001xEQO00PY9o4_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000003ytZCh3LYLkh_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000001rM9vP1z3OJl_1.jpg?max_age=2592000"
            << "http://y.gtimg.cn/music/photo_new/T002R500x500M000002KhpvO2onL52_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002jL3lo4QydNE_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002iWYEP1NsXim_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004SVT961IWY2U_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000000Cynhk1pfdmC_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004SMH8t4336xW_1.jpg?max_age=25920000";
    for (int i = 0; i < imgList.size(); ++i) {
        roamItemBox[i] = new QWidget(recomBox);
        roamItemBox[i]->setFixedWidth(160);
        roamItemBox[i]->setObjectName("roamItemBox");
        recomItemLayout = new QVBoxLayout;
        recomItemLayout->setSpacing(0);
        recomItemLayout->setMargin(0);
        recomItemLayout->setAlignment(Qt::AlignTop);

        recomImgBox = new QLabel(roamItemBox[i]);
        recomImgBox->setFixedSize(160, 160);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("roamImgBox");
        recomImgBox->setProperty("index", i);
        recomImgBox->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 6));

        maskBox = new QWidget(recomImgBox);
        maskBox->setFixedSize(recomImgBox->width(), recomImgBox->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(recomImgBox);
        playBox->setObjectName("playBox");
        playBox->setVisible(false);
        playBox->setFixedSize(40, 30);
        QPixmap playPix(":/resource/images/play.png");
        playBox->setPixmap(playPix);
        playBox->setScaledContents(true);
        playBox->move(10, recomImgBox->height() - 40);

        playCount = new QLabel(recomImgBox);
        playCount->setFixedWidth(recomImgBox->width() - 10);
        playCount->setText("5580亿");
        playCount->setAlignment(Qt::AlignRight);
        playCount->setObjectName("playCount");
        playCount->move(0, recomImgBox->height() - 25);

        recomTit = new QLabel;
        recomTit->setCursor(Qt::PointingHandCursor);
        recomTit->setObjectName("recomTit");
        recomTit->setText("抖音最火BGM，根本停不下来");
        recomTit->setWordWrap(true);
        recomTit->setAlignment(Qt::AlignTop);
        recomTit->setFixedHeight(38);


        recomItemLayout->addSpacing(10);
        recomItemLayout->addWidget(recomImgBox);
        recomItemLayout->addSpacing(6);
        recomItemLayout->addWidget(recomTit);
        roamItemBox[i]->setLayout(recomItemLayout);
        recomConLayout->addWidget(roamItemBox[i]);
        recomConLayout->setSpacing(25);
    }

    recomLayout->addWidget(arrowBox(3, "left"));
    recomLayout->addWidget(recomScrollBox);
    recomLayout->addWidget(arrowBox(3, "right"));

    layout->addWidget(recomOutBox);
    layout->addSpacing(30);
}

void Recommend::RecommHeartbeat() {
    recomOutBox = new QWidget(widget);
    recomOutBox->setFixedWidth(810);
    recomOutLayout = new QVBoxLayout;
    recomOutLayout->setSpacing(0);
    recomOutLayout->setMargin(0);
    recomOutBox->setLayout(recomOutLayout);

    titLayout = new QHBoxLayout;
    titLayout->setSpacing(0);
    titLayout->setMargin(0);
    titLayout->setAlignment(Qt::AlignLeft);
    titleBox = new QWidget(recomOutBox);
    titleBox->setLayout(titLayout);
    title = new QLabel;
    title->setObjectName("title");
    title->setText("心动的歌曲推荐");
    titLayout->addWidget(title);
    titLayout->addSpacing(10);

    QLabel *titPlay = new QLabel(titleBox);
    titPlay->setCursor(Qt::PointingHandCursor);
    titPlay->setObjectName("tit_playBox");
    titPlay->setFixedSize(40, 30);
    titPlay->setFont(tools->aliIcon());
    titPlay->setText(QChar(0xea83));
    titPlay->setAlignment(Qt::AlignCenter);
    titLayout->addWidget(titPlay);
    recomOutLayout->addWidget(titleBox);


    recomBox = new QWidget(recomOutBox);
    recomBox->setFixedSize(recomOutBox->width(), 200);
    recomBox->installEventFilter(this);
    recomBox->setObjectName("heartBox");
    recomOutLayout->addSpacing(15);
    recomOutLayout->addWidget(recomBox);

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setMinimumSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    gridLayout = new QGridLayout;
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);
    gridLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[4] = new QWidget(recomScrollBox);
    wrapconBox[4]->setLayout(gridLayout);
    animation[4] = new QPropertyAnimation(wrapconBox[4], "geometry");
    animation[4]->setDuration(300);
    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000";
    for (int i = 0; i < imgList.size(); ++i) {
        heartItemBox[i] = new QWidget(recomBox);
        heartItemBox[i]->installEventFilter(this);
        heartItemBox[i]->setFixedSize(240, 66);
        heartItemBox[i]->setObjectName("heartItemBox");
        heartItemBox[i]->setProperty("index", i);
        listenLayout = new QHBoxLayout;
        listenLayout->setSpacing(0);
        listenLayout->setMargin(0);
        listenLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

        recomImgBox = new QLabel(heartItemBox[i]);
        recomImgBox->setFixedSize(50, 50);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("heartImgBox");
        // 先提取网络图片 再处理圆角 Tools
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 6));

        maskBox = new QWidget(recomImgBox);
        maskBox->setFixedSize(recomImgBox->width(), recomImgBox->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(recomImgBox);
        playBox->setObjectName("listenPlay");
        playBox->setVisible(false);
        playBox->setFont(tools->aliIcon());
        playBox->setText(QChar(0xea83));
        playBox->move(17, 17);

        rightLayout = new QVBoxLayout;
        rightLayout->setMargin(0);
        rightLayout->setSpacing(0);
        rightBox = new QWidget(heartItemBox[i]);
        rightBox->setFixedSize(heartItemBox[i]->width() - 76, recomImgBox->height());
        rightBox->setLayout(rightLayout);

        songsLayout = new QHBoxLayout;
        songsLayout->setMargin(0);
        songsLayout->setSpacing(0);
        songsLayout->setAlignment(Qt::AlignVCenter);
        songsLabel = new QLabel;
        songsLabel->setLayout(songsLayout);
        rightLayout->addWidget(songsLabel);

        recomTit = new QLabel;
        recomTit->setObjectName("songsTit");
        QString recomTxt = tools->textElps("五彩湖泊五彩湖泊五彩湖泊五彩湖泊", 110, recomTit->font());
        recomTit->setText(recomTxt);
        recomTit->setFixedSize(recomTit->sizeHint().width(), recomTit->sizeHint().height());
        songsLayout->addWidget(recomTit);

        idenLabel = new QLabel;
        idenLabel->setObjectName("idenLabel");
        idenLabel->setFixedSize(34, 14);
        QPixmap idenPix(":/resource/images/sound.png");
        idenLabel->setPixmap(idenPix);
        idenLabel->setScaledContents(true);
        songsLayout->addSpacing(5);
        songsLayout->addWidget(idenLabel);

        authorLabel = new QLabel;
        authorLabel->setCursor(Qt::PointingHandCursor);
        authorLabel->setObjectName("authorTit");
        authorLabel->setText("衫和" + QString::number(i));
        rightLayout->addWidget(authorLabel);

        floatLayout = new QHBoxLayout;
        floatLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        floatBox = new QWidget(rightBox);
        floatBox->setObjectName("floatBox");
        floatBox->setVisible(false);
        floatBox->setFixedHeight(rightBox->height());
        floatBox->move(rightBox->width() - 100, 0);
        floatBox->setLayout(floatLayout);

        loveBox = new QLabel;
        loveBox->setCursor(Qt::PointingHandCursor);
        loveBox->setObjectName("loveBox");
        loveBox->setFont(tools->aliIcon());
        loveBox->setText(QChar(0xe86f));
        floatLayout->addWidget(loveBox);
        floatLayout->addSpacing(10);

        moreBox = new QLabel;
        moreBox->setCursor(Qt::PointingHandCursor);
        moreBox->setObjectName("moreBox");
        moreBox->setFont(tools->aliIcon());
        moreBox->setText(QChar(0xe60f));
        floatLayout->addWidget(moreBox);
        floatLayout->addWidget(moreBox);


        listenLayout->addSpacing(8);
        listenLayout->addWidget(recomImgBox);
        listenLayout->addSpacing(10);
        listenLayout->addWidget(rightBox);
        heartItemBox[i]->setLayout(listenLayout);
        int r = floor(i / 6) + 1;
        int c = (i % 6) + 1;
        gridLayout->addWidget(heartItemBox[i], r, c);
        gridLayout->setHorizontalSpacing(10);
    }

    recomLayout->addWidget(arrowBox(4, "left"));
    recomLayout->addWidget(recomScrollBox);
    recomLayout->addWidget(arrowBox(4, "right"));

    layout->addWidget(recomOutBox);
    layout->addSpacing(30);
}

void Recommend::RecommProgram() {
    recomOutBox = new QWidget(widget);
    recomOutBox->setFixedWidth(810);
    recomOutLayout = new QVBoxLayout;
    recomOutLayout->setSpacing(0);
    recomOutLayout->setMargin(0);
    recomOutBox->setLayout(recomOutLayout);
    title = new QLabel;
    title->setObjectName("title");
    title->setText("热门节目，听点不一样的");
    recomOutLayout->addWidget(title);

    recomBox = new QWidget(recomOutBox);
    recomBox->setFixedSize(recomOutBox->width(), 220);
    recomBox->installEventFilter(this);
    recomBox->setObjectName("programBox");
    recomOutLayout->addSpacing(6);
    recomOutLayout->addWidget(recomBox);

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setFixedSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    recomConLayout = new QHBoxLayout;
    recomConLayout->setSpacing(0);
    recomConLayout->setMargin(0);
    recomConLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[5] = new QWidget(recomScrollBox);
    wrapconBox[5]->setLayout(recomConLayout);
    animation[5] = new QPropertyAnimation(wrapconBox[5], "geometry");
    animation[5]->setDuration(300);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "http://y.qq.com/music/photo_new/T002R300x300M000004RlJ4h0SOy7o_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004IQrYm2aq13C_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002RFvQa0KZgWT_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000001xEQO00PY9o4_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000003ytZCh3LYLkh_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000001rM9vP1z3OJl_1.jpg?max_age=2592000"
            << "http://y.gtimg.cn/music/photo_new/T002R500x500M000002KhpvO2onL52_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002jL3lo4QydNE_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000002iWYEP1NsXim_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004SVT961IWY2U_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000000Cynhk1pfdmC_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000004SMH8t4336xW_1.jpg?max_age=25920000";
    for (int i = 0; i < imgList.size(); ++i) {
        programItemBox[i] = new QWidget(recomBox);
        programItemBox[i]->setFixedWidth(160);
        programItemBox[i]->setObjectName("programItemBox");
        recomItemLayout = new QVBoxLayout;
        recomItemLayout->setSpacing(0);
        recomItemLayout->setMargin(0);
        recomItemLayout->setAlignment(Qt::AlignTop);

        recomImgBox = new QLabel(programItemBox[i]);
        recomImgBox->setFixedSize(160, 160);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("programImgBox");
        recomImgBox->setProperty("index", i);
        recomImgBox->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 6));

        maskBox = new QWidget(recomImgBox);
        maskBox->setFixedSize(recomImgBox->width(), recomImgBox->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);

        playBox = new QLabel(recomImgBox);
        playBox->setObjectName("playBox");
        playBox->setVisible(false);
        playBox->setFixedSize(40, 30);
        QPixmap playPix(":/resource/images/play.png");
        playBox->setPixmap(playPix);
        playBox->setScaledContents(true);
        playBox->move(10, recomImgBox->height() - 40);

        playCount = new QLabel(recomImgBox);
        playCount->setFixedWidth(recomImgBox->width() - 10);
        playCount->setText("5580亿");
        playCount->setAlignment(Qt::AlignRight);
        playCount->setObjectName("playCount");
        playCount->move(0, recomImgBox->height() - 25);

        recomTit = new QLabel;
        recomTit->setCursor(Qt::PointingHandCursor);
        recomTit->setObjectName("recomTit");
        recomTit->setText("抖音最火BGM，根本停不下来");
        recomTit->setWordWrap(true);
        recomTit->setAlignment(Qt::AlignTop);
        recomTit->setFixedHeight(38);


        recomItemLayout->addSpacing(10);
        recomItemLayout->addWidget(recomImgBox);
        recomItemLayout->addSpacing(6);
        recomItemLayout->addWidget(recomTit);
        programItemBox[i]->setLayout(recomItemLayout);
        recomConLayout->addWidget(programItemBox[i]);
        recomConLayout->setSpacing(25);
    }

    recomLayout->addWidget(arrowBox(5, "left"));
    recomLayout->addWidget(recomScrollBox);
    recomLayout->addWidget(arrowBox(5, "right"));

    layout->addWidget(recomOutBox);
    layout->addSpacing(30);
}

QPixmap *Recommend::getImage(QString url) {
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
QLabel *Recommend::arrowBox(int i, QString type) {
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
void Recommend::showArrow(QObject *o, QEvent *e, int i) {
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
void Recommend::toggleItem(QWidget *itemBox, QString objName, QEvent *e) {
    QLabel *box = itemBox->findChild<QLabel *>(objName);
    QWidget *mask = itemBox->findChild<QWidget *>("maskBox");
    QLabel *play_box = itemBox->findChild<QLabel *>("playBox");
    QLabel *play_count = itemBox->findChild<QLabel *>("playCount");


    QPropertyAnimation *animation = new QPropertyAnimation(box, "geometry");
    animation->setDuration(150);

    if (e->type() == QEvent::Enter) {
        animation->setStartValue(QRect(0, 10, box->width(), box->height()));
        animation->setEndValue(QRect(0, 0, box->width(), box->height()));
        animation->start();
        if (play_box) {
            play_box->setVisible(true);
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
            mask->setVisible(false);
        }
        if (play_count) {
            play_count->setVisible(true);
        }
    }
}

bool Recommend::eventFilter(QObject *o, QEvent *e) {

    // 左右箭头交互
    if (o->objectName() == "recomBox") {
        showArrow(o, e, 0);
    }
    if (o->objectName() == "treaBox") {
        showArrow(o, e, 1);
    }
    if (o->objectName() == "listenBox") {
        showArrow(o, e, 2);
    }
    if (o->objectName() == "roamBox") {
        showArrow(o, e, 3);
    }
    if (o->objectName() == "heartBox") {
        showArrow(o, e, 4);
    }
    if (o->objectName() == "programBox") {
        showArrow(o, e, 5);
    }


    if (o->objectName() == "recomImgBox") {
        int i = o->property("index").toInt();
        toggleItem(recomItemBox[i], "recomImgBox", e);
    }

    if (o->objectName() == "treaImgBox") {
        int i = o->property("index").toInt();
        toggleItem(treaItemBox[i], "treaImgBox", e);
    }
    if (o->objectName() == "everyItemBox") {
        int i = o->property("index").toInt();
        QWidget *mask = everyItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = everyItemBox[i]->findChild<QLabel *>("listenPlay");
        QWidget *float_box = everyItemBox[i]->findChild<QWidget *>("floatBox");
        QLabel *iden_label = everyItemBox[i]->findChild<QLabel *>("idenLabel");

        if (e->type() == QEvent::Enter) {
            if (play_box) {
                play_box->setVisible(true);
                mask->setVisible(true);
                float_box->setVisible(true);
                iden_label->setVisible(false);
            }
        }
        if (e->type() == QEvent::Leave) {
            if (play_box) {
                play_box->setVisible(false);
                mask->setVisible(false);
                float_box->setVisible(false);
                iden_label->setVisible(true);
            }

        }
    }

    if (o->objectName() == "roamImgBox") {
        int i = o->property("index").toInt();
        toggleItem(roamItemBox[i], "roamImgBox", e);
    }

    if (o->objectName() == "heartItemBox") {
        int i = o->property("index").toInt();
        QWidget *mask = heartItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = heartItemBox[i]->findChild<QLabel *>("listenPlay");
        QWidget *float_box = heartItemBox[i]->findChild<QWidget *>("floatBox");
        QLabel *iden_label = heartItemBox[i]->findChild<QLabel *>("idenLabel");

        if (e->type() == QEvent::Enter) {
            if (play_box) {
                play_box->setVisible(true);
                mask->setVisible(true);
                float_box->setVisible(true);
                iden_label->setVisible(false);
            }
        }
        if (e->type() == QEvent::Leave) {
            if (play_box) {
                play_box->setVisible(false);
                mask->setVisible(false);
                float_box->setVisible(false);
                iden_label->setVisible(true);
            }

        }
    }

    if (o->objectName() == "programImgBox") {
        int i = o->property("index").toInt();
        toggleItem(programItemBox[i], "programImgBox", e);
    }


    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *) e;
        if (mouseEvent->button() == Qt::LeftButton) {
            // 每个区域左右轮播切换
            for (int i = 0; i < 6; ++i) {
                if (i != 2 && i != 4) {
                    int width = wrapconBox[i]->width();
                    int height = wrapconBox[i]->height();
                    int s_width = recomScrollBox->width();
                    if (o->objectName() == "leftArrow" + QString::number(i)) {
                        if (move_x == 0) {
                            int moveLeft = s_width - width;
                            animation[i]->setStartValue(QRect(move_x, 0, width, height));
                            animation[i]->setEndValue(QRect(moveLeft, 0, width, height));
                            move_x = moveLeft;
                        } else {
                            animation[i]->setStartValue(QRect(move_x, 0, width, height));
                            animation[i]->setEndValue(QRect(0, 0, width, height));
                            move_x = 0;
                        }
                        animation[i]->start();
                    }
                    if (o->objectName() == "rightArrow" + QString::number(i)) {
                        if (move_x == 0) {
                            int moveLeft = s_width - width;
                            animation[i]->setStartValue(QRect(move_x, 0, width, height));
                            animation[i]->setEndValue(QRect(moveLeft, 0, width, height));
                            move_x = moveLeft;
                        } else {
                            animation[i]->setStartValue(QRect(move_x, 0, width, height));
                            animation[i]->setEndValue(QRect(0, 0, width, height));
                            move_x = 0;
                        }
                        animation[i]->start();
                    }
                } else {
                    int width = wrapconBox[i]->width();
                    int s_width = recomScrollBox->width();
                    if (o->objectName() == "leftArrow" + QString::number(i)) {
                        if (move_x == 0) {
                            int moveLeft = s_width - width;
                            wrapconBox[i]->move(moveLeft, 0);
                            move_x = moveLeft;
                        } else {
                            wrapconBox[i]->move(0, 0);
                            move_x = 0;
                        }

                    }
                    if (o->objectName() == "rightArrow" + QString::number(i)) {
                        if (move_x == 0) {
                            int moveLeft = s_width - width;
                            wrapconBox[i]->move(moveLeft, 0);
                            move_x = moveLeft;
                        } else {
                            wrapconBox[i]->move(0, 0);
                            move_x = 0;
                        }
                    }
                }
            }

            if(o->objectName() == "heartItemBox"){
                qDebug() << 11;
//                heartItemBox[i]
            }


        }
    }
    return QWidget::eventFilter(o, e);
}


void Recommend::loadQSS() {
    QFile qss(":/resource/qss/recommend.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}