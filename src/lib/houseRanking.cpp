//
// Created by dinglong on 2024/4/10 17:04
//

#include "houseRanking.h"

HouseRanking::HouseRanking(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    //对应页面  https://y.qq.com/wk_v17/#/musicroom/toplist
    this->setFixedSize(820, 1690);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");

    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignRight);

    QJsonObject json_data = tools->toJson(":/resource/json/music_ranking.json");
    QJsonObject req_0 = json_data["req_0"].toObject();
    QJsonObject data = req_0["data"].toObject();
    group = data["group"].toArray();

    rankingTop();
    regional();
    feature();
    globa();
    widget->setLayout(layout);


}

void HouseRanking::rankingTop() {

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(widget->width() - 20, 678);
    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);


    QJsonObject group_obj = group.at(0).toObject();
    QJsonArray list = group_obj["toplist"].toArray();

    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString frontPicUrl = item_obj["frontPicUrl"].toString();
        QString musichallTitle = item_obj["musichallTitle"].toString();
        int listenNum = item_obj["listenNum"].toInt();
        QString listen_num = tools->toStrWan(listenNum);

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
        itemImg->setPixmap(tools->imgPixRadius(getImage(frontPicUrl), getImage(frontPicUrl)->size(), 20));
        itemImg->setFixedSize(150, 150);

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

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe841));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText(listen_num);
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
        title->setText(musichallTitle);
        title->setObjectName("blodTit");
        title->setFixedSize(rw, 30);
        rightListLayout->addWidget(title);
        rightListLayout->addSpacing(20);

        QJsonArray song_list = item_obj["song"].toArray();
        for (int j = 0; j < song_list.size(); ++j) {
            QJsonObject song_item = song_list.at(j).toObject();
            QString song_title = song_item["title"].toString();
            QString song_name = song_item["singerName"].toString();

            songItem[j] = new QLabel;
            QString txt = tools->textElps(song_title + "-" + song_name, rightListBox->width(), songItem[j]->font());
            songItem[j]->setText(txt);
            songItem[j]->setObjectName("songItem");
            rightListLayout->addWidget(songItem[j]);
            rightListLayout->addSpacing(10);
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
    layout->addSpacing(10);
}

// 地区榜
void HouseRanking::regional() {
    containerVBox = new QWidget(widget);
    containerVBox->setFixedSize(widget->width() - 20, 366);

    containerVLayout = new QVBoxLayout;
    containerVLayout->setSpacing(0);
    containerVLayout->setMargin(0);
    containerVLayout->setAlignment(Qt::AlignTop);
    containerVBox->setLayout(containerVLayout);

    QJsonObject group_obj = group.at(1).toObject();
    QString group_name = group_obj["groupName"].toString();
    QJsonArray list = group_obj["toplist"].toArray();

    title = new QLabel;
    title->setText(group_name);
    title->setObjectName("title");
    containerVLayout->addWidget(title);
    containerVLayout->addSpacing(20);

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(containerVBox->size());
    containerVLayout->addWidget(containerBox);

    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString frontPicUrl = item_obj["frontPicUrl"].toString();
        int listenNum = item_obj["listenNum"].toInt();
        QString listen_num = tools->toStrWan(listenNum);
        int regSize = (containerBox->width() / 5) - 20;
        regItem[i] = new QWidget;
        regItem[i]->installEventFilter(this);
        regItem[i]->setObjectName("regItem");
        regItem[i]->setFixedSize(regSize, regSize + 10);
        regItem[i]->setCursor(Qt::PointingHandCursor);

        contentLayout = new QHBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        regItem[i]->setLayout(contentLayout);

        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        itemImg->setObjectName("regImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(frontPicUrl), getImage(frontPicUrl)->size(), 20));
        itemImg->setFixedSize(regSize, regSize);

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

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe841));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText(listen_num);
        playCount->setFixedSize(playCount->sizeHint());
        playCount->setAlignment(Qt::AlignCenter);

        playCountLayout->addWidget(playSicon);
        playCountLayout->addSpacing(2);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width() + 26;
        playCountBox->setGeometry(itemImg->width() - sc - 10, itemImg->height() - 30, sc, 22);

        contentLayout->addWidget(itemImg);

        int r = floor(i / 5) + 1;
        int c = (i % 5) + 1;
        containerLayout->addWidget(regItem[i], r, c);
        containerLayout->setSpacing(20);
    }
    layout->addSpacing(10);
    layout->addWidget(containerVBox);
    layout->addSpacing(10);
}

