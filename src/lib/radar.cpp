//
// Created by dinglong on 2024/4/18 18:58
//

#include "radar.h"

Radar::Radar(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    //对应页面  https://y.qq.com/wk_v17/radio.html
    this->setFixedSize(820, 500);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, this->width(), this->height());
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);


    radarTop();
    radarList();
    widget->setLayout(layout);
}
void Radar::radarTop() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(widget->width() - 80);
    contentLayout = new QVBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(contentLayout);

    title = new QLabel;
    title->setObjectName("blodTit");
    title->setText("全部分类");

    typeBox = new QWidget;
    typeOutLayout = new QHBoxLayout;
    typeOutLayout->setSpacing(0);
    typeOutLayout->setMargin(0);
    typeOutLayout->setAlignment(Qt::AlignTop);
    typeBox->setLayout(typeOutLayout);

    QList<QString> txtList;
    txtList << "热门" << "心情" << "主题" << "场景" << "曲风" << "语言" << "人群" << "乐器" << "陪你听" << "厂牌";
    for (int i = 0; i < txtList.size(); ++i) {
        typeItem[i] = new QWidget;
        typeItem[i]->installEventFilter(this);
        typeItem[i]->setFixedWidth(44);
        typeItem[i]->setCursor(Qt::PointingHandCursor);
//        typeItem[i]->setStyleSheet("background:#f0f");

        typeLayout = new QVBoxLayout;
        typeLayout->setSpacing(0);
        typeLayout->setMargin(0);
        typeLayout->setAlignment(Qt::AlignCenter);
        typeItem[i]->setLayout(typeLayout);

        typeTxt = new QLabel;
        typeTxt->setObjectName("typeTit");
        typeTxt->setText(txtList[i]);

        bot = new QLabel;
        bot->setFixedSize(8,8);
        bot->setObjectName("bot");


        typeLayout->addWidget(typeTxt);
        typeLayout->addSpacing(10);
        typeLayout->addWidget(bot,0,Qt::AlignHCenter);

        typeOutLayout->addWidget(typeItem[i]);
        typeOutLayout->setSpacing(20);
    }
    contentLayout->addWidget(title);
    contentLayout->addWidget(typeBox);


    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
};

void Radar::radarList() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(widget->width() - 20);
    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://y.qq.com/music/photo_new/T001R300x300M0000025NhlN2yWrP4.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000003fA5G40k6hKc.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000001BLpXF2DyJe2.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000002J4UUk29y8BY.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000003Nz2So3XXYek.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000001fNHEf1SFEFN.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000002azErJ0UcDN6.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000001z2JmX09LLgL.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000001BHDR33FZVZ0.webp"
            << "https://y.qq.com/music/photo_new/T001R300x300M000000IBYF50SRnXP.webp";
    for (int i = 0; i < imgList.size(); ++i) {
        int size = (containerBox->width() / 4) - 20;
        item[i] = new QWidget;
        item[i]->installEventFilter(this);
        item[i]->setFixedWidth(size);
        item[i]->setCursor(Qt::PointingHandCursor);

        contentLayout = new QVBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        contentLayout->setAlignment(Qt::AlignTop);
        item[i]->setLayout(contentLayout);

        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), size));
        itemImg->setFixedSize(size, size);
        contentLayout->addWidget(itemImg);
        contentLayout->addSpacing(16);

        singerName = new QLabel;
        singerName->setObjectName("singerName");
        singerName->setText("周杰伦");
        contentLayout->addWidget(singerName,0,Qt::AlignHCenter);

        int r = floor(i / 4) + 1;
        int c = (i % 4) + 1;
        containerLayout->addWidget(item[i], r, c);
        containerLayout->setSpacing(20);
        containerLayout->setVerticalSpacing(30);
    }
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
};

QPixmap *Radar::getImage(QString url) {
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

void Radar::loadQSS() {
    QFile qss(":/resource/qss/radar.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}