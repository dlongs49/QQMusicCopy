//
// Created by dinglong on 2024/4/10 17:04
//

#include "houseRanking.h"

HouseRanking::HouseRanking(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();

    this->setFixedSize(820, 2000);
    widget = new QWidget(this);
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, 820, 500);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);

    rankingTop();
    regional();
    feature();
    globa();
    widget->setLayout(layout);


}

void HouseRanking::rankingTop() {

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(widget->width() - 20, 558);
    containerBox->setObjectName("selectedBox");

    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6483999.jpg"
            << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6484203.jpg"
            << "https://y.qq.com/music/common/upload/ocs/2681676c054da54091a9f000208e81bf.png"
            << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6482174.jpg";
    for (int i = 0; i < imgList.size(); ++i) {
        item[i] = new QWidget;
        item[i]->installEventFilter(this);
        item[i]->setObjectName("item");
        item[i]->setFixedSize(containerBox->width()/2, 150);

        contentLayout = new QHBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        contentLayout->setAlignment(Qt::AlignTop);



        itemImg = new QLabel(item[i]);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        itemImg->setObjectName("bannerImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 16));
        itemImg->setFixedSize(150, 150);

        maskBox = new QWidget(itemImg);
        maskBox->setFixedSize(itemImg->width(), itemImg->height());
        maskBox->setObjectName("maskBox");
        maskBox->setVisible(false);


        playCountBox = new QWidget(itemImg);
        playCountBox->setObjectName("playCountBox");
        playCountLayout = new QHBoxLayout;
        playCountLayout->setMargin(0);
        playCountLayout->setSpacing(0);
        playCountLayout->setAlignment(Qt::AlignCenter);
        playCountBox->setLayout(playCountLayout);

        playSicon = new QLabel;
        playSicon->setFixedSize(14, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe841));


        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText("203.6万");
        playCount->setFixedSize(playCount->sizeHint());

        playCountLayout->addWidget(playSicon);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width();
        playCountBox->setGeometry(itemImg->width()-10, itemImg->height() - 40, sc+32, 24);


        rightSongBox = new QWidget;


        titleLabel = new QLabel;
        QString txt = tools->textElps("贺峻霖全新单曲《缘故》正式上线 ", 150, titleLabel->font());
        titleLabel->setText(txt);
        titleLabel->setObjectName("titleLabel");


        contentLayout->addWidget(itemImg);

        int r = floor(i / 2) + 1;
        int c = (i % 2) + 1;
        containerLayout->addWidget(item[i],r,c);
    }
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
}

// 地区榜
void HouseRanking::regional() {

}

// 特色榜
void HouseRanking::feature() {
}

// 全球榜
void HouseRanking::globa() {
}

QPixmap *HouseRanking::getImage(QString url) {
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

// 向上动画
void HouseRanking::toggleItem(QWidget *itemBox, QString objName, QEvent *e) {
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


bool HouseRanking::eventFilter(QObject *o, QEvent *e) {
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

void HouseRanking::loadQSS() {
    QFile qss(":/resource/qss/houseRanking.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}