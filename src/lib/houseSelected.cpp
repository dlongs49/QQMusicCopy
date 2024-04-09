//
// Created by dinglong on 2024/4/6 下午 02:49
//

#include "houseSelected.h"

HouseSelected::HouseSelected(QWidget *parent) : QWidget(parent) {
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

    handleMenu = new HandleMenu(scrollArea);
    songInfo = new SongInfo(scrollArea);

    RecommTops();
    widget->setLayout(layout);


}
void HouseSelected::RecommTops() {

    containerBox = new QWidget(widget);
    containerBox->setFixedSize(widget->width(), 230);
    containerBox->installEventFilter(this);
    containerBox->setObjectName("selectedBox");


    contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);
    contentLayout->setAlignment(Qt::AlignTop);
    containerBox->setLayout(contentLayout);

    scrollBox = new QWidget(containerBox);
    scrollBox->setFixedSize(containerBox->width() - 60, containerBox->height());
    scrollBox->setObjectName("recomScrollBox");

    bannerLayout = new QHBoxLayout;
    bannerLayout->setSpacing(0);
    bannerLayout->setMargin(0);
    bannerLayout->setAlignment(Qt::AlignLeft);

    bannerBox = new QWidget(scrollBox);
    bannerBox->setLayout(bannerLayout);
    animation[0] = new QPropertyAnimation(bannerBox, "geometry");
    animation[0]->setDuration(300);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6483999.jpg"
            << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6484203.jpg"
            << "https://y.qq.com/music/common/upload/ocs/2681676c054da54091a9f000208e81bf.png"
            << "https://y.qq.com/music/common/upload/MUSIC_FOCUS/6482174.jpg";
    for (int i = 0; i < imgList.size(); ++i) {
        bannerItem[i] = new QWidget;
        bannerItem[i] -> installEventFilter(this);
        bannerItem[i]->setFixedSize(240,178);
        bannerImgLayout = new QVBoxLayout;
        bannerImgLayout->setSpacing(0);
        bannerImgLayout->setMargin(0);
        bannerImgLayout->setAlignment(Qt::AlignTop);

        bannerImg = new QLabel(bannerItem[i]);
        bannerImg->setCursor(Qt::PointingHandCursor);
        bannerImg->setScaledContents(true);
        bannerImg->setObjectName("bannerImg");
        bannerImg->setProperty("index", i);
        bannerImg->installEventFilter(this);
        // 先提取网络图片 再处理圆角 Tools
        bannerImg->setPixmap(tools->imgPixRadius(getImage(imgList[i]), getImage(imgList[i])->size(), 6));
        bannerImg->setFixedSize(240, 178);

        bomBox = new QWidget(bannerImg);
        bomBox->setGeometry(0,bannerImg->height()-40,bannerImg->width(),40);
        bomLayout = new QHBoxLayout;
        bomLayout->setAlignment(Qt::AlignBottom);
        bomBox->setLayout(bomLayout);

        tagLabel = new QLabel;
        tagLabel->setObjectName("tagLabel");
        tagLabel->setText("音乐人");
        tagLabel->setFixedSize(tagLabel->sizeHint().width()+5,tagLabel->sizeHint().height());

        titleLabel = new QLabel;
        QString txt = tools->textElps("贺峻霖全新单曲《缘故》正式上线 ", 150, titleLabel->font());
        titleLabel->setText(txt);
        titleLabel->setObjectName("titleLabel");

        bomLayout->addWidget(tagLabel);
        bomLayout->addWidget(titleLabel);

        bannerImgLayout->addWidget(bannerImg);
        bannerItem[i]->setLayout(bannerImgLayout);
        bannerLayout->addWidget(bannerItem[i]);
        if (i != imgList.size() - 1) {
            bannerLayout->addSpacing(20);
        }
    }

    contentLayout->addWidget(arrowBox(0, "left"));
    contentLayout->addWidget(scrollBox);
    contentLayout->addWidget(arrowBox(0, "right"));
    layout->addSpacing(10);
    layout->addWidget(containerBox);
    layout->addSpacing(30);
}



QPixmap *HouseSelected::getImage(QString url) {
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

// 左右箭头部件
QLabel *HouseSelected::arrowBox(int i, QString type) {
    if (type == "left") {
        QLabel *leftArrow = new QLabel;
        leftArrow->setObjectName("leftArrow" + QString::number(i));
        leftArrow->setProperty("class", "leftArrow");
        leftArrow->installEventFilter(this);
        leftArrow->setFixedSize(30, 38);
        leftArrow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        leftArrow->setCursor(Qt::PointingHandCursor);
        leftArrow->setFont(tools->aliIcon());
        leftArrow->setText(QChar(0xea84));
        leftArrow->setVisible(false);
        QSizePolicy policy_lf = leftArrow->sizePolicy();
        policy_lf.setRetainSizeWhenHidden(true);
        leftArrow->setSizePolicy(policy_lf);
        return leftArrow;
    }
    if (type == "right") {
        QLabel *rightArrow = new QLabel;
        rightArrow->setObjectName("rightArrow" + QString::number(i));
        rightArrow->setProperty("class", "rightArrow");
        rightArrow->installEventFilter(this);
        rightArrow->setFixedSize(30, 38);
        rightArrow->setCursor(Qt::PointingHandCursor);
        rightArrow->setFont(tools->aliIcon());
        rightArrow->setText(QChar(0xe63e));
        rightArrow->setVisible(false);
        QSizePolicy policy = rightArrow->sizePolicy();
        policy.setRetainSizeWhenHidden(true);
        rightArrow->setSizePolicy(policy);
        return rightArrow;
    }
}

// 左右箭头切换隐藏
void HouseSelected::showArrow(QObject *o, QEvent *e, int i) {
    QLabel *leftArrow = o->findChild<QLabel *>("leftArrow" + QString::number(i));
    QLabel *rightArrow = o->findChild<QLabel *>("rightArrow" + QString::number(i));
    if (e->type() == QEvent::Enter) {
        if (leftArrow != NULL && rightArrow != NULL) {
            leftArrow->setVisible(true);
            rightArrow->setVisible(true);
        }
    }
    if (e->type() == QEvent::Leave) {
        if (leftArrow != NULL && rightArrow != NULL) {
            leftArrow->setVisible(false);
            rightArrow->setVisible(false);
        }
    }
}


bool HouseSelected::eventFilter(QObject *o, QEvent *e) {
    // 左右箭头交互
    if (o->objectName() == "selectedBox") {
        showArrow(o, e, 0);
    }
}
void HouseSelected::loadQSS() {
    QFile qss(":/resource/qss/houseSelected.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}