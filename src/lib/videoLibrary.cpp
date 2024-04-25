//
// Created by dinglong on 2024/4/18 14:54
//

#include "videoLibrary.h"
VideoLibrary::VideoLibrary(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    // 页面  https://y.qq.com/wk_v17/#/mv/list

    this->setFixedSize(820, 0);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");

    json_data = tools->toJson(":/resource/json/video_library.json");

    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);
    tagList();
    allMV();
    widget->setLayout(layout);
}
// 导航
void VideoLibrary::tagList(){
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(this->width() - 80);
    containerLayout = new QVBoxLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerBox->setLayout(containerLayout);

    int nav_w = 80;
    int nav_h = 32;
    areaLayout = new QHBoxLayout;
    areaLayout->setAlignment(Qt::AlignLeft);
    areaLayout->setSpacing(0);
    areaLayout->setMargin(0);
    areaBox = new QWidget;
    areaBox->setLayout(areaLayout);

    for (int i = 0; i < areaList.size(); ++i) {
        areaBtn[i] = new QPushButton;
        areaBtn[i]->installEventFilter(this);
        areaBtn[i]->setFixedSize(nav_w,nav_h);
        areaBtn[i]->setCursor(Qt::PointingHandCursor);
        areaBtn[i]->setText(areaList[i]);
        areaBtn[i]->setObjectName("navItem");
        if(i == 0){
            areaBtn[i]->setProperty("class", "active");
        }else{
            areaBtn[i]->setProperty("class", "nav_item");
        }
        areaLayout->addWidget(areaBtn[i]);
        areaLayout->addSpacing(15);
        connect(areaBtn[i], &QPushButton::clicked, this, [=](){clickNation(i);});
    }

    distLayout = new QHBoxLayout;
    distLayout->setSpacing(0);
    distLayout->setMargin(0);
    distLayout->setAlignment(Qt::AlignLeft);
    distBox = new QWidget;
    distBox->setLayout(distLayout);

    for (int i = 0; i < distList.size(); ++i) {
        distBtn[i] = new QPushButton;
        distBtn[i]->installEventFilter(this);
        distBtn[i]->setFixedSize(nav_w,nav_h);
        distBtn[i]->setCursor(Qt::PointingHandCursor);
        distBtn[i]->setText(distList[i]);
        distBtn[i]->setObjectName("navItem");
        if(i == 0){
            distBtn[i]->setProperty("class", "active");
        }else{
            distBtn[i]->setProperty("class", "nav_item");
        }
        distLayout->addWidget(distBtn[i]);
        distLayout->addSpacing(15);
        connect(distBtn[i], &QPushButton::clicked, this, [=](){clickCategory(i);});
    }

    containerLayout->addWidget(areaBox);
    containerLayout->setSpacing(20);
    containerLayout->addWidget(distBox);

    layout->addSpacing(20);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
}
// 全部MV
void VideoLibrary::allMV() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(this->width() - 80);
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
    title->setText("全部MV");

    rightLayout = new QHBoxLayout;
    rightLayout->setSpacing(0);
    rightLayout->setMargin(0);
    rightLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    rightBox = new QLabel;
    rightBox->setLayout(rightLayout);

    QStringList navList = {"最新", "最热"};
    for (int i = 0; i < navList.size(); ++i) {
        rNavTit[i] = new QLabel;
        rNavTit[i]->installEventFilter(this);
        rNavTit[i]->setCursor(Qt::PointingHandCursor);
        rNavTit[i]->setText(navList[i]);
        rNavTit[i]->setObjectName("rnav_tit");
        rightLayout->addSpacing(30);
        rightLayout->addWidget(rNavTit[i]);
    }

    containerLayout->addWidget(titleBox);

    titleLayout->addWidget(title);
    titleLayout->addWidget(rightBox);

    contentBox = new QWidget(containerBox);
    contentBox->setFixedWidth(containerBox->width());
    contentBox->installEventFilter(this);
    containerLayout->addSpacing(6);
    containerLayout->addWidget(contentBox);

    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    contentBox->setLayout(contentLayout);

    bannerBox = new QWidget(contentBox);
    bannerBox->setFixedWidth(contentBox->width());

    mvLayout = new QGridLayout;
    mvLayout->setSpacing(0);
    mvLayout->setMargin(0);
    mvLayout->setAlignment(Qt::AlignLeft);

    wrapconBox = new QWidget(bannerBox);
    wrapconBox->setLayout(mvLayout);
    animation = new QPropertyAnimation(wrapconBox, "geometry");
    animation->setDuration(300);

    QJsonObject req_0 = json_data["req_0"].toObject();
    QJsonObject data = req_0["data"].toObject();
    QJsonArray list = data["list"].toArray();
    int cl = ceil((double)list.size()/3);
    for (int i = 0; i < list.size(); ++i) {
        QJsonObject mv_item = list.at(i).toObject();
        QString picurl = mv_item["picurl"].toString();
        QString title_str = mv_item["title"].toString();
        QJsonArray singers = mv_item["singers"].toArray();
        // 处理 文字拼接
        QString name_str = "";
        for (int y = 0; y < singers.size(); ++y) {
            QJsonObject singers_obj = singers.at(y).toObject();
            QString name = singers_obj["name"].toString();
            name_str = name_str == "" ? name : name_str + "/" + name;
        }


        int item_w = (bannerBox->width()/3) - 12;
        mvItem[i] = new QWidget;
        mvItem[i]->setFixedWidth(item_w);
        mvItem[i]->setObjectName("bannerItem");
        itemLayout = new QVBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);

        itemImg = new QLabel(mvItem[i]);
        itemImg->setFixedSize(item_w, 142);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("mvImg");
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
        QString txt = tools->textElps(title_str, itemImg->width()-6, title->font());
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
        mvItem[i]->setLayout(itemLayout);

        int r = floor(i / 3) + 1;
        int c = (i % 3) + 1;
        mvLayout->addWidget(mvItem[i],r,c);
        mvLayout->setSpacing(20);
    }
    int hh = cl * 224;
    contentBox->setFixedHeight(hh);
    bannerBox->setFixedHeight(hh);
    contentLayout->addWidget(bannerBox);
    layout->addWidget(containerBox);
    this->setFixedHeight(hh + 120);
    widget->setFixedSize(this->size());
}


QPixmap *VideoLibrary::getImage(QString url) {
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
void VideoLibrary::clickNation(int i){
    for (int j = 0; j < areaList.size(); ++j) {
        areaBtn[j]->setProperty("class", "nav_item");
        areaBtn[j]->style()->polish(areaBtn[j]);
    }
    areaBtn[i]->setProperty("class", "active");
    areaBtn[i]->style()->polish(areaBtn[i]);
}
void VideoLibrary::clickCategory(int i){
    for (int j = 0; j < distList.size(); ++j) {
        distBtn[j]->setProperty("class", "nav_item");
        distBtn[j]->style()->polish(distBtn[j]);
    }
    distBtn[i]->setProperty("class", "active");
    distBtn[i]->style()->polish(distBtn[i]);
}
// 轮播图切换
void VideoLibrary::toggleItem(QWidget *itemBox, QString objName, QEvent *e) {
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
bool VideoLibrary::eventFilter(QObject *o, QEvent *e) {
    if (o->objectName() == "mvImg") {
        int i = o->property("index").toInt();
        toggleItem(mvItem[i], "mvImg", e);
    }
    return QWidget::eventFilter(o, e);

}

void VideoLibrary::loadQSS() {
    QFile qss(":/resource/qss/videoLibrary.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}

