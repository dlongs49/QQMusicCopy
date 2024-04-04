//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"

Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    this->setFixedSize(820, 2000);
//    this->setFixedWidth(820);
//    this->setMinimumHeight(700);
    widget = new QWidget(this);
    widget->setObjectName("conbox");
    widget->setStyleSheet("QWidget#conbox{background:#fff}");
    widget->setFixedSize(820, 2000);
//    widget->setFixedWidth(820);
//    widget->setMinimumHeight(700);
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignRight);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, 820, 700);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(false);


    RecommTop();
    RecommTrea();
    RecommListen();
    RecommRoam();
    RecommHeartbeat();
    RecommProgram();
    widget->setLayout(layout);

    tools = new Tools();

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
        recomAttrList.append("recomImgBox" + QString::number(i));
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

    leftArrow[0] = new QLabel;
    leftArrow[0]->setObjectName("leftArrow_0");
    leftArrow[0]->installEventFilter(this);
    leftArrow[0]->setFixedSize(30, 38);
    leftArrow[0]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftArrow[0]->setCursor(Qt::PointingHandCursor);
    leftArrow[0]->setFont(tools->aliIcon());
    leftArrow[0]->setText(QChar(0xea84));
    leftArrow[0]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[0]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[0]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[0]);

    recomLayout->addWidget(recomScrollBox);

    rightArrow[0] = new QLabel;
    rightArrow[0]->setObjectName("rightArrow_0");
    rightArrow[0]->installEventFilter(this);
    rightArrow[0]->setFixedSize(30, 38);
    rightArrow[0]->setCursor(Qt::PointingHandCursor);
    rightArrow[0]->setFont(tools->aliIcon());
    rightArrow[0]->setText(QChar(0xe63e));
    rightArrow[0]->setVisible(false);
    QSizePolicy policy = rightArrow[0]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[0]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[0]);
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
        recomAttrList.append("treaImgBox" + QString::number(i));
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

    leftArrow[1] = new QLabel;
    leftArrow[1]->setObjectName("leftArrow_1");
    leftArrow[1]->installEventFilter(this);
    leftArrow[1]->setFixedSize(30, 38);
    leftArrow[1]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftArrow[1]->setCursor(Qt::PointingHandCursor);
    leftArrow[1]->setFont(tools->aliIcon());
    leftArrow[1]->setText(QChar(0xea84));
    leftArrow[1]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[1]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[1]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[1]);


    recomLayout->addWidget(recomScrollBox);

    rightArrow[1] = new QLabel;
    rightArrow[1]->setObjectName("rightArrow_1");
    rightArrow[1]->installEventFilter(this);
    rightArrow[1]->setFixedSize(30, 38);
    rightArrow[1]->setCursor(Qt::PointingHandCursor);
    rightArrow[1]->setFont(tools->aliIcon());
    rightArrow[1]->setText(QChar(0xe63e));
    rightArrow[1]->setVisible(false);
    QSizePolicy policy = rightArrow[1]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[1]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[1]);
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
        recomAttrList.append("treaImgBox" + QString::number(i));
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
//        rightBox->setStyleSheet("background:#ff0");

        songsLayout = new QHBoxLayout;
        songsLayout->setMargin(0);
        songsLayout->setSpacing(0);
        songsLayout->setAlignment(Qt::AlignVCenter);
        songsLabel = new QLabel;
