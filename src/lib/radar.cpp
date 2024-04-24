//
// Created by dinglong on 2024/4/18 18:58
//

#include <QCoreApplication>
#include "radar.h"

Radar::Radar(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    //对应页面  https://y.qq.com/wk_v17/radio.html
    this->setFixedSize(820, 500);
    widget = new QWidget(this);
    widget->setFixedWidth(this->size().width());
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

    QFile file(":/resource/json/radar.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "读取json失败";
        return;
    }
    QByteArray dataByte(file.readAll());
    file.close();

    QJsonParseError jError;
    QJsonDocument json_doc = QJsonDocument::fromJson(dataByte, &jError);

    QJsonObject obj = json_doc.object();
    QJsonObject req_0 = obj["req_0"].toObject();
    QJsonObject data = req_0["data"].toObject();
    navList = data["radio_list"].toArray();
    QJsonObject firstItem = navList.at(0).toObject();
    radarList = firstItem["list"].toArray();


    radarTop();
    radarListCon();
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

    for (int i = 0; i < navList.size(); ++i) {
        QJsonObject nav_item = navList.at(i).toObject();
        QString title_txt = nav_item["title"].toString();
        typeItem[i] = new QWidget;
        typeItem[i]->installEventFilter(this);
        typeItem[i]->setFixedWidth(44);
        typeItem[i]->setCursor(Qt::PointingHandCursor);
        typeItem[i]->setObjectName("nav_item");
        typeItem[i]->setProperty("n_idx", i);

        typeLayout = new QVBoxLayout;
        typeLayout->setSpacing(0);
        typeLayout->setMargin(0);
        typeLayout->setAlignment(Qt::AlignCenter);
        typeItem[i]->setLayout(typeLayout);

        typeTxt = new QLabel;
        if(i == 0){
            typeTxt->setProperty("class", "active");
        }else{
            typeTxt->setProperty("class", "");
        }
        typeTxt->setObjectName("typeTit");
        typeTxt->setText(title_txt);

        bot = new QLabel;
        bot->setFixedSize(8, 8);
        if(i == 0){
            bot->setProperty("class", "bot_active");
        }else{
            bot->setProperty("class", "bot");
        }
        bot->setObjectName("bot");


        typeLayout->addWidget(typeTxt);
        typeLayout->addSpacing(10);
        typeLayout->addWidget(bot, 0, Qt::AlignHCenter);

        typeOutLayout->addWidget(typeItem[i]);
        typeOutLayout->setSpacing(20);
    }
    contentLayout->addWidget(title);
    contentLayout->addSpacing(14);
    contentLayout->addWidget(typeBox);


    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(20);
};

void Radar::radarListCon() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(widget->width() - 80);
    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    forList();
};

void Radar::forList() {
    int cl = ceil((double) radarList.size() / 6);
    for (int i = 0; i < radarList.size(); ++i) {
        int size = (containerBox->width() / 6) - 12;
        item[i] = new QWidget;
        item[i]->installEventFilter(this);
        item[i]->setFixedSize(size, 140);

        contentLayout = new QVBoxLayout;
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
        contentLayout->setAlignment(Qt::AlignTop);
        item[i]->setLayout(contentLayout);

        itemImg = new QLabel;
        itemImg->setObjectName("itemImg");
        itemImg->setProperty("index", i);
        itemImg->installEventFilter(this);
        itemImg->setCursor(Qt::PointingHandCursor);
        itemImg->setScaledContents(true);
        //获取数组索引的图片 先提取网络图片 再处理圆角 Tools
        QJsonObject radar_item = radarList.at(i).toObject();
        QString img_url = radar_item["pic_url"].toString();
        itemImg->setPixmap(tools->imgPixRadius(getImage(img_url), getImage(img_url)->size(), size * 2));
        itemImg->setFixedSize(size, size);

        contentLayout->addWidget(itemImg);
        contentLayout->addSpacing(16);

        playBox = new QLabel(itemImg);
        playBox->setFixedSize(36, 36);
        playBox->setObjectName("playBox");
        playBox->setFont(tools->aliIcon());
        playBox->setText(QChar(0xe87c));
        playBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        int p_w = (itemImg->width() / 2) - (playBox->width() / 2);
        int p_h = (itemImg->height() / 2) - (playBox->height() / 2);
        playBox->move(p_w, p_h);
        playBox->setVisible(false);


        singerName = new QLabel;
        singerName->setObjectName("singerName");
        QString bom_tit = radar_item["title"].toString();
        singerName->setText(bom_tit);
        contentLayout->addWidget(singerName, 0, Qt::AlignHCenter);

        int r = floor(i / 6) + 1;
        int c = (i % 6) + 1;
        containerLayout->addWidget(item[i], r, c);
        containerLayout->setSpacing(20);
        containerLayout->setVerticalSpacing(20);
    }
    int hh = (item[0]->height() + 20) * cl;
    qDebug() << hh;
    containerBox->setFixedHeight(hh);
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
    widget->setFixedHeight(hh + 120);
}

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

bool Radar::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *) e;
        if (mouseEvent->button() == Qt::LeftButton) {
            if (o->objectName() == "nav_item") {
                int i = o->property("n_idx").toInt();
                QLabel *t_tit = o->findChild<QLabel *>("typeTit");
                QLabel *t_bot = o->findChild<QLabel *>("bot");
                for (int y = 0; y < navList.size(); ++y) {
                    QLabel *t_tits = typeItem[y]->findChild<QLabel *>("typeTit");
                    QLabel *t_bots = typeItem[y]->findChild<QLabel *>("bot");
                    if (t_tits) {
                        t_tits->setProperty("class", "");
                        t_tits->style()->polish(t_tits);
                    }
                    if (t_bots) {
                        t_bots->setProperty("class", "bot");
                        t_bots->style()->polish(t_bots);
                    }

                }
                t_tit->setProperty("class", "active");
                t_bot->setProperty("class", "bot_active");
                t_tit->style()->polish(t_tit);
                t_bot->style()->polish(t_bot);
//                for (int j = 0; j < radarList.size(); ++j) {
//                    delete item[j];
//                }
//                QJsonObject objList = navList.at(i).toObject();
//                radarList = objList["list"].toArray();
//
//                forList();
            }
        }
    }


    if (o->objectName() == "itemImg") {
        int i = o->property("index").toInt();
        QLabel *play_box = item[i]->findChild<QLabel *>("playBox");
        if (e->type() == QEvent::Enter) {
            play_box->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            play_box->setVisible(false);
        }
    }

    return QWidget::eventFilter(o, e);

}

void Radar::loadQSS() {
    QFile qss(":/resource/qss/radar.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}