//
// Created by dinglong on 2024/4/13 12:22
//

#include "houseSinger.h"

HouseSinger::HouseSinger(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();
    // 更多qq音乐客户端对应的页面 https://y.qq.com/m/client/config/url.pc.json?pcachetime=1712844941
    //对应的qq页面  https://y.qq.com/wk_v17/#/musicroom/recommend
    this->setFixedSize(820, 1400);
    widget = new QWidget(this);
    widget->setFixedSize(this->size());
    widget->setObjectName("conbox");
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(0);
    layout->setMargin(0);

    singerTop();
    singerList();
    widget->setLayout(layout);
}

void HouseSinger::singerTop() {
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
        containerLayout->addWidget(singerItem[i], r, c);
        containerLayout->setSpacing(20);
        containerLayout->setVerticalSpacing(30);
    }
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
};

void HouseSinger::singerList() {
    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(widget->width() - 20);
    containerLayout = new QGridLayout;
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(containerLayout);

    QList<QString> txtList;
    txtList << "李荣浩" << "韦礼安" << "张碧晨" << "陶喆" << "许嵩" << "赵雷" << "蔡健雅" << "BABYMONSTER"
            << "张韶涵" << "王力宏" << "希林娜依高" << "郭顶" << "BEYOND" << "Taylor Swift (泰勒·斯威夫特)" << "孙燕姿" << "程响"
            << "五月天" << "周传雄" << "王菲" << "告五人" << "徐佳莹" << "张靓颖" << "黄丽玲" << "单依纯" << "方大同" << "张学友"
            << "梁静茹" << "任然" << "胡彦斌" << "凤凰传奇" << "王杰" << "孙楠" << "王靖雯" << "莫文蔚" << "潘玮柏" << "葛东琪"
            << "任素汐" << "王心凌" << "陈粒" << "杨丞琳" << "蔡依林" << "许巍" << "BIGBANG (빅뱅)" << "张信哲" << "EXO (엑소)"
            << "杨宗纬" << "田馥甄" << "刘若英" << "BLACKPINK (블랙핑크)" << "颜人中" << "伍佰 & China Blue";
    for (int i = 0; i < txtList.size(); ++i) {
        int size = (containerBox->width() / 4) - 20;
        item[i] = new QWidget;
        item[i]->installEventFilter(this);
        item[i]->setFixedWidth(size);
        item[i]->setCursor(Qt::PointingHandCursor);

        itemLayout = new QHBoxLayout;
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);
        item[i]->setLayout(itemLayout);

        singerName = new QLabel;
        singerName->setObjectName("singerName");
        QString txt = tools->textElps(txtList[i], size-20, singerName->font());
        singerName->setText(txt);
        itemLayout->addWidget(singerName,0,Qt::AlignHCenter);


        int r = floor(i / 4) + 1;
        int c = (i % 4) + 1;
        containerLayout->addWidget(item[i], r, c);
        containerLayout->setSpacing(14);
        containerLayout->setVerticalSpacing(30);
    }
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(10);
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