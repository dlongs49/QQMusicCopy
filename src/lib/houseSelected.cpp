//
// Created by dinglong on 2024/4/6 下午 02:49
//

#include "houseSelected.h"

HouseSelected::HouseSelected(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();

    // 对应页面 https://y.qq.com/wk_v17/#/musicroom/recommend
    this->setFixedSize(820, 1350);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    json_data = tools->toJson(":/resource/json/music_selected.json");

    bannerTop();
    officialPlayList();
    listenBook();
    latestIssue();
    classPrefe();
    widget->setLayout(layout);


}

void HouseSelected::bannerTop() {

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

    QJsonObject req_1 = json_data["req_1"].toObject();
    QJsonObject data = req_1["data"].toObject();
    QJsonObject shelf = data["shelf"].toObject();
    QJsonArray v_niche = shelf["v_niche"].toArray();
    QJsonObject v_niche_obj = v_niche.at(0).toObject();
    QJsonArray list = v_niche_obj["v_card"].toArray();
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString cover = item_obj["cover"].toString();
        QJsonObject miscellany = item_obj["miscellany"].toObject();
        QString item_title = item_obj["title"].toString();
        QString item_tag = miscellany["tag"].toString();
        bannerItem[i] = new QWidget;
        bannerItem[i]->installEventFilter(this);
        bannerItem[i]->setObjectName("bannerItem");
        bannerItem[i]->setFixedSize(240, containerBox->height());
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
        bannerImg->setPixmap(tools->imgPixRadius(getImage(cover), getImage(cover)->size(), 16));
        bannerImg->setFixedSize(240, containerBox->height());

        bomBox = new QWidget(bannerImg);
        bomBox->setGeometry(0, bannerImg->height() - 40, bannerImg->width(), 40);
        bomLayout = new QHBoxLayout;
        bomLayout->setAlignment(Qt::AlignBottom);
        bomBox->setLayout(bomLayout);

        tagLabel = new QLabel;
        tagLabel->setObjectName("tagLabel");
        tagLabel->setText(item_tag);
        tagLabel->setFixedSize(tagLabel->sizeHint().width() + 5, tagLabel->sizeHint().height());

        titleLabel = new QLabel;
        QString txt = tools->textElps(item_title, 150, titleLabel->font());
        titleLabel->setText(txt);
        titleLabel->setObjectName("titleLabel");

        bomLayout->addWidget(tagLabel);
        bomLayout->addWidget(titleLabel);

        bannerImgLayout->addWidget(bannerImg);
        bannerItem[i]->setLayout(bannerImgLayout);
        bannerLayout->addWidget(bannerItem[i]);
        if (i != list.size() - 1) {
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

// 官方歌单
void HouseSelected::officialPlayList() {
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
    title->setText("官方歌单");
    titLeftLayout->addWidget(title);
    titLeftLayout->addSpacing(10);

    subTitle = new QLabel;
    subTitle->setObjectName("subTitle");
    subTitle->setText("官方甄选订阅歌单");
    titLeftLayout->addWidget(subTitle);


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
    contentBox->setObjectName("officialBox");

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

    QJsonObject req_2 = json_data["req_2"].toObject();
    QJsonObject data = req_2["data"].toObject();
    QJsonArray modules = data["modules"].toArray();
    QJsonObject modules_obj = modules.at(0).toObject();
    QJsonArray list = modules_obj["grids"].toArray();
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString picurl = item_obj["picurl"].toString();
        QString item_title = item_obj["title"].toString();
        int listen_count = item_obj["listeners"].toInt();
        QString listenCount = tools->toStrWan(listen_count);

        officialItem[i] = new QWidget(contentBox);
        officialItem[i]->setFixedWidth(170);
        officialItem[i]->setObjectName("bannerItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(officialItem[i]);
        itemImg->setFixedSize(170, 170);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("officialImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(picurl), getImage(picurl)->size(), 12));

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

        playCount = new QLabel(itemImg);
        playCount->setFixedWidth(itemImg->width() - 10);
        playCount->setText(listenCount);
        playCount->setAlignment(Qt::AlignRight);
        playCount->setObjectName("playCount");
        playCount->move(0, itemImg->height() - 25);

        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        title->setObjectName("recomTit");
        title->setText(item_title);
        title->setWordWrap(true);
        title->setAlignment(Qt::AlignTop);
        title->setFixedHeight(38);


        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        officialItem[i]->setLayout(itemLayout);
        bannerLayout->addWidget(officialItem[i]);
        bannerLayout->setSpacing(20);
    }

    contentLayout->addWidget(arrowBox(1, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(1, "right"));

    layout->addWidget(containerBox);
    layout->addSpacing(20);
}

// 推荐听书
void HouseSelected::listenBook() {
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
    title->setText("推荐听书");
    titleLayout->addWidget(title);
    containerLayout->addWidget(titleBox);

    contentBox = new QWidget(containerBox);
    contentBox->setFixedSize(containerBox->width(), 230);
    contentBox->installEventFilter(this);
    contentBox->setObjectName("listenBookBox");

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

    QJsonObject req_4 = json_data["req_4"].toObject();
    QJsonObject data = req_4["data"].toObject();
    QJsonArray list = data["radioList"].toArray();
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString cover = item_obj["cover"].toString();
        QString item_title = item_obj["title"].toString();
        int cnt = item_obj["cnt"].toInt();
        QString play_count = tools->toStrWan(cnt);

        listenBookItem[i] = new QWidget(contentBox);
        listenBookItem[i]->setFixedWidth(170);
        listenBookItem[i]->setObjectName("listenBookItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(listenBookItem[i]);
        itemImg->setFixedSize(170, 170);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("listenBookImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(cover), getImage(cover)->size(), 12));

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

        playCount = new QLabel(itemImg);
        playCount->setFixedWidth(itemImg->width() - 10);
        playCount->setText(play_count);
        playCount->setAlignment(Qt::AlignRight);
        playCount->setObjectName("playCount");
        playCount->move(0, itemImg->height() - 25);

        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        title->setText(item_title);
        title->setWordWrap(true);
        title->setAlignment(Qt::AlignTop);
        title->setFixedHeight(38);


        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        listenBookItem[i]->setLayout(itemLayout);
        bannerLayout->addWidget(listenBookItem[i]);
        bannerLayout->setSpacing(20);
    }

    contentLayout->addWidget(arrowBox(2, "left"));
    contentLayout->addWidget(bannerBox);
    contentLayout->addWidget(arrowBox(2, "right"));

    layout->addWidget(containerBox);
    layout->addSpacing(30);
}

// 最新发行
void HouseSelected::latestIssue() {
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

    QJsonObject req_3 = json_data["req_3"].toObject();
    QJsonObject data = req_3["data"].toObject();
    QJsonArray nav = data["lanlist"].toArray();
    for (int i = 0; i < nav.size(); ++i) {
        QJsonObject nav_item = nav.at(i).toObject();
        QString lan = nav_item["lan"].toString();

        latestNavItem[i] = new QLabel;
        latestNavItem[i]->setCursor(Qt::PointingHandCursor);
        latestNavItem[i]->setObjectName("latestNavItem");
        latestNavItem[i]->setText(lan);
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
    contentBox->setFixedSize(containerBox->width(), 250);
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


    QJsonArray list = data["songlist"].toArray();

    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QJsonObject album = item_obj["album"].toObject();
        QString pmid = album["pmid"].toString();
        QString cover = "https://y.qq.com/music/photo_new/T002R300x300M000" + pmid + ".jpg";
        QString item_title = item_obj["name"].toString();
        QString time_public = album["time_public"].toString();
        QJsonArray singer = item_obj["singer"].toArray();
        // 处理 文字拼接
        QString name_str = "";
        for (int y = 0; y < singer.size(); ++y) {
            QJsonObject singers_obj = singer.at(y).toObject();
            QString name = singers_obj["name"].toString();
            name_str = name_str == "" ? name : name_str + "/" + name;
        }

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
        itemImg->setPixmap(tools->imgPixRadius(getImage(cover), getImage(cover)->size(), 12));

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
        QString titleTxt = tools->textElps(item_title, itemImg->width() - 20, title->font());
        title->setText(titleTxt);

        exTitle = new QLabel;
        exTitle->setObjectName("exTitle");
        QString txt = tools->textElps(name_str, itemImg->width() - 20, exTitle->font());
        exTitle->setText(txt);

        dateLabel = new QLabel;
        dateLabel->setObjectName("dateLabel");
        dateLabel->setText(time_public);

        itemLayout->addSpacing(10);
        itemLayout->addWidget(itemImg);
        itemLayout->addSpacing(6);
        itemLayout->addWidget(title);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(exTitle);
        itemLayout->addSpacing(3);
        itemLayout->addWidget(dateLabel);
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
void HouseSelected::classPrefe() {
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

    QJsonObject req_5 = json_data["req_5"].toObject();
    QJsonObject data = req_5["data"].toObject();
    QJsonObject shelf = data["shelf"].toObject();
    QJsonArray v_niche = shelf["v_niche"].toArray();
    QJsonObject v_niche_obj = v_niche.at(0).toObject();
    QJsonArray list = v_niche_obj["v_card"].toArray();
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QJsonObject miscellany = item_obj["miscellany"].toObject();
        QString cover = miscellany["icon"].toString();
        QString item_title = item_obj["title"].toString();
        QString subtitle = item_obj["subtitle"].toString();
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
        itemImg->setPixmap(tools->imgPixRadius(getImage(cover), getImage(cover)->size(), 12));

        maskBox = new QWidget(itemImg);
        maskBox->setFixedSize(itemImg->width(), itemImg->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);


        title = new QLabel;
        title->setCursor(Qt::PointingHandCursor);
        title->setObjectName("recomTit");
        title->setText(item_title);

        exTitle = new QLabel;
        exTitle->setObjectName("exTitle");
        QString txt = tools->textElps(subtitle, itemImg->width() - 20, exTitle->font());
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

QPixmap *HouseSelected::getImage(QString url) {
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
QLabel *HouseSelected::arrowBox(int i, QString type) {
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
void HouseSelected::showArrow(QObject *o, QEvent *e, int i) {
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
void HouseSelected::toggleItem(QWidget *itemBox, QString objName, QEvent *e) {
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


bool HouseSelected::eventFilter(QObject *o, QEvent *e) {
    // 左右箭头交互
    if (o->objectName() == "selectedBox") {
        showArrow(o, e, 0);
    }
    if (o->objectName() == "officialBox") {
        showArrow(o, e, 1);
    }
    if (o->objectName() == "listenBookBox") {
        showArrow(o, e, 2);
    }
    if (o->objectName() == "latestBox") {
        showArrow(o, e, 3);
    }
    if (o->objectName() == "classPrefeBox") {
        showArrow(o, e, 4);
    }
    if (o->objectName() == "officialImg") {
        int i = o->property("index").toInt();
        toggleItem(officialItem[i], "officialImg", e);
    }
    if (o->objectName() == "listenBookImg") {
        int i = o->property("index").toInt();
        toggleItem(listenBookItem[i], "listenBookImg", e);
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

void HouseSelected::loadQSS() {
    QFile qss(":/resource/qss/houseSelected.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}