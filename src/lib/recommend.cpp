//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"

Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    this->setFixedSize(820, 800);

    widget = new QWidget(this);
    widget->setObjectName("conbox");
    widget->setStyleSheet("QWidget#conbox{background:#fff}");
    widget->setFixedSize(820, 800);
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignRight);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0, 0, 820, 600);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(false);


    recomBox = new QWidget(widget);
    recomBox->installEventFilter(this);
    recomBox->setFixedWidth(810);
    recomBox->setFixedHeight(218);
    recomBox->setObjectName("recomBox");

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setFixedSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");

    recomConLayout = new QHBoxLayout;
    recomConLayout->setSpacing(0);
    recomConLayout->setMargin(0);
    recomConLayout->setAlignment(Qt::AlignLeft);

    recomConBox = new QWidget(recomScrollBox);
    recomConBox->setLayout(recomConLayout);
    moveAnimation = new QPropertyAnimation(recomConBox, "geometry");
    moveAnimation->setDuration(300);

    QList<QString> imgList;
    QList<QString> txtList;
    imgList << "http://y.qq.com/n3/wk_v20/entry/bg6.dab9cba46.png?max_age=2592000"
            << "https://y.gtimg.cn/music/photo_new/T002R300x300M000003MvqCa0Fq3Mq_2.jpg"
            << "http://y.qq.com/music/photo_new/T002R300x300M000000J15TK3Afzlb_5.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M0000008mjyX38ncsg_2.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000003ldyaV1pgN3M_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000000cpBaV2uDCBC_1.jpg?max_age=2592000"
            << "http://y.qq.com/music/photo_new/T002R300x300M000003yGUXR2isN9F_2.jpg?max_age=2592000";
    for (int i = 0; i < imgList.size(); ++i) {
        recomItemBox[i] = new QWidget(recomBox);
        if (i == 0) {
            recomItemBox[0]->setFixedWidth(356);
        } else {
            recomItemBox[i]->setFixedWidth(160);
        }
        recomItemLayout = new QVBoxLayout;
        recomItemLayout->setSpacing(0);
        recomItemLayout->setMargin(0);
        recomItemLayout->setAlignment(Qt::AlignTop);

        recomImgBox = new QLabel(recomItemBox[i]);
        recomImgBox->setCursor(Qt::PointingHandCursor);
        recomImgBox->setScaledContents(true);
        recomImgBox->setObjectName("recomImgBox");
        recomImgBox->setProperty("index", i);
        recomAttrList.append("recomImgBox" + QString::number(i));
        recomImgBox->installEventFilter(this);
        recomImgBox->setPixmap(getImage(imgList[i]));

        if (i == 0) {
            recomImgBox->setFixedSize(406, 160);

            guessLayout = new QVBoxLayout;
            guessLayout->setAlignment(Qt::AlignVCenter);
            guessTit = new QLabel;
            guessTit->setStyleSheet("font-size:20px");
            guessTit->setText("晚上好");
            guessSubTit = new QLabel;
            guessSubTit->setText("尝试来点音\n乐提提神吧");
            playBox = new QLabel;
            playBox->setFixedSize(40, 30);
            QPixmap playPix(":/resource/images/play.png");
            playBox->setPixmap(playPix);
            playBox->setScaledContents(true);
            guessLayout->addWidget(guessTit);
            guessLayout->addWidget(guessSubTit);
            guessLayout->addSpacing(5);
            guessLayout->addWidget(playBox);
            recomImgBox->setLayout(guessLayout);
        } else {
            recomImgBox->setFixedSize(160, 160);
            maskBox = new QWidget(recomImgBox);
            maskBox->setFixedSize(recomImgBox->width(), recomImgBox->height());
            maskBox->setObjectName("maskBox");
            maskBox->setVisible(false);

            playBox = new QLabel(recomImgBox);
            playBox->setObjectName("playBox");
            playBox->setVisible(false);
            playBox->setFixedSize(40, 30);
            QPixmap playPix(":/resource/images/play.png");
            playBox->setPixmap(playPix);
            playBox->setScaledContents(true);
            playBox->move(10, recomImgBox->height() - 40);
        }

        recomTit = new QLabel;
        recomTit->setCursor(Qt::PointingHandCursor);
        recomTit->setObjectName("recomTit");
        recomTit->setText("一生无悔-高安/杭娇");
        recomTit->setFixedSize(recomTit->sizeHint().width(), recomTit->sizeHint().height());
        recomSubTit = new QLabel;
        recomSubTit->setCursor(Qt::PointingHandCursor);
        recomSubTit->setObjectName("recomTit");
        recomSubTit->setText("每日三十首");
        recomSubTit->setFixedSize(recomSubTit->sizeHint().width(), recomSubTit->sizeHint().height());


        recomItemLayout->addSpacing(10);
        recomItemLayout->addWidget(recomImgBox);
        recomItemLayout->addSpacing(6);
        recomItemLayout->addWidget(recomTit);
        recomItemLayout->addSpacing(3);
        recomItemLayout->addWidget(recomSubTit);
        recomItemBox[i]->setLayout(recomItemLayout);
        recomConLayout->addWidget(recomItemBox[i]);
        if (i != imgList.size() - 1) {
            recomConLayout->addSpacing(20);
        }
    }

    leftArrow[0] = new QLabel;
    leftArrow[0]->setObjectName("leftArrow[0]");
    leftArrow[0]->installEventFilter(this);
    leftArrow[0]->setFixedSize(30, 38);
    leftArrow[0]->setCursor(Qt::PointingHandCursor);
    leftArrowPix[0] = new QPixmap;
    leftArrowPix[0]->load(":/resource/images/br_lf_arrow.png");
    leftArrow[0]->setPixmap(*leftArrowPix[0]);
    leftArrow[0]->setScaledContents(true);
    leftArrow[0]->setVisible(false);
    QSizePolicy policy_lf = leftArrow[0]->sizePolicy();
    policy_lf.setRetainSizeWhenHidden(true);
    leftArrow[0]->setSizePolicy(policy_lf);
    recomLayout->addWidget(leftArrow[0]);


    recomLayout->addWidget(recomScrollBox);

    rightArrow[0] = new QLabel;
    rightArrow[0]->setObjectName("rightArrow[0]");
    rightArrow[0]->installEventFilter(this);
    rightArrow[0]->setFixedSize(30, 38);
    rightArrow[0]->setCursor(Qt::PointingHandCursor);
    rightArrowPix[0] = new QPixmap;
    rightArrowPix[0]->load(":/resource/images/br_rh_arrow.png");
    rightArrow[0]->setPixmap(*rightArrowPix[0]);
    rightArrow[0]->setScaledContents(true);
    rightArrow[0]->setVisible(false);
    QSizePolicy policy = rightArrow[0]->sizePolicy();
    policy.setRetainSizeWhenHidden(true);
    rightArrow[0]->setSizePolicy(policy);
    recomLayout->addWidget(rightArrow[0]);


    layout->addWidget(recomBox);
    closeWidget = new QWidget(widget);
    closeWidget->setFixedSize(800, 200);
    closeWidget->setStyleSheet("background:#000");
    layout->addWidget(closeWidget);
    widget->setLayout(layout);

    tools = new Tools();

}

