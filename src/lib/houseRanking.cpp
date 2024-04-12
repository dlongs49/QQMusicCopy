//
// Created by dinglong on 2024/4/10 17:04
//

#include "houseRanking.h"

HouseRanking::HouseRanking(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    // 更多qq音乐客户端对应的页面 https://y.qq.com/m/client/config/url.pc.json?pcachetime=1712844941
    //对应的qq页面  https://y.qq.com/wk_v17/#/musicroom/recommend
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
    containerBox->setFixedSize(widget->width() - 20, 678);

    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://y.qq.com/music/photo_new/T003R300x300M000003jPzHn4JkfK1.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000002MMbGH3LbfTS.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000001heSXA0sxaTY.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M0000011BU8d2iufia.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000002eYcg0312V98.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000004H76012Gkas2.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000003SSGWk0N4fI0.jpg";
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
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 20));
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
        int p_w = (itemImg->width()/2) - (playBox->width()/2);
        int p_h = (itemImg->height()/2) - (playBox->height()/2);
        playBox->move(p_w,p_h);
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
        title->setFixedSize(rw, 30);
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
            if (j == slist.size() - 1) {
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
    containerVBox = new QWidget(widget);
    containerVBox->setFixedSize(widget->width() - 20, 678);

    containerVLayout = new QVBoxLayout;
    containerVLayout->setSpacing(0);
    containerVLayout->setMargin(0);
    containerVLayout->setAlignment(Qt::AlignTop);
    containerVBox->setLayout(containerVLayout);

    title = new QLabel;
    title->setText("地区榜");
    title->setObjectName("title");
    containerVLayout->addWidget(title);
    containerVLayout->addSpacing(20);

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(containerVBox->width(), 678);

    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://y.qq.com/music/photo_new/T003R300x300M000000kyP0Y41mVgr.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000003CPSUH29Htzl.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000004IjbuM0yx0i2.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M0000041fyIo1W7VzR.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M00000084GsF3zkK62.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000001e2aJF1DYb74.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000003RpQin0xR8Sb.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M000001SRF6I0z2v3I.jpg"
            << "https://y.qq.com/music/photo_new/T003R300x300M0000013o4V60ch0es.jpg"
    for (int i = 0; i < imgList.size(); ++i) {
        int box_w = containerBox->width() / 5;
        int item_h  = 130;
        regItem[i] = new QWidget;
        regItem[i]->installEventFilter(this);
        regItem[i]->setObjectName("regItem");
        regItem[i]->setFixedSize(box_w - 20, item_h);
        regItem[i]->setCursor(Qt::PointingHandCursor);

        contentLayout = new QHBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        regItem[i]->setLayout(contentLayout);

        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        itemImg->setObjectName("itemImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 20));
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
        int p_w = (itemImg->width()/2) - (playBox->width()/2);
        int p_h = (itemImg->height()/2) - (playBox->height()/2);
        playBox->move(p_w,p_h);
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
        playCount->setText("203.6万");
        playCount->setFixedSize(playCount->sizeHint());
        playCount->setAlignment(Qt::AlignCenter);

        playCountLayout->addWidget(playSicon);
        playCountLayout->addSpacing(2);
        playCountLayout->addWidget(playCount);
        int sc = playCount->sizeHint().width() + 26;
        playCountBox->setGeometry(itemImg->width() - sc - 10, itemImg->height() - 30, sc, 22);

        contentLayout->addWidget(itemImg);

        int r = floor(i / 2) + 1;
        int c = (i % 2) + 1;
        containerLayout->addWidget(regItem[i], r, c);
        containerLayout->setSpacing(20);
    }
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
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


bool HouseRanking::eventFilter(QObject *o, QEvent *e) {

    if (o->objectName() == "itemImg") {
        int i = o->property("index").toInt();
        toggleItem(item[i], "itemImg", e);
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