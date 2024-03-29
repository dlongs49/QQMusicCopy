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
    layout->setAlignment(Qt::AlignTop|Qt::AlignRight);
    layout->setSpacing(0);
    layout->setMargin(0);

    area = new QScrollArea(this);
    area->setAlignment(Qt::AlignTop);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setGeometry(0, 0, 820, 600);
    area->setWidget(widget);
    area->setWidgetResizable(false);


    recomBox = new QWidget(widget);
    recomBox->setFixedWidth(810);
    recomBox->setFixedHeight(218);
    recomBox->setObjectName("recomBox");
    recomBox->setStyleSheet("QWidget#recomBox{background:#00f}");

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);

    recomScrollBox = new QWidget(recomBox);
    recomScrollBox->setFixedSize(recomBox->width() - 70, recomBox->height());
    recomScrollBox->setObjectName("recomScrollBox");
    recomScrollBox->setStyleSheet("QWidget#recomScrollBox{background:#ff0}");

    recomConLayout = new QHBoxLayout;
    recomConLayout->setSpacing(0);
    recomConLayout->setMargin(0);
    recomConLayout->setAlignment(Qt::AlignLeft);

    recomConBox = new QWidget(recomScrollBox);
    recomConBox->setLayout(recomConLayout);
//    recomConBox->move(-100,0);

    for (int i = 0; i < 3; ++i) {
        recomItemBox[i] = new QWidget(recomBox);
        recomItemBox[i]->setObjectName("ff");
        if (i == 0) {
            recomItemBox[0]->setFixedWidth(356);
        } else {
            recomItemBox[i]->setFixedWidth(160);
        }
        recomItemLayout = new QVBoxLayout;
        recomItemLayout->setSpacing(0);
        recomItemLayout->setMargin(0);
        recomItemLayout->setAlignment(Qt::AlignTop);

        recomImgBox = new QWidget(recomItemBox[i]);
        recomImgBox->setObjectName("recomImgBox");
        recomImgBox->installEventFilter(this);
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

            playBox = new QLabel(recomImgBox);
            playBox->setFixedSize(40, 30);
            QPixmap playPix(":/resource/images/play.png");
            playBox->setPixmap(playPix);
            playBox->setScaledContents(true);
            playBox->move(10, recomImgBox->height() - 40);
        }

        recomTit = new QLabel;
        recomTit->setObjectName("recomTit");
        recomTit->setText("一生无悔-高安/杭娇");
        recomSubTit = new QLabel;
        recomSubTit->setObjectName("recomTit");
        recomSubTit->setText("每日三十首");

        recomItemLayout->addSpacing(10);
        recomItemLayout->addWidget(recomImgBox);
        recomItemLayout->addSpacing(6);
        recomItemLayout->addWidget(recomTit);
        recomItemLayout->addSpacing(3);
        recomItemLayout->addWidget(recomSubTit);
        recomItemBox[i]->setLayout(recomItemLayout);
        recomConLayout->addWidget(recomItemBox[i]);
        if(i != 2){
            qDebug() << i;
            recomConLayout->addSpacing(20);
        }
    }

    leftArrow = new QLabel;
    leftArrow->setFixedSize(30, 38);
    leftArrow->setCursor(Qt::PointingHandCursor);
    QPixmap lfArrow(":/resource/images/br_lf_arrow.png");
    leftArrow->setPixmap(lfArrow);
    leftArrow->setScaledContents(true);
    recomLayout->addWidget(leftArrow);


    recomLayout->addWidget(recomScrollBox);

    rightArrow = new QLabel;
    rightArrow->setFixedSize(30, 38);
    rightArrow->setCursor(Qt::PointingHandCursor);
    QPixmap rhArrow(":/resource/images/br_rh_arrow.png");
    rightArrow->setPixmap(rhArrow);
    rightArrow->setScaledContents(true);
    recomLayout->addWidget(rightArrow);


    layout->addWidget(recomBox);
    closeWidget = new QWidget(widget);
    closeWidget->setFixedSize(800, 200);
    closeWidget->setStyleSheet("background:#000");
    layout->addWidget(closeWidget);
    widget->setLayout(layout);
}

bool Recommend::eventFilter(QObject *o, QEvent *e) {
    if (o->objectName() == "recomImgBox") {
        if (e->type() == QEvent::Enter) {
//            animation->setStartValue(QRect(0, 10, recomImgBox->width(), recomImgBox->height()));
//            animation->setEndValue(QRect(0, 0, recomImgBox->width(), recomImgBox->height()));
//            animation->start();
        }
        if (e->type() == QEvent::Leave) {
//            animation->setStartValue(QRect(0, 0, recomImgBox->width(), recomImgBox->height()));
//            animation->setEndValue(QRect(0, 10, recomImgBox->width(), recomImgBox->height()));
//            animation->start();
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