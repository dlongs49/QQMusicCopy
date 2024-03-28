//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"
Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    this->setFixedSize(820,800);

    widget = new QWidget(this);
    widget->setFixedSize(820,800);
    layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    area = new QScrollArea(this);
    area->setAlignment(Qt::AlignTop);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setGeometry(0,0,820,600);
    area->setWidget(widget);
    area->setWidgetResizable(false);


    recomBox = new QWidget(this);
    recomBox->setFixedWidth(820);
    recomBox->setObjectName("recomBox");
    recomBox->setStyleSheet("QWidget#recomBox{background:#fff}");
    recomLayout = new QHBoxLayout;


    recomItemBox = new QWidget(recomBox);
    recomItemBox->setFixedSize(406,230);
    recomItemLayout = new QVBoxLayout;
    recomItemLayout->setSpacing(0);
    recomItemLayout->setMargin(0);
    recomImgBox = new QWidget(recomItemBox);
    recomImgBox->setObjectName("recomImgBox");
    recomImgBox->installEventFilter(this);
    recomImgBox->setFixedSize(406,190);
    recomImgBox->setStyleSheet("background:#f0f");

    recomTit = new QLabel;
    recomTit->setObjectName("recomTit");
    recomTit->setText("Lone Ranger-Rachel Platten");
    recomSubTit = new QLabel;
    recomSubTit->setObjectName("recomTit");
    recomSubTit->setText("猜你喜欢");

    animation = new QPropertyAnimation(recomImgBox, "geometry");
    animation->setDuration(100);


    recomItemLayout->addWidget(recomImgBox);
    recomItemLayout->addWidget(recomTit);
    recomItemLayout->addWidget(recomSubTit);

    recomItemBox->setLayout(recomItemLayout);
    recomLayout->addWidget(recomItemBox);

    layout->addWidget(recomBox);
}

bool Recommend::eventFilter(QObject *o, QEvent *e) {
    if (o->objectName() == "recomImgBox") {
        if (e->type() == QEvent::Enter) {
            animation->setStartValue(QRect(0, 0, recomImgBox->width(), recomImgBox->height()));
            animation->setEndValue(QRect(0, -10, recomImgBox->width(), recomImgBox->height()));
            animation->start();
        }
        if (e->type() == QEvent::Leave) {
            animation->setStartValue(QRect(0, -10, recomImgBox->width(), recomImgBox->height()));
            animation->setEndValue(QRect(0, 0, recomImgBox->width(), recomImgBox->height()));
            animation->start();
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