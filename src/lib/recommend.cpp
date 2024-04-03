//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"

Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    this->setFixedSize(820, 1400);

    widget = new QWidget(this);
    widget->setObjectName("conbox");
    widget->setStyleSheet("QWidget#conbox{background:#fff}");
    widget->setFixedSize(820, 1400);
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignRight);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, 820, 600);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(false);


    RecommTop();
    RecommTrea();
    RecommListen();

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

    recomConBox = new QWidget(recomScrollBox);
    recomConBox->setLayout(recomConLayout);
    moveAnimation = new QPropertyAnimation(recomConBox, "geometry");
    moveAnimation->setDuration(300);

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
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]),getImage(imgList[i])->size(),6));
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
    leftArrow[0]->setObjectName("leftArrow[0]");
    leftArrow[0]->installEventFilter(this);
    leftArrow[0]->setFixedSize(30, 38);
    leftArrow[0]->setCursor(Qt::PointingHandCursor);
    leftArrowPix[0] = new QPixmap;
    leftArrowPix[0]->load(":/resource/images/br_lf_arrow.png");
    leftArrow[0]->setPixmap(*leftArrowPix[0]);
    leftArrow[0]->setScaledContents(true);
    leftArrow[0]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[0]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[0]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[0]);


    recomLayout->addWidget(recomScrollBox);

    rightArrow[0] = new QLabel;
    rightArrow[0]->setObjectName("rightArrow[0]");
    rightArrow[0]->installEventFilter(this);
    rightArrow[0]->setFixedSize(30, 38);
    rightArrow[0]->setCursor(Qt::PointingHandCursor);
    rightArrowPix[0] = new QPixmap;
    rightArrowPix[0]->load(":/resource/images/br_rh_arrow.png");
    rightArrow[0]->setPixmap(*rightArrowPix[0]);
    rightArrow[0]->setScaledContents(true);
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

    recomConBox = new QWidget(recomScrollBox);
    recomConBox->setLayout(treaLayout);
    moveAnimation = new QPropertyAnimation(recomConBox, "geometry");
    moveAnimation->setDuration(300);

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
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]),getImage(imgList[i])->size(),6));

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
    leftArrow[1]->setCursor(Qt::PointingHandCursor);
    leftArrow[1]->setFont(tools->aliIcon());
    leftArrow[1]->setText(QChar(0xe6dc));
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
    rightArrow[1]->setText(QChar(0xe6dc));
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
    titPlay->setObjectName("playBox");
    titPlay->setFixedSize(40, 30);
    QPixmap titPlayPix(":/resource/images/play.png");
    titPlay->setPixmap(titPlayPix);
    titPlay->setScaledContents(true);
    titLayout->addWidget(titPlay);
    recomOutLayout->addWidget(titleBox);


    recomBox = new QWidget(recomOutBox);
    recomBox->setFixedSize(recomOutBox->width(), 460);
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
    recomScrollBox->setFixedSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    gridLayout = new QGridLayout;
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);
    gridLayout->setAlignment(Qt::AlignLeft);

    recomConBox = new QWidget(recomScrollBox);
    recomConBox->setLayout(gridLayout);
    moveAnimation = new QPropertyAnimation(recomConBox, "geometry");
    moveAnimation->setDuration(300);
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
    ;
    for (int i = 0; i < imgList.size(); ++i) {
        everyItemBox[i] = new QWidget(recomBox);
        everyItemBox[i]->installEventFilter(this);
        everyItemBox[i]->setFixedSize(240,66);
        everyItemBox[i]->setObjectName("everyItemBox");
        everyItemBox[i]->setProperty("index", i);
        recomAttrList.append("treaImgBox" + QString::number(i));
        listenLayout = new QHBoxLayout;
        listenLayout->setSpacing(0);
        listenLayout->setMargin(0);
        listenLayout->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);

        recomImgBox = new QLabel(everyItemBox[i]);
        recomImgBox->setFixedSize(50, 50);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("everyImgBox");
        // 先提取网络图片 再处理圆角 Tools
        recomImgBox->setPixmap(tools->imgPixRadius(getImage(imgList[i]),getImage(imgList[i])->size(),6));

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
        rightBox->setFixedSize(everyItemBox[i]->width() -76,recomImgBox->height());
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
        QString recomTxt = tools->textElps("五彩湖泊五彩湖泊五彩湖泊五彩湖泊",110,recomTit->font());
        recomTit->setText(recomTxt);
        recomTit->setFixedSize(recomTit->sizeHint().width(),recomTit->sizeHint().height());
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
        authorLabel->setText("衫和");
        rightLayout->addWidget(authorLabel);

        floatLayout = new QHBoxLayout;
        floatLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        floatBox = new QWidget(rightBox);
        floatBox->setObjectName("floatBox");
        floatBox->setVisible(false);
        floatBox->setFixedHeight(rightBox->height());
        floatBox->move(rightBox->width() - 100,0);
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
        int r = floor(i / 3) + 1;
        int c = (i % 3) + 1;