//        songsLabel->setStyleSheet("background:#f0f");
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
        authorLabel->setText("衫和"+QString::number(i));
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
        qDebug() << r << c;
        gridLayout->addWidget(everyItemBox[i], r, c);
        gridLayout->setHorizontalSpacing(10);
    }

    leftArrow[2] = new QLabel;
    leftArrow[2]->setObjectName("leftArrow_2");
    leftArrow[2]->installEventFilter(this);
    leftArrow[2]->setFixedSize(30, 38);
    leftArrow[2]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftArrow[2]->setCursor(Qt::PointingHandCursor);
    leftArrow[2]->setFont(tools->aliIcon());
    leftArrow[2]->setText(QChar(0xea84));
    leftArrow[2]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[2]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[2]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[2]);

    recomLayout->addWidget(recomScrollBox);

    rightArrow[2] = new QLabel;
    rightArrow[2]->setObjectName("rightArrow_2");
    rightArrow[2]->installEventFilter(this);
    rightArrow[2]->setFixedSize(30, 38);
    rightArrow[2]->setCursor(Qt::PointingHandCursor);
    rightArrow[2]->setFont(tools->aliIcon());
    rightArrow[2]->setText(QChar(0xe63e));
    rightArrow[2]->setVisible(false);
    QSizePolicy policy = rightArrow[2]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[2]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[2]);
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
        recomAttrList.append("treaImgBox" + QString::number(i));
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

    leftArrow[3] = new QLabel;
    leftArrow[3]->setObjectName("leftArrow_3");
    leftArrow[3]->installEventFilter(this);
    leftArrow[3]->setFixedSize(30, 38);
    leftArrow[3]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftArrow[3]->setCursor(Qt::PointingHandCursor);
    leftArrow[3]->setFont(tools->aliIcon());
    leftArrow[3]->setText(QChar(0xea84));
    leftArrow[3]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[3]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[3]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[3]);


    recomLayout->addWidget(recomScrollBox);

    rightArrow[3] = new QLabel;
    rightArrow[3]->setObjectName("rightArrow_3");
    rightArrow[3]->installEventFilter(this);
    rightArrow[3]->setFixedSize(30, 38);
    rightArrow[3]->setCursor(Qt::PointingHandCursor);
    rightArrow[3]->setFont(tools->aliIcon());
    rightArrow[3]->setText(QChar(0xe63e));
    rightArrow[3]->setVisible(false);
    QSizePolicy policy = rightArrow[3]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[3]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[3]);
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
        recomAttrList.append("treaImgBox" + QString::number(i));
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
//        rightBox->setStyleSheet("background:#ff0");

        songsLayout = new QHBoxLayout;
        songsLayout->setMargin(0);
        songsLayout->setSpacing(0);
        songsLayout->setAlignment(Qt::AlignVCenter);
        songsLabel = new QLabel;
//        songsLabel->setStyleSheet("background:#f0f");
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
        authorLabel->setText("衫和"+QString::number(i));
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
        qDebug() << r << c;
        gridLayout->addWidget(heartItemBox[i], r, c);
        gridLayout->setHorizontalSpacing(10);
    }

    leftArrow[4] = new QLabel;
    leftArrow[4]->setObjectName("leftArrow_4");
    leftArrow[4]->installEventFilter(this);
    leftArrow[4]->setFixedSize(30, 38);
    leftArrow[4]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftArrow[4]->setCursor(Qt::PointingHandCursor);
    leftArrow[4]->setFont(tools->aliIcon());
    leftArrow[4]->setText(QChar(0xea84));
    leftArrow[4]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[4]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[4]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[4]);

    recomLayout->addWidget(recomScrollBox);

    rightArrow[4] = new QLabel;
    rightArrow[4]->setObjectName("rightArrow_4");
    rightArrow[4]->installEventFilter(this);
    rightArrow[4]->setFixedSize(30, 38);
    rightArrow[4]->setCursor(Qt::PointingHandCursor);
    rightArrow[4]->setFont(tools->aliIcon());
    rightArrow[4]->setText(QChar(0xe63e));
    rightArrow[4]->setVisible(false);
    QSizePolicy policy = rightArrow[4]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[4]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[4]);
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
        recomAttrList.append("treaImgBox" + QString::number(i));
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

    leftArrow[5] = new QLabel;
    leftArrow[5]->setObjectName("leftArrow_5");
    leftArrow[5]->installEventFilter(this);
    leftArrow[5]->setFixedSize(30, 38);
    leftArrow[5]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftArrow[5]->setCursor(Qt::PointingHandCursor);
    leftArrow[5]->setFont(tools->aliIcon());
    leftArrow[5]->setText(QChar(0xea84));
    leftArrow[5]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[5]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[5]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[5]);


    recomLayout->addWidget(recomScrollBox);

    rightArrow[5] = new QLabel;
    rightArrow[5]->setObjectName("rightArrow_5");
    rightArrow[5]->installEventFilter(this);
    rightArrow[5]->setFixedSize(30, 38);
    rightArrow[5]->setCursor(Qt::PointingHandCursor);
    rightArrow[5]->setFont(tools->aliIcon());
    rightArrow[5]->setText(QChar(0xe63e));
    rightArrow[5]->setVisible(false);
    QSizePolicy policy = rightArrow[5]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[5]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[5]);
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

