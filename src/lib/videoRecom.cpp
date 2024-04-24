//
// Created by dinglong on 2024/4/16 11:51
//

#include "videoRecom.h"

VideoRecom::VideoRecom(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    // 页面  https://y.qq.com/wk_v17/#/mv/recommend

    this->setFixedSize(820, 1700);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    json_data = tools->toJson(":/resource/json/video.json");

    bannerTop();
    newest();
    hotList();
    assemble();
    indiv();
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

    QJsonObject obj = tools->toJson(":/resource/json/getmv_by_tag.json");
    QJsonObject data = obj["data"].toObject();
    QJsonObject focus = data["focus"].toObject();
    QJsonArray bannerList = focus["list"].toArray();

    for (int i = 0; i < bannerList.size(); ++i) {
        QJsonObject banner_item = bannerList.at(i).toObject();
        QString picurl = banner_item["picurl"].toString();
        int item_w = (scrollBox->width() / 2) - 10;
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
        bannerImg->setPixmap(tools->imgPixRadius(getImage(picurl), getImage(picurl)->size(), 16));
        bannerImg->setFixedSize(item_w, containerBox->height());

        bannerImgLayout->addWidget(bannerImg);
        bannerItem[i]->setLayout(bannerImgLayout);
        bannerLayout->addWidget(bannerItem[i]);
        if (i != bannerList.size() - 1) {
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

    QJsonObject req = json_data["req_1"].toObject();
    QJsonObject data = req["data"].toObject();
    QJsonArray list = data["list"].toArray();
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString picurl = item_obj["picurl"].toString();
        QString item_title = item_obj["title"].toString();
        int play_count = item_obj["playcnt"].toInt();
        QString playcnt = tools->toStrWan(play_count);
        QJsonArray singers = item_obj["singers"].toArray();
        // 处理 文字拼接
        QString name_str = "";
        for (int j = 0; j < singers.size(); ++j) {
            QJsonObject singers_obj = singers.at(j).toObject();
            QString name = singers_obj["name"].toString();
            name_str = name_str == "" ? name : name_str + "/" + name;
        }

        int item_w = (bannerBox->width() / 3) - 12;
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
        itemImg->setPixmap(tools->imgPixRadius(getImage(picurl), getImage(picurl)->size(), 12));

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
        playCountBox->setVisible(true);

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe633));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText(playcnt);
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
        QString txt = tools->textElps(item_title, itemImg->width() - 6, title->font());
        title->setText(txt);
        title->setAlignment(Qt::AlignTop);

        author = new QLabel;
        author->setCursor(Qt::PointingHandCursor);
        author->setObjectName("author");
        author->setText(name_str);
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

    contentLayout->
            addWidget(arrowBox(1, "left")
    );
    contentLayout->
            addWidget(bannerBox);
    contentLayout->
            addWidget(arrowBox(1, "right")
    );

    layout->
            addWidget(containerBox);
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
    animation[2] = new QPropertyAnimation(wrapconBox[2], "geometry");
    animation[2]->setDuration(300);

    QJsonObject req = json_data["req_2"].toObject();
    QJsonObject data = req["data"].toObject();
    QJsonArray list = data["list"].toArray();
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString picurl = item_obj["picurl"].toString();
        QString item_title = item_obj["title"].toString();
        int play_count = item_obj["playcnt"].toInt();
        QString playcnt = tools->toStrWan(play_count);
        QJsonArray singers = item_obj["singers"].toArray();
        // 处理 文字拼接
        QString name_str = "";
        for (int j = 0; j < singers.size(); ++j) {
            QJsonObject singers_obj = singers.at(j).toObject();
            QString name = singers_obj["name"].toString();
            name_str = name_str == "" ? name : name_str + "/" + name;
        }
        int item_w = (bannerBox->width() / 3) - 12;
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
        itemImg->setPixmap(tools->imgPixRadius(getImage(picurl), getImage(picurl)->size(), 12));

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
        playCountBox->setVisible(true);

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe633));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText(playcnt);
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
        QString txt = tools->textElps(item_title, itemImg->width() - 6,
                                      title->font());
        title->setText(txt);
        title->setAlignment(Qt::AlignTop);

        author = new QLabel;
        author->setCursor(Qt::PointingHandCursor);
        author->setObjectName("author");
        author->setText(name_str);
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

    contentLayout->addWidget(arrowBox(2, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(2, "right"));

    layout->addWidget(containerBox);
    layout->addSpacing(20);
}