//        qDebug() << r <<c;
        gridLayout->addWidget(everyItemBox[i], r, c);
        gridLayout->setHorizontalSpacing(10);
    }

    leftArrow[2] = new QLabel;
    leftArrow[2]->setObjectName("leftArrow[2]");
    leftArrow[2]->installEventFilter(this);
    leftArrow[2]->setFixedSize(30, 38);
    leftArrow[2]->setCursor(Qt::PointingHandCursor);
    leftArrowPix[2] = new QPixmap;
    leftArrowPix[2]->load(":/resource/images/br_lf_arrow.png");
    leftArrow[2]->setPixmap(*leftArrowPix[2]);
    leftArrow[2]->setScaledContents(true);
    leftArrow[2]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[2]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[2]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[2]);


    recomLayout->addWidget(recomScrollBox);

    rightArrow[2] = new QLabel;
    rightArrow[2]->setObjectName("rightArrow[2]");
    rightArrow[2]->installEventFilter(this);
    rightArrow[2]->setFixedSize(30, 38);
    rightArrow[2]->setCursor(Qt::PointingHandCursor);
    rightArrowPix[2] = new QPixmap;
    rightArrowPix[2]->load(":/resource/images/br_rh_arrow.png");
    rightArrow[2]->setPixmap(*rightArrowPix[2]);
    rightArrow[2]->setScaledContents(true);
    rightArrow[2]->setVisible(false);
    QSizePolicy policy = rightArrow[2]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[2]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[2]);
    layout->addWidget(recomOutBox);
}
QPixmap* Recommend::getImage(QString url) {
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
    if (o->objectName() == "leftArrow[0]") {
        if (e->type() == QEvent::Enter) {
            leftArrow[0]->setPixmap(tools->hoverPixColor(leftArrowPix[0], "#31c27c"));
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[0]->setPixmap(leftArrowImgPath);
        }
    }

    if (o->objectName() == "rightArrow[0]") {
        if (e->type() == QEvent::Enter) {
            rightArrow[0]->setPixmap(tools->hoverPixColor(rightArrowPix[0], "#31c27c"));
        }
        if (e->type() == QEvent::Leave) {
            rightArrow[0]->setPixmap(righArrowImgPath);
        }
    }
    if (o->objectName() == "leftArrow[1]") {
        if (e->type() == QEvent::Enter) {
            leftArrow[1]->setPixmap(tools->hoverPixColor(leftArrowPix[1], "#31c27c"));
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[1]->setPixmap(leftArrowImgPath);
        }
    }

    if (o->objectName() == "rightArrow[1]") {
        if (e->type() == QEvent::Enter) {
            rightArrow[1]->setPixmap(tools->hoverPixColor(rightArrowPix[1], "#31c27c"));
        }
        if (e->type() == QEvent::Leave) {
            rightArrow[1]->setPixmap(righArrowImgPath);
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

    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *) e;
        if (mouseEvent->button() == Qt::LeftButton) {
            int r_width = recomConBox->width();
            int s_width = recomScrollBox->width();
            if (o->objectName() == "leftArrow[1]") {
                if (move_x == 0) {
                    int moveLeft = s_width - r_width;
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(moveLeft, 0, r_width, recomConBox->height()));
                    move_x = moveLeft;
                } else {
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(0, 0, r_width, recomConBox->height()));
                    move_x = 0;
                }
                moveAnimation->start();
            }
            if (o->objectName() == "rightArrow[1]") {
                if (move_x == 0) {
                    int moveLeft = s_width - r_width;
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(moveLeft, 0, r_width, recomConBox->height()));
                    move_x = moveLeft;
                } else {
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(0, 0, r_width, recomConBox->height()));
                    move_x = 0;
                }
                moveAnimation->start();
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