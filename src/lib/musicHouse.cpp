//
// Created by dinglong on 2024/4/6 12:41
//

#include "musicHouse.h"

MusicHouse::MusicHouse(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();

    this->setFixedSize(820, 500);
    widget = new QWidget(this);
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

    containerBox = new QWidget(widget);
    containerBox->setFixedWidth(this->width() - 20);

    containerLayout = new QVBoxLayout;
    containerLayout->setAlignment(Qt::AlignTop);
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    containerBox->setLayout(containerLayout);
    title = new QLabel;
    title->setObjectName("title");
    title->setText("乐馆");
    containerLayout->addSpacing(20);
    containerLayout->addWidget(title);
    containerLayout->addSpacing(22);

    navBox = new QWidget(containerBox);
    navBox->setFixedSize(containerBox->width() - 38, 34);
    navBox->installEventFilter(this);
    containerLayout->addWidget(navBox, 0, Qt::AlignRight);
    activeLine = new QLabel(navBox);
    activeLine->setFixedSize(22, 3);
    activeLine->setObjectName("activeLine");
    activeLine->move(2, 26);

    navLayout = new QHBoxLayout;
    navLayout->setSpacing(0);
    navLayout->setMargin(0);
    navLayout->setAlignment(Qt::AlignTop);
    navBox->setLayout(navLayout);

    QStringList navList = {"精选", "排行", "歌手"};
    for (int i = 0; i < navList.size(); ++i) {
        navItem[i] = new QLabel;
        navItem[i]->installEventFilter(this);
        navItem[i]->setCursor(Qt::PointingHandCursor);
        navItem[i]->setText(navList[i]);
        navItem[i]->setFixedSize(navItem[i]->sizeHint());
        navItem[i]->setObjectName("navItem");
        navItem[i]->setProperty("index",i);
        navLayout->addWidget(navItem[i]);
        navLayout->addSpacing(50);
    }


    layout->addWidget(containerBox);
    houseSelected = new HouseSelected(scrollArea);
    layout->addWidget(houseSelected);

    houseRanking = new HouseRanking(scrollArea);
    layout->addWidget(houseRanking);
    houseRanking->hide();

    houseSinger = new HouseSinger(scrollArea);
    layout->addWidget(houseSinger);
    houseSinger->hide();

    layout->addSpacing(30);

    widget->setLayout(layout);


}
bool MusicHouse::eventFilter(QObject *o, QEvent *e) {

    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *) e;
        if (mouseEvent->button() == Qt::LeftButton) {

            if (o->objectName() == "navItem") {
                int i = o->property("index").toInt();
                houseSelected->hide();
                houseRanking->hide();
                houseSinger->hide();
                if(i == 0){
                    houseSelected->show();
                    activeLine->move(2,26);
                }else if(i == 1){
                    houseRanking->show();
                    activeLine->move(77,26);
                }else{
                    houseSinger->show();
                    activeLine->move(154,26);
                }
            }
        }
        return QWidget::eventFilter(o, e);
    }
}


void MusicHouse::loadQSS() {
    QFile qss(":/resource/qss/musicHouse.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}