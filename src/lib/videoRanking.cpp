//
// Created by dinglong on 2024/4/17 下午 09:08
//

#include "videoRanking.h"

VideoRanking::VideoRanking(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    //对应页面  https://y.qq.com/wk_v17/#/mv/toplist
    this->setFixedSize(820, 1690);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");

    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    rankingTop();
    rankList();
    widget->setLayout(layout);


}

void VideoRanking::rankingTop() {

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(widget->width() - 80, 170);
    containerLayout = new QHBoxLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);


    QString mv_url = "https://y.qq.com/music/common/upload/iphone_order_channel/20150127163830.jpg";
    itemImg = new QLabel;
    itemImg->setScaledContents(true);
    itemImg->setObjectName("topImg");
    itemImg->installEventFilter(this);
    // 先提取网络图片 再处理圆角 Tools
    itemImg->setPixmap(tools->imgPixRadius(getImage(mv_url), getImage(mv_url)->size(), 20));
    itemImg->setFixedSize(170, 170);


    rightLayout = new QVBoxLayout;
    rightLayout->setMargin(0);
    rightLayout->setSpacing(0);
    rightLayout->setAlignment(Qt::AlignTop);
    rightBox = new QWidget;
    rightBox->setLayout(rightLayout);

    title = new QLabel;
    title->setText("巅峰榜.MV");
    title->setObjectName("blodTit");
    rightLayout->addWidget(title);
    rightLayout->addSpacing(26);

    dateTit = new QLabel;
    dateTit->setText("04.15-05.26");
    dateTit->setObjectName("dateTit");
    rightLayout->addWidget(dateTit);

    containerLayout->addWidget(itemImg);
    containerLayout->addSpacing(25);
    containerLayout->addWidget(rightBox);

    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(40);
}

// 排行榜列表
void VideoRanking::rankList() {
    containerBox = new QWidget(widget);
    containerBox->setFixedSize(widget->width() - 80, 1000);
    containerVLayout = new QVBoxLayout;
    containerVLayout->setSpacing(0);
    containerVLayout->setMargin(0);
    containerVLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerVLayout);

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
            << "https://y.qq.com/music/photo_new/T003R300x300M0000013o4V60ch0es.jpg";
    for (int i = 0; i < imgList.size(); ++i) {
        contentLayout = new QHBoxLayout;
        contentLayout->setAlignment(Qt::AlignLeft);
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);

        item[i] = new QWidget;
        item[i]->setFixedHeight(80);
        item[i]->setObjectName("item");
        item[i]->setLayout(contentLayout);



        QPixmap sortPix(":/resource/images/sort.png");
        sort = new QLabel;
        sort->setFixedSize(18,20);
        num = new QLabel(sort);
        if(i < 3){
            sort->setPixmap(sortPix);
            num->setObjectName("bg_title");
        }else{
            num->setObjectName("title");
        }
        sort->setScaledContents(true);
        num->setFixedSize(sort->size());
        num->setAlignment(Qt::AlignCenter);
        num->setText(QString::number(i+1));


        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setObjectName("itemImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 20));
        itemImg->setFixedSize(142, item[i]->height());

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


        rightLayout = new QVBoxLayout;
        rightLayout->setMargin(0);
        rightLayout->setSpacing(0);
        rightLayout->setAlignment(Qt::AlignVCenter);
        rightBox = new QWidget;
        rightBox->setLayout(rightLayout);

        QStringList slist = {"缘故-贺均分", "蜃楼-周深", "发布时间：2024-05-16"};
        for (int j = 0; j < slist.size(); ++j) {
            songItem[j] = new QLabel;
            songItem[j]->setText(slist[j]);
            if(j > 1){
                songItem[j]->setObjectName("dateItem");
            }else{
                songItem[j]->setObjectName("songItem");
                songItem[j]->setCursor(Qt::PointingHandCursor);
                songItem[j]->setFixedSize(songItem[j]->sizeHint());
            }
            rightLayout->addWidget(songItem[j]);
            rightLayout->addSpacing(5);
        }


        contentLayout->addWidget(sort);
        contentLayout->addSpacing(40);
        contentLayout->addWidget(itemImg);
        contentLayout->addSpacing(20);
        contentLayout->addWidget(rightBox);

        containerVLayout->addWidget(item[i]);
        containerVLayout->setSpacing(30);
    }
    layout->addWidget(containerBox);
}

QPixmap *VideoRanking::getImage(QString url) {
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

void VideoRanking::toggleItem(QWidget *itemBox, QString objName, QEvent *e) {
    QWidget *mask = itemBox->findChild<QWidget *>("maskBox");
    QLabel *play_box = itemBox->findChild<QLabel *>("playBox");
    if (e->type() == QEvent::Enter) {
        if (play_box) {
            play_box->setVisible(true);
        }
        if (mask) {
            mask->setVisible(true);
        }
    }
    if (e->type() == QEvent::Leave) {
        if (play_box) {
            play_box->setVisible(false);
        }
        if (mask) {
            mask->setVisible(false);
        }
    }
}


bool VideoRanking::eventFilter(QObject *o, QEvent *e) {
    if (o->objectName() == "itemImg") {
        int i = o->property("index").toInt();
        toggleItem(item[i], "itemImg", e);
    }

    return QWidget::eventFilter(o, e);

}

void VideoRanking::loadQSS() {
    QFile qss(":/resource/qss/videoRanking.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}