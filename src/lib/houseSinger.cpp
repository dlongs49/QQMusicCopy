//
// Created by dinglong on 2024/4/13 12:22
//

#include "houseSinger.h"

HouseSinger::HouseSinger(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    //对应页面  https://y.qq.com/wk_v17/#/musicroom/singer
    this->setFixedSize(820, 0);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    json_data = tools->toJson(":/resource/json/music_singer.json");

    singerList();
    widget->setLayout(layout);
}

void HouseSinger::singerList() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(widget->width() - 20);
    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    QJsonObject req_0 = json_data["req_0"].toObject();
    QJsonObject data = req_0["data"].toObject();
    QJsonArray list = data["singerlist"].toArray();
    int cl = ceil((double)list.size()/4);
   for (int i = 0; i < list.size(); ++i) {
       QJsonObject item_obj = list.at(i).toObject();
       QString singer_pic = item_obj["singer_pic"].toString();
       QString singer_name = item_obj["singer_name"].toString();
        int size = (containerBox->width() / 4) - 20;
        singerItem[i] = new QWidget;
        singerItem[i]->installEventFilter(this);
        singerItem[i]->setFixedWidth(size);
        singerItem[i]->setCursor(Qt::PointingHandCursor);

        contentLayout = new QVBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        contentLayout->setAlignment(Qt::AlignTop);
        singerItem[i]->setLayout(contentLayout);

        itemImg = new QLabel;
        itemImg->setScaledContents(true);
        // 先提取网络图片 再处理圆角 Tools
        itemImg->setPixmap(tools->imgPixRadius(getImage(singer_pic), getImage(singer_pic)->size(), size));
        itemImg->setFixedSize(size, size);
        contentLayout->addWidget(itemImg);
        contentLayout->addSpacing(16);

        singerName = new QLabel;
        singerName->setObjectName("singerName");
        singerName->setText(singer_name);
        contentLayout->addWidget(singerName, 0, Qt::AlignHCenter);

        int r = floor(i / 4) + 1;
        int c = (i % 4) + 1;
        containerLayout->addWidget(singerItem[i], r, c);
        containerLayout->setSpacing(20);
        containerLayout->setVerticalSpacing(30);
    }
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    int hh = 245*cl;
    this->setFixedHeight(hh);
    widget->setFixedHeight(hh);
};
QPixmap *HouseSinger::getImage(QString url) {
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

void HouseSinger::loadQSS() {
    QFile qss(":/resource/qss/houseSinger.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}