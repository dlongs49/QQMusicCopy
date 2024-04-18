//
// Created by dinglong on 2024/4/18 14:54
//

#include "videoLibrary.h"
VideoLibrary::VideoLibrary(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    // 页面  https://y.qq.com/wk_v17/#/mv/list

    this->setFixedSize(820, 1700);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
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
    areaBox = new QWidget(containerBox);
    areaBox->setLayout(areaLayout);

    QStringList areaList = {"全部", "内地","港台","欧美","韩国","日本"};
    for (int i = 0; i < areaList.size(); ++i) {
        areaLabel[i] = new QLabel;
        areaLabel[i]->installEventFilter(this);
        areaLabel[i]->setAlignment(Qt::AlignCenter);
        areaLabel[i]->setFixedSize(nav_w,nav_h);
        areaLabel[i]->setCursor(Qt::PointingHandCursor);
        areaLabel[i]->setText(areaList[i]);
        areaLabel[i]->setObjectName("navItem");
        areaLayout->addWidget(areaLabel[i]);
        areaLayout->addSpacing(30);
    }

    distLayout = new QHBoxLayout;
    distLayout->setSpacing(0);
    distLayout->setMargin(0);
    distLayout->setAlignment(Qt::AlignLeft);
    distBox = new QWidget(containerBox);
    distBox->setLayout(distLayout);

    QStringList distList = {"全部", "MV","现场","翻唱","舞蹈","影视","综艺","儿歌"};
    for (int i = 0; i < distList.size(); ++i) {
        distLabel[i] = new QLabel;
        distLabel[i]->installEventFilter(this);
        distLabel[i]->setAlignment(Qt::AlignCenter);
        distLabel[i]->setFixedSize(nav_w,nav_h);
        distLabel[i]->setCursor(Qt::PointingHandCursor);
        distLabel[i]->setText(distList[i]);
        distLabel[i]->setObjectName("navItem");
        distLayout->addWidget(distLabel[i]);
        distLayout->addSpacing(30);
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

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QfX3MU2dzluKMUOBEjz0h6g/300"
            << "https://qpic.y.qq.com/music_cover/MKjEtF7diatibd6B0iaeF5Kgn7iblB0nh85QY8gA4UrJxhxQ9BBHZHDyFQ/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqojSibubibse2uIWSaZhZ39n1F1CQCXVuMGdw/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqoglWn5x5ITgE8KljTdMrDCyBpia0Jkn6BDg/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqoglWn5x5ITgE8KljTdMrDCyBpia0Jkn6BDg/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqoglWn5x5ITgE8KljTdMrDCyBpia0Jkn6BDg/300?n=1"
            << "https://qpic.y.qq.com/music_cover/ib2uYYJVhia5TeO7z67ehqoglWn5x5ITgE8KljTdMrDCyBpia0Jkn6BDg/300?n=1"
            << "https://qpic.y.qq.com/music_cover/I2ZdwiaF8XY3CVB1y18cmH6dVjiaC6hprhowF1emvMrTFIxCibB04GH5A/300?n=1"
            << "https://qpic.y.qq.com/music_cover/I2ZdwiaF8XY3CVB1y18cmH6dVjiaC6hprhowF1emvMrTFIxCibB04GH5A/300?n=1"
            << "https://qpic.y.qq.com/music_cover/4pmnRu5sL5QbtO8OS8NKJTN5qBpjx5XMS8vhm4hcZSN7PEHPQ68C0Q/300?n=1";
    int cl = ceil(imgList.size()/3);
    for (int i = 0; i < imgList.size(); ++i) {
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
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 12));

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
        QString txt = tools->textElps("贺峻霖全新单曲《缘故》正式上线正式上线正式上线 ", itemImg->width()-6, title->font());
        title->setText(txt);
        title->setAlignment(Qt::AlignTop);

        author = new QLabel;
        author->setCursor(Qt::PointingHandCursor);
        author->setObjectName("author");
        author->setText("弦子");
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
        int c = (i % cl) + 1;
        mvLayout->addWidget(mvItem[i],r,c);
        mvLayout->setSpacing(20);
    }
    contentBox->setFixedHeight(cl * 220);
    bannerBox->setFixedHeight(cl * 220);

    contentLayout->addWidget(bannerBox);
    layout->addWidget(containerBox);
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