bool Recommend::eventFilter(QObject *o, QEvent *e) {
    if (o->objectName() == "recomBox") {
        if (e->type() == QEvent::Enter) {
            leftArrow[0]->setVisible(true);
            rightArrow[0]->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[0]->setVisible(false);
            rightArrow[0]->setVisible(false);
        }
    }
    if (o->objectName() == "treaBox") {
        if (e->type() == QEvent::Enter) {
            leftArrow[1]->setVisible(true);
            rightArrow[1]->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[1]->setVisible(false);
            rightArrow[1]->setVisible(false);
        }
    }
    if (o->objectName() == "listenBox") {
        if (e->type() == QEvent::Enter) {
            leftArrow[2]->setVisible(true);
            rightArrow[2]->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[2]->setVisible(false);
            rightArrow[2]->setVisible(false);
        }
    }
    if (o->objectName() == "roamBox") {
        if (e->type() == QEvent::Enter) {
            leftArrow[3]->setVisible(true);
            rightArrow[3]->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[3]->setVisible(false);
            rightArrow[3]->setVisible(false);
        }
    }
    if (o->objectName() == "heartBox") {
        if (e->type() == QEvent::Enter) {
            leftArrow[4]->setVisible(true);
            rightArrow[4]->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[4]->setVisible(false);
            rightArrow[4]->setVisible(false);
        }
    }
    if (o->objectName() == "programBox") {
        if (e->type() == QEvent::Enter) {
            leftArrow[5]->setVisible(true);
            rightArrow[5]->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[5]->setVisible(false);
            rightArrow[5]->setVisible(false);
        }
    }

    if (o->objectName() == "recomImgBox") {
        int i = o->property("index").toInt();
        QLabel *box = recomItemBox[i]->findChild<QLabel *>("recomImgBox");
        QWidget *mask = recomItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = recomItemBox[i]->findChild<QLabel *>("playBox");
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
        }
        if (e->type() == QEvent::Leave) {
            animation->setStartValue(QRect(0, 0, box->width(), box->height()));
            animation->setEndValue(QRect(0, 10, box->width(), box->height()));
            animation->start();
            if (play_box) {
                play_box->setVisible(false);
                mask->setVisible(false);
            }
        }
    }

    if (o->objectName() == "treaImgBox") {
        int i = o->property("index").toInt();
        QLabel *box = treaItemBox[i]->findChild<QLabel *>("treaImgBox");
        QWidget *mask = treaItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = treaItemBox[i]->findChild<QLabel *>("playBox");
        QLabel *play_count = treaItemBox[i]->findChild<QLabel *>("playCount");
        QPropertyAnimation *animation = new QPropertyAnimation(box, "geometry");
        animation->setDuration(150);

        if (e->type() == QEvent::Enter) {
            animation->setStartValue(QRect(0, 10, box->width(), box->height()));
            animation->setEndValue(QRect(0, 0, box->width(), box->height()));
            animation->start();
            if (play_box) {
                play_box->setVisible(true);
                mask->setVisible(true);
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
                play_count->setVisible(true);
            }
        }
    }
    if (o->objectName() == "everyItemBox") {
        int i = o->property("index").toInt();
        QWidget *mask = everyItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = everyItemBox[i]->findChild<QLabel *>("listenPlay");
        QWidget *float_box = everyItemBox[i]->findChild<QWidget *>("floatBox");
        QLabel *iden_label = everyItemBox[i]->findChild<QLabel *>("idenLabel");
        QLabel *songs_tit = everyItemBox[i]->findChild<QLabel *>("songsTit");

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
        QLabel *box = roamItemBox[i]->findChild<QLabel *>("roamImgBox");
        QWidget *mask = roamItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = roamItemBox[i]->findChild<QLabel *>("playBox");
        QLabel *play_count = roamItemBox[i]->findChild<QLabel *>("playCount");
        QPropertyAnimation *animation = new QPropertyAnimation(box, "geometry");
        animation->setDuration(150);

        if (e->type() == QEvent::Enter) {
            animation->setStartValue(QRect(0, 10, box->width(), box->height()));
            animation->setEndValue(QRect(0, 0, box->width(), box->height()));
            animation->start();
            if (play_box) {
                play_box->setVisible(true);
                mask->setVisible(true);
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
                play_count->setVisible(true);
            }
        }
    }

    if (o->objectName() == "heartImgBox") {
        int i = o->property("index").toInt();
        QLabel *box = heartItemBox[i]->findChild<QLabel *>("treaImgBox");
        QWidget *mask = heartItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = heartItemBox[i]->findChild<QLabel *>("playBox");
        QLabel *play_count = heartItemBox[i]->findChild<QLabel *>("playCount");
        QPropertyAnimation *animation = new QPropertyAnimation(box, "geometry");
        animation->setDuration(150);

        if (e->type() == QEvent::Enter) {
            animation->setStartValue(QRect(0, 10, box->width(), box->height()));
            animation->setEndValue(QRect(0, 0, box->width(), box->height()));
            animation->start();
            if (play_box) {
                play_box->setVisible(true);
                mask->setVisible(true);
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
                play_count->setVisible(true);
            }
        }
    }
    if (o->objectName() == "heartItemBox") {
        int i = o->property("index").toInt();
        QWidget *mask = heartItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = heartItemBox[i]->findChild<QLabel *>("listenPlay");
        QWidget *float_box = heartItemBox[i]->findChild<QWidget *>("floatBox");
        QLabel *iden_label = heartItemBox[i]->findChild<QLabel *>("idenLabel");
        QLabel *songs_tit = everyItemBox[i]->findChild<QLabel *>("songsTit");

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
        QLabel *box = programItemBox[i]->findChild<QLabel *>("programImgBox");
        QWidget *mask = programItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = programItemBox[i]->findChild<QLabel *>("playBox");
        QLabel *play_count = programItemBox[i]->findChild<QLabel *>("playCount");
        QPropertyAnimation *animation = new QPropertyAnimation(box, "geometry");
        animation->setDuration(150);
        if (e->type() == QEvent::Enter) {
            animation->setStartValue(QRect(0, 10, box->width(), box->height()));
            animation->setEndValue(QRect(0, 0, box->width(), box->height()));
            animation->start();
            if (play_box) {
                play_box->setVisible(true);
                mask->setVisible(true);
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
                play_count->setVisible(true);
            }
        }
    }


    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *) e;
        if (mouseEvent->button() == Qt::LeftButton) {
            if (o->objectName() == "leftArrow_0" || o->objectName() == "rightArrow_0") {
                int r_width = wrapconBox[0]->width();
                int s_width = recomScrollBox->width();
                qDebug() << r_width << s_width;
                if (o->objectName() == "leftArrow_0") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[0]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[0]->height()));
                        animation[0]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[0]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[0]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[0]->height()));
                        animation[0]->setEndValue(QRect(0, 0, r_width, wrapconBox[0]->height()));
                        move_x = 0;
                    }
                    animation[0]->start();
                }
                if (o->objectName() == "rightArrow_0") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[0]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[0]->height()));
                        animation[0]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[0]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[0]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[0]->height()));
                        animation[0]->setEndValue(QRect(0, 0, r_width, wrapconBox[0]->height()));
                        move_x = 0;
                    }
                    animation[0]->start();
                }
            }
            if (o->objectName() == "leftArrow_1" || o->objectName() == "rightArrow_1") {
                int r_width = wrapconBox[1]->width();
                int s_width = recomScrollBox->width();
                qDebug() << r_width << s_width;
                if (o->objectName() == "leftArrow_1") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[1]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[1]->height()));
                        animation[1]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[1]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[1]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[1]->height()));
                        animation[1]->setEndValue(QRect(0, 0, r_width, wrapconBox[1]->height()));
                        move_x = 0;
                    }
                    animation[1]->start();
                }
                if (o->objectName() == "rightArrow_1") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[1]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[1]->height()));
                        animation[1]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[1]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[1]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[1]->height()));
                        animation[1]->setEndValue(QRect(0, 0, r_width, wrapconBox[1]->height()));
                        move_x = 0;
                    }
                    animation[1]->start();
                }
            }
            if (o->objectName() == "leftArrow_2" || o->objectName() == "rightArrow_2") {
                int r_width = wrapconBox[2]->width();
                int s_width = recomScrollBox->width();
                qDebug() << r_width << s_width;
                if (o->objectName() == "leftArrow_2") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        wrapconBox[2]->move(moveLeft,0);
                        move_x = moveLeft;
                    }else{
                        wrapconBox[2]->move(0,0);
                        move_x = 0;
                    }

                }
                if (o->objectName() == "rightArrow_2") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        wrapconBox[2]->move(moveLeft,0);
                        move_x = moveLeft;
                    } else {
                        wrapconBox[2]->move(0,0);
                        move_x = 0;
                    }
                }
            }
            if (o->objectName() == "leftArrow_3" || o->objectName() == "rightArrow_3") {
                int r_width = wrapconBox[3]->width();
                int s_width = recomScrollBox->width();
                qDebug() << r_width << s_width;
                if (o->objectName() == "leftArrow_3") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[3]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[3]->height()));
                        animation[3]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[3]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[3]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[3]->height()));
                        animation[3]->setEndValue(QRect(0, 0, r_width, wrapconBox[3]->height()));
                        move_x = 0;
                    }
                    animation[3]->start();
                }
                if (o->objectName() == "rightArrow_3") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[3]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[3]->height()));
                        animation[3]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[3]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[3]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[3]->height()));
                        animation[3]->setEndValue(QRect(0, 0, r_width, wrapconBox[3]->height()));
                        move_x = 0;
                    }
                    animation[3]->start();
                }
            }
            if (o->objectName() == "leftArrow_4" || o->objectName() == "rightArrow_4") {
                int r_width = wrapconBox[4]->width();
                int s_width = recomScrollBox->width();
                qDebug() << r_width << s_width;
                if (o->objectName() == "leftArrow_4") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        wrapconBox[4]->move(moveLeft,0);
                        move_x = moveLeft;
                    }else{
                        wrapconBox[4]->move(0,0);
                        move_x = 0;
                    }

                }
                if (o->objectName() == "rightArrow_4") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        wrapconBox[4]->move(moveLeft,0);
                        move_x = moveLeft;
                    } else {
                        wrapconBox[4]->move(0,0);
                        move_x = 0;
                    }
                }
            }
            if (o->objectName() == "leftArrow_5" || o->objectName() == "rightArrow_5") {
                int r_width = wrapconBox[5]->width();
                int s_width = recomScrollBox->width();
                qDebug() << r_width << s_width;
                if (o->objectName() == "leftArrow_5") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[5]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[5]->height()));
                        animation[5]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[5]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[5]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[5]->height()));
                        animation[5]->setEndValue(QRect(0, 0, r_width, wrapconBox[5]->height()));
                        move_x = 0;
                    }
                    animation[5]->start();
                }
                if (o->objectName() == "rightArrow_5") {
                    if (move_x == 0) {
                        int moveLeft = s_width - r_width;
                        animation[5]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[5]->height()));
                        animation[5]->setEndValue(QRect(moveLeft, 0, r_width, wrapconBox[5]->height()));
                        move_x = moveLeft;
                    } else {
                        animation[5]->setStartValue(QRect(move_x, 0, r_width, wrapconBox[5]->height()));
                        animation[5]->setEndValue(QRect(0, 0, r_width, wrapconBox[5]->height()));
                        move_x = 0;
                    }
                    animation[5]->start();
                }
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