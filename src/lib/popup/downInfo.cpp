//
// Created by dinglong on 2024/3/27 18:48
//

#include "downInfo.h"

DownInfo::DownInfo(QWidget *parent) : QWidget(parent) {
    loadQSS();
    this->hide();
    int h = 210;
    this->setGeometry(416, 44, w + 18, h + 18);
    // 边框阴影 + 圆角
    frame = new QFrame(this);
    frame->setGeometry(9, 9, w, h);
    frame->setObjectName("searchFrame");
    shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(1, 1);
    shadow->setColor(QColor("#c0c0c0"));
    shadow->setBlurRadius(14);
    frame->setGraphicsEffect(shadow);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);


    pointsWidget = new QWidget(frame);
    pointsWidget->setFixedSize(frame->width(), 100);
    pointsWidget->setObjectName("pointsBox");
    pointsLayout = new QHBoxLayout;
    pointsLayout->setAlignment(Qt::AlignCenter);

    numLabel = new QLabel;
    numLabel->setText("9");
    numLabel->setObjectName("pointsNum");
    titLabel = new QLabel;
    titLabel->setStyleSheet("margin-bottom:3px;");
    titLabel->setText("积分");
    pointsLayout->addWidget(numLabel);
    pointsLayout->addWidget(titLabel, 0, Qt::AlignBottom);
    pointsWidget->setLayout(pointsLayout);
    mainLayout->addWidget(pointsWidget);

    statisWidget = new QWidget(frame);
    statisWidget->setFixedSize(w,60);
    statisWidget->setObjectName("statisBox");
    statisLayout = new QHBoxLayout;
    songsLabel = new QLabel;
    songsLabel->setText("歌单6");
    songsLabel->setFixedSize(songsLabel->sizeHint().width(),songsLabel->sizeHint().height());
    songsLabel->setCursor(Qt::PointingHandCursor);
    songsLabel->setProperty("class","sfvLabel");
    followLabel = new QLabel;
    followLabel->setText("关注");
    followLabel->setFixedSize(songsLabel->sizeHint().width(),songsLabel->sizeHint().height());
    followLabel->setCursor(Qt::PointingHandCursor);
    followLabel->setProperty("class","sfvLabel");
    vermLabel = new QLabel;
    vermLabel->setText("粉丝2");
    vermLabel->setFixedSize(songsLabel->sizeHint().width(),songsLabel->sizeHint().height());
    vermLabel->setCursor(Qt::PointingHandCursor);
    vermLabel->setProperty("class","sfvLabel");
    statisLayout->addWidget(songsLabel);
    statisLayout->addWidget(followLabel);
    statisLayout->addWidget(vermLabel);
    statisWidget->setLayout(statisLayout);
    mainLayout->addWidget(statisWidget);

    opearWidget = new QWidget(frame);
    opearLayout = new QHBoxLayout;
    opearLayout->setAlignment(Qt::AlignTop);
    opearLayout->setSpacing(0);
    opearLayout->setMargin(0);

    homeBtn = new QPushButton("个人主页");
    homeBtn->setFixedHeight(50);
    homeBtn->setCursor(Qt::PointingHandCursor);
    homeBtn->setProperty("class","opearBtn");
    lineLabel = new QLabel;
    lineLabel->setFixedSize(1,27);
    lineLabel->setStyleSheet("background:#eee");
    toggleBtn = new QPushButton("切换账号");
    toggleBtn->setFixedHeight(50);
    toggleBtn->setCursor(Qt::PointingHandCursor);
    toggleBtn->setProperty("class","opearBtn");
    opearLayout->addWidget(homeBtn);
    opearLayout->addWidget(lineLabel);
    opearLayout->addWidget(toggleBtn);
    opearWidget->setLayout(opearLayout);

    mainLayout->addWidget(opearWidget);

    frame->setLayout(mainLayout);
}


bool DownInfo::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::MouseButtonRelease) {

        return true;
    }
    return false;
}

void DownInfo::loadQSS() {
    QFile qss(":/resource/qss/downInfo.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}