//
// Created by dinglong on 2024/4/5 下午 02:50
//

#include "songInfo.h"

SongInfo::SongInfo(QWidget *parent) : QWidget(parent) {
    loadQSS();
    this->hide();
    int h = 90;
    this->setGeometry(0, 0, w + 18, h + 18);
    // 边框阴影 + 圆角
    frame = new QFrame(this);
    frame->setGeometry(9, 9, w, h);
    frame->setObjectName("boxFrame");
    shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(1, 1);
    shadow->setColor(QColor("#c0c0c0"));
    shadow->setBlurRadius(14);
    frame->setGraphicsEffect(shadow);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    titleLabel = new QLabel;
    titleLabel->setFixedWidth(frame->width());
    titleLabel->setObjectName("titleBox");
    titleLabel->setText("Missing You (ASOT 1112) [Future Favorite]");

    mainLayout->addWidget(titleLabel);

    bomWidget = new QWidget(frame);
    bomWidget->setFixedHeight(40);
    bomWidget->setObjectName("bomBox");
    bomLayout = new QHBoxLayout;
    bomLayout->setMargin(0);
    bomLayout->setSpacing(0);

    bomItem[0] = new QLabel;
    bomItem[0]->setObjectName("txt");
    bomItem[0]->setText("大小：3M/15M/26M");

    bomItem[1] = new QLabel;
    bomItem[1]->setObjectName("txt");
    bomItem[1]->setText("时长：03:24");
    bomLayout->addSpacing(18);
    bomLayout->addWidget(bomItem[0],0,Qt::AlignLeft);
    bomLayout->addWidget(bomItem[1],0,Qt::AlignRight);
    bomLayout->addSpacing(18);
    bomWidget->setLayout(bomLayout);

    frame->setFixedHeight(h);

    mainLayout->addWidget(bomWidget);

    frame->setLayout(mainLayout);
}

void SongInfo::loadQSS() {
    QFile qss(":/resource/qss/songInfo.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}