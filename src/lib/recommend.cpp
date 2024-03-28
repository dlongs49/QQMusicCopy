//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"

Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    this->setFixedSize(820, 800);

    widget = new QWidget(this);
    widget->setStyleSheet("QWidget{background:#fff}");
    widget->setFixedSize(820, 800);
    layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    area = new QScrollArea(this);
    area->setAlignment(Qt::AlignTop);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setGeometry(0, 0, 820, 600);
    area->setWidget(widget);
    area->setWidgetResizable(false);


    recomBox = new QWidget(this);
    recomBox->setFixedWidth(800);
    recomBox->setFixedHeight(280);
    recomBox->setObjectName("recomBox");

    recomLayout = new QHBoxLayout;
    recomLayout->setSpacing(0);
    recomLayout->setMargin(0);
    recomLayout->setAlignment(Qt::AlignTop);
    recomBox->setLayout(recomLayout);


    for (int i = 0; i < 3; ++i) {
        recomItemBox[i] = new QWidget(recomBox);
        if(i == 0){
            recomItemBox[0]->setFixedSize(356, 250);
        }else{
            recomItemBox[i]->setFixedSize(160, 250);
        }
        recomItemLayout = new QVBoxLayout;
        recomItemLayout->setSpacing(0);
        recomItemLayout->setMargin(0);
        recomItemLayout->setAlignment(Qt::AlignTop);

        recomImgBox = new QWidget(recomItemBox[i]);
        recomImgBox->setObjectName("recomImgBox");
        recomImgBox->installEventFilter(this);
        if(i == 0){
            recomImgBox->setFixedSize(406, 160);
            guessLayout = new  QVBoxLayout;
            guessLayout->setAlignment(Qt::AlignVCenter);
            guessTit = new QLabel;
            guessTit->setStyleSheet("font-size:20px");
            guessTit->setText("晚上好");
            guessSubTit = new QLabel;
            guessSubTit->setText("尝试来点音\n乐提提神吧");
            playBox = new QLabel;
            playBox->setFixedSize(40,30);
            QPixmap playPix(":/resource/images/play.png");
            playBox->setPixmap(playPix);
            playBox->setScaledContents(true);
            guessLayout->addWidget(guessTit);
            guessLayout->addWidget(guessSubTit);
            guessLayout->addSpacing(5);
            guessLayout->addWidget(playBox);
            recomImgBox->setLayout(guessLayout);
        }else{
            recomImgBox->setFixedSize(160, 160);
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
        recomLayout->addSpacing(20);
        recomLayout->addWidget(recomItemBox[i]);
    }


    layout->addWidget(recomBox);
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