// 合集
void VideoRecom::assemble() {
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
    title->setText("合集");

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
    contentBox->setObjectName("assembleBox");
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


    QJsonObject req = json_data["req_3"].toObject();
    QJsonObject data = req["data"].toObject();
    QJsonArray list = data["list"].toArray();
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString picurl = item_obj["picurl"].toString();
        QString item_title = item_obj["title"].toString();
        QString subtitle = item_obj["subtitle"].toString();
        int item_w = (bannerBox->width() / 3) - 12;
        assemItem[i] = new QWidget(contentBox);
        assemItem[i]->setFixedWidth(item_w);
        assemItem[i]->setObjectName("bannerItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        l = new QLabel(assemItem[i]);
        l->setFixedSize(item_w - 20, 4);
        l->move(((item_w - l->width()) / 2), 5);
        l->setObjectName("bg_l");
        ll = new QLabel(assemItem[i]);
        ll->setFixedSize(item_w - 36, 4);
        ll->move(((item_w - ll->width()) / 2), 1);
        ll->setObjectName("bg_ll");

        itemImg = new QLabel(assemItem[i]);
        itemImg->setFixedSize(item_w, 142);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("assemImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(picurl), getImage(picurl)->size(), 12));

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

        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        QString txt = tools->textElps(item_title, itemImg->width() - 6,
                                      title->font());
        title->setText(txt);
        title->setAlignment(Qt::AlignTop);

        author = new QLabel;
        author->setCursor(Qt::PointingHandCursor);
        author->setObjectName("author");
        author->setText(subtitle);
        author->setFixedSize(author->sizeHint());
        author->setAlignment(Qt::AlignTop);

        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(author);
        assemItem[i]->setLayout(itemLayout);
        bannerLayout->addWidget(assemItem[i]);
        bannerLayout->setSpacing(20);
    }

    contentLayout->addWidget(arrowBox(3, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(3, "right"));

    layout->addWidget(containerBox);
    layout->addSpacing(20);
}

// 个性推荐
void VideoRecom::indiv() {
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
    title->setText("个性推荐");

    moreRightLayout = new QHBoxLayout;
    moreRightLayout->setSpacing(0);
    moreRightLayout->setMargin(0);
    moreRightLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    rightMoreBox = new QLabel;
    rightMoreBox->setFixedWidth(60);
    rightMoreBox->setObjectName("rightMoreBox");
    rightMoreBox->setCursor(Qt::PointingHandCursor);
    rightMoreBox->setLayout(moreRightLayout);

    arrowTitle = new QLabel;
    arrowTitle->setObjectName("refresh");
    arrowTitle->setFont(tools->aliIcon());
    arrowTitle->setText(QChar(0xe65c));
    arrowTitle->setFixedSize(18, 18);
    moreRightLayout->addWidget(arrowTitle);

    moreTitle = new QLabel;
    moreTitle->setObjectName("moreTit");
    moreTitle->setText("换一批");
    moreRightLayout->addWidget(moreTitle);
    moreRightLayout->addSpacing(5);

    containerLayout->addWidget(titleBox);

    titleLayout->addWidget(title);
    titleLayout->addWidget(rightMoreBox);
    titleLayout->addSpacing(20);

    contentBox = new QWidget(containerBox);
    contentBox->setFixedWidth(containerBox->width());
    contentBox->installEventFilter(this);
    contentBox->setObjectName("indivBox");
    containerLayout->addSpacing(6);
    containerLayout->addWidget(contentBox);

    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    contentBox->setLayout(contentLayout);

    bannerBox = new QWidget(contentBox);
    bannerBox->setFixedWidth(contentBox->width() - 60);
    bannerBox->setObjectName("bannerBox");

    indivLayout = new QGridLayout;
    indivLayout->setSpacing(0);
    indivLayout->setMargin(0);
    indivLayout->setAlignment(Qt::AlignLeft);

    wrapconBox[4] = new QWidget(bannerBox);
    wrapconBox[4]->setLayout(indivLayout);
    animation[4] = new QPropertyAnimation(wrapconBox[4], "geometry");
    animation[4]->setDuration(300);

    QJsonObject req = json_data["req_0"].toObject();
    QJsonObject data = req["data"].toObject();
    QJsonArray feedsList = data["vecFeeds"].toArray();
    int cl = ceil(feedsList.size() / 3);
    for (int i = 0; i < feedsList.size(); ++i) {
        QJsonObject item_obj = feedsList.at(i).toObject();
        QJsonObject videoObj = item_obj["video"].toObject();
        QString picurl = videoObj["cover_pic"].toString();
        QString name = videoObj["name"].toString();
        QString uploader_nick = videoObj["uploader_nick"].toString();
        int play_count = videoObj["playcnt"].toInt();
        QString playcnt = tools->toStrWan(play_count);
        int item_w = (bannerBox->width() / 3) - 12;
        indivItem[i] = new QWidget(contentBox);
        indivItem[i]->setFixedWidth(item_w);
        indivItem[i]->setObjectName("bannerItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(indivItem[i]);
        itemImg->setFixedSize(item_w, 142);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setObjectName("indivImg");
        itemImg->setScaledContents(true);
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        QPixmap pixmap = tools->imgPixRadius(getImage(picurl), getImage(picurl)->size(), 12);
        pixmap.scaled(itemImg->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        itemImg->setPixmap(pixmap);

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
        playCountBox->setVisible(true);

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe633));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText(playcnt);
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
        QString txt = tools->textElps(name, itemImg->width() - 6,
                                      title->font());
        title->setText(txt);
        title->setAlignment(Qt::AlignTop);

        author = new QLabel;
        author->setCursor(Qt::PointingHandCursor);
        author->setObjectName("author");
        author->setText(uploader_nick);
        author->setFixedSize(author->sizeHint());
        author->setAlignment(Qt::AlignTop);

        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(author);
        indivItem[i]->setLayout(itemLayout);

        int r = floor(i / 3) + 1;
        int c = (i % cl) + 1;
        indivLayout->addWidget(indivItem[i], r, c);
        indivLayout->setSpacing(20);
    }
    contentBox->setFixedHeight(cl * 220);
    bannerBox->setFixedHeight(cl * 220);

    contentLayout->addWidget(arrowBox(2, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(2, "right"));
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
    if (o->objectName() == "assembleBox") {
        showArrow(o, e, 3);
    }
    if (o->objectName() == "newestImg") {
        int i = o->property("index").toInt();
        toggleItem(newestItem[i], "newestImg", e);
    }
    if (o->objectName() == "hotImg") {
        int i = o->property("index").toInt();
        toggleItem(hotItem[i], "hotImg", e);
    }

    if (o->objectName() == "assemImg") {
        int i = o->property("index").toInt();
        toggleItem(assemItem[i], "assemImg", e);
    }
    if (o->objectName() == "indivImg") {
        int i = o->property("index").toInt();
        toggleItem(indivItem[i], "indivImg", e);
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