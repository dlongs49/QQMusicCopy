//
// Created by window on 2024/3/27 18:48
//

#include "downInfo.h"
DownInfo::DownInfo(QWidget *parent) : QWidget(parent) {
    loadQSS();
//    this->hide();
    int h = 525;
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