QPixmap Recommend::getImage(QString url) {
    manager = new QNetworkAccessManager;
    reply = manager->get(QNetworkRequest(QUrl(url)));
    loop = new QEventLoop();
    connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
    loop->exec();
    QByteArray imgData = reply->readAll();
    coverImg = new QPixmap;
    coverImg->loadFromData(imgData);
    return *coverImg;
}

bool Recommend::eventFilter(QObject *o, QEvent *e) {
    if (o->objectName() == "recomBox") {
        if (e->type() == QEvent::Enter) {
            leftArrow[0]->setVisible(true);
            rightArrow[0]->setVisible(true);
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[0]->setVisible(false);
            rightArrow[0]->setVisible(false);
        }
    }
    if (o->objectName() == "leftArrow[0]") {
        if (e->type() == QEvent::Enter) {
            leftArrow[0]->setPixmap(tools->hoverPixColor(leftArrowPix[0], "#31c27c"));
        }
        if (e->type() == QEvent::Leave) {
            leftArrow[0]->setPixmap(leftArrowImgPath);
        }
    }

    if (o->objectName() == "rightArrow[0]") {
        if (e->type() == QEvent::Enter) {
            rightArrow[0]->setPixmap(tools->hoverPixColor(rightArrowPix[0], "#31c27c"));
        }
        if (e->type() == QEvent::Leave) {
            rightArrow[0]->setPixmap(righArrowImgPath);
        }
    }

    if (o->objectName() == "recomImgBox") {
        int i = o->property("index").toInt();
        QLabel *box = recomItemBox[i]->findChild<QLabel *>("recomImgBox");
        QWidget *mask = recomItemBox[i]->findChild<QWidget *>("maskBox");
        QLabel *play_box = recomItemBox[i]->findChild<QLabel *>("playBox");
        animation = new QPropertyAnimation(box, "geometry");
        animation->setDuration(150);

        if (e->type() == QEvent::Enter) {
            animation->setStartValue(QRect(0, 10, box->width(), box->height()));
            animation->setEndValue(QRect(0, 0, box->width(), box->height()));
            animation->start();
            if (play_box) {
                play_box->setVisible(true);
                mask->setVisible(true);
            }
        }
        if (e->type() == QEvent::Leave) {
            animation->setStartValue(QRect(0, 0, box->width(), box->height()));
            animation->setEndValue(QRect(0, 10, box->width(), box->height()));
            animation->start();
            if (play_box) {
                play_box->setVisible(false);
                mask->setVisible(false);
            }
        }
    }

    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *) e;
        if (mouseEvent->button() == Qt::LeftButton) {
            int r_width = recomConBox->width();
            int s_width = recomScrollBox->width();
            if (o->objectName() == "recomLfArrow") {
                if (move_x == 0) {
                    int moveLeft = s_width - r_width;
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(moveLeft, 0, r_width, recomConBox->height()));
                    move_x = moveLeft;
                } else {
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(0, 0, r_width, recomConBox->height()));
                    move_x = 0;
                }
                moveAnimation->start();
            }
            if (o->objectName() == "recomRhArrow") {
                if (move_x == 0) {
                    int moveLeft = s_width - r_width;
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(moveLeft, 0, r_width, recomConBox->height()));
                    move_x = moveLeft;
                } else {
                    moveAnimation->setStartValue(QRect(move_x, 0, r_width, recomConBox->height()));
                    moveAnimation->setEndValue(QRect(0, 0, r_width, recomConBox->height()));
                    move_x = 0;
                }
                moveAnimation->start();
            }
        }
    }
    return QWidget::eventFilter(o, e);
}


void Recommend::loadQSS() {
    QFile qss(":/resource/qss/recommend.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}