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
        int box_w = containerBox->width() / 2;
        int item_h = 150;
        item[i] = new QWidget;
        item[i]->installEventFilter(this);
        item[i]->setObjectName("item");
        item[i]->setFixedSize(box_w - 20, item_h);
        item[i]->setCursor(Qt::PointingHandCursor);


        contentLayout = new QHBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        item[i]->setLayout(contentLayout);


        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        itemImg->setObjectName("itemImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 40));
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
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe841));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText("203.6万");
        playCount->setFixedSize(playCount->sizeHint());
        playCount->setAlignment(Qt::AlignCenter);

        playCountLayout->addWidget(playSicon);
        playCountLayout->addSpacing(2);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width() + 26;
        playCountBox->setGeometry(itemImg->width() - sc - 10, itemImg->height() - 30, sc, 22);


        rightListLayout = new QVBoxLayout;
        rightListLayout->setMargin(0);
        rightListLayout->setSpacing(0);
        rightListLayout->setAlignment(Qt::AlignTop);
        rightListBox = new QWidget;
        int rw = box_w - itemImg->width() - 40;
        rightListBox->setFixedSize(rw, item_h - 30);
        rightListBox->setLayout(rightListLayout);

        title = new QLabel;
        title->setText("腾讯音乐人原创榜");
        title->setObjectName("blodTit");
        title->setFixedSize(rw,30);
        rightListLayout->addWidget(title);
        rightListLayout->addSpacing(20);

        QStringList slist = {"缘故-贺均分", "蜃楼-周深", "总有人留在过去-黑雾乐队"};
        for (int j = 0; j < slist.size(); ++j) {
            songItem[j] = new QLabel;
            QString txt = tools->textElps(slist[j], rightListBox->width(), songItem[j]->font());
            songItem[j]->setText(txt);
            songItem[j]->setObjectName("songItem");
            rightListLayout->addWidget(songItem[j]);
            rightListLayout->addSpacing(10);
            if(j == slist.size() - 1){
                rightListLayout->addSpacing(0);
            }
        }

        contentLayout->addWidget(itemImg);
        contentLayout->addSpacing(15);
        contentLayout->addWidget(rightListBox);

        int r = floor(i / 2) + 1;
        int c = (i % 2) + 1;
        containerLayout->addWidget(item[i], r, c);
        containerLayout->setSpacing(20);
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