// 特色榜
void HouseRanking::feature() {
    containerVBox = new QWidget(widget);
    containerVBox->setFixedSize(widget->width() - 20, 376);

    containerVLayout = new QVBoxLayout;
    containerVLayout->setSpacing(0);
    containerVLayout->setMargin(0);
    containerVLayout->setAlignment(Qt::AlignTop);
    containerVBox->setLayout(containerVLayout);

    QJsonObject group_obj = group.at(2).toObject();
    QString group_name = group_obj["groupName"].toString();
    QJsonArray list = group_obj["toplist"].toArray();

    title = new QLabel;
    title->setText(group_name);
    title->setObjectName("title");
    containerVLayout->addWidget(title);
    containerVLayout->addSpacing(20);

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(containerVBox->size());
    containerVLayout->addWidget(containerBox);

    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString frontPicUrl = item_obj["frontPicUrl"].toString();
        int listenNum = item_obj["listenNum"].toInt();
        QString listen_num = tools->toStrWan(listenNum);
        int regSize = (containerBox->width() / 5) - 20;
        feaItem[i] = new QWidget;
        feaItem[i]->installEventFilter(this);
        feaItem[i]->setObjectName("feaItem");
        feaItem[i]->setFixedSize(regSize, regSize + 10);
        feaItem[i]->setCursor(Qt::PointingHandCursor);

        contentLayout = new QHBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        feaItem[i]->setLayout(contentLayout);

        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        itemImg->setObjectName("feaImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(frontPicUrl), getImage(frontPicUrl)->size(), 20));
        itemImg->setFixedSize(regSize, regSize);

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

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe841));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText(listen_num);
        playCount->setFixedSize(playCount->sizeHint());
        playCount->setAlignment(Qt::AlignCenter);

        playCountLayout->addWidget(playSicon);
        playCountLayout->addSpacing(2);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width() + 26;
        playCountBox->setGeometry(itemImg->width() - sc - 10, itemImg->height() - 30, sc, 22);

        contentLayout->addWidget(itemImg);

        int r = floor(i / 5) + 1;
        int c = (i % 5) + 1;
        containerLayout->addWidget(feaItem[i], r, c);
        containerLayout->setSpacing(20);
    }
    layout->addSpacing(10);
    layout->addWidget(containerVBox);
    layout->addSpacing(10);
}

// 全球榜
void HouseRanking::globa() {
    containerVBox = new QWidget(widget);
    containerVBox->setFixedSize(widget->width() - 20, 202);

    containerVLayout = new QVBoxLayout;
    containerVLayout->setSpacing(0);
    containerVLayout->setMargin(0);
    containerVLayout->setAlignment(Qt::AlignTop);
    containerVBox->setLayout(containerVLayout);

    QJsonObject group_obj = group.at(3).toObject();
    QString group_name = group_obj["groupName"].toString();
    QJsonArray list = group_obj["toplist"].toArray();

    title = new QLabel;
    title->setText(group_name);
    title->setObjectName("title");
    containerVLayout->addWidget(title);
    containerVLayout->addSpacing(20);

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(containerVBox->size());
    containerVLayout->addWidget(containerBox);

    containerHLayout = new QHBoxLayout;
    containerHLayout->setSpacing(0);
    containerHLayout->setMargin(0);
    containerHLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerHLayout);

    for (int i = 0; i < list.size(); ++i) {
        QJsonObject item_obj = list.at(i).toObject();
        QString frontPicUrl = item_obj["frontPicUrl"].toString();
        int listenNum = item_obj["listenNum"].toInt();
        QString listen_num = tools->toStrWan(listenNum);
        int regSize = (containerBox->width() / 5) - 20;
        globItem[i] = new QWidget;
        globItem[i]->installEventFilter(this);
        globItem[i]->setObjectName("globItem");
        globItem[i]->setFixedSize(regSize, regSize + 10);
        globItem[i]->setCursor(Qt::PointingHandCursor);

        contentLayout = new QHBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        globItem[i]->setLayout(contentLayout);

        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        itemImg->setObjectName("globImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(frontPicUrl), getImage(frontPicUrl)->size(), 20));
        itemImg->setFixedSize(regSize, regSize);

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

        playSicon = new QLabel;
        playSicon->setFixedSize(18, 14);
        playSicon->setObjectName("playSicon");
        playSicon->setFont(tools->aliIcon());
        playSicon->setText(QChar(0xe841));
        playSicon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        playCount = new QLabel;
        playCount->setObjectName("playCount");
        playCount->setText(listen_num);
        playCount->setFixedSize(playCount->sizeHint());
        playCount->setAlignment(Qt::AlignCenter);

        playCountLayout->addWidget(playSicon);
        playCountLayout->addSpacing(2);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width() + 26;
        playCountBox->setGeometry(itemImg->width() - sc - 10, itemImg->height() - 30, sc, 22);

        contentLayout->addWidget(itemImg);

        containerHLayout->addWidget(globItem[i]);
        containerHLayout->setSpacing(20);
    }
    layout->addSpacing(10);
    layout->addWidget(containerVBox);
    layout->addSpacing(10);
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
void HouseRanking::toggleTopItem(QWidget *itemBox, QString objName, QEvent *e) {
    QLabel *box = itemBox->findChild<QLabel *>(objName);
    QWidget *mask = itemBox->findChild<QWidget *>("maskBox");
    QLabel *play_box = itemBox->findChild<QLabel *>("playBox");
    QWidget *play_count = itemBox->findChild<QWidget *>("playCountBox");

    if (e->type() == QEvent::Enter) {
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

void HouseRanking::toggleItem(QWidget *itemBox, QString objName, QEvent *e) {
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


bool HouseRanking::eventFilter(QObject *o, QEvent *e) {

    if (o->objectName() == "itemImg") {
        int i = o->property("index").toInt();
        toggleTopItem(item[i], "itemImg", e);
    }
    if (o->objectName() == "regImg") {
        int i = o->property("index").toInt();
        toggleItem(regItem[i], "regImg", e);
    }
    if (o->objectName() == "feaImg") {
        int i = o->property("index").toInt();
        toggleItem(feaItem[i], "feaImg", e);
    }
    if (o->objectName() == "globImg") {
        int i = o->property("index").toInt();
        toggleItem(globItem[i], "globImg", e);
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