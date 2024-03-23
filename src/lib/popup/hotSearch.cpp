#include "hotSearch.h"

HotSearch::HotSearch(QWidget *parent) : QWidget(parent) {
    int w = 476;
    int h = 376;
    this->resize(w + 18, h + 18);
    frame = new QFrame(this);
    frame->setGeometry(9, 9, w, h);
    frame->setObjectName("searchFrame");
    shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(1, 1);
    shadow->setColor(QColor("#c0c0c0"));
    shadow->setBlurRadius(14);
    frame->setGraphicsEffect(shadow);

    mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignCenter);

    lWidget = new QWidget(frame);
    lWidget->setFixedSize((w / 2) - 4, h - 2);
    lWidget->setStyleSheet("background:#fff");
    hotLayout = new QVBoxLayout;
    hotLayout->setSpacing(0);
    hotLayout->setMargin(0);
    hotLayout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    hotLabel = new QLabel;
    hotLabel->setFixedSize(lWidget->width() - 10, 38);
    hotLabel->setObjectName("hotTitleLabel");
    hotLabel->setText("热门搜索");
    hotLayout->addWidget(hotLabel);
    hotLayout->addSpacing(4);

    for (int i = 0; i < 10; i++) {
        txtLayout = new QHBoxLayout;
        txtLayout->setAlignment(Qt::AlignJustify | Qt::AlignVCenter);
        txtLayout->setSpacing(0);
        txtLayout->setMargin(0);


        txtLabel[i] = new QLabel;
        txtLabel[i]->setCursor(Qt::PointingHandCursor);
        txtLabel[i]->setFixedSize(lWidget->width() - 10, 30);
        txtLabel[i]->setObjectName("txtLabel");
        txtLabel[i]->setStyleSheet("QLabel#txtLabel:hover{background:#eee}");

        titLabel = new QLabel;
        titLabel->setStyleSheet("background:transparent");
        titLabel->setObjectName("tlabel");
        titLabel->setText("无名的人");
        titLabel->setFixedWidth(txtLabel[i]->width() - 68);
        txtLayout->addSpacing(8);
        txtLayout->addWidget(titLabel);

        numLabel = new QLabel;
        numLabel->setObjectName("tlabel");
        numLabel->setStyleSheet("background:transparent");
        numLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        numLabel->setText("400万");
        numLabel->setFixedWidth(52);
        txtLayout->addWidget(numLabel);
        txtLayout->addSpacing(8);

        txtLabel[i]->setLayout(txtLayout);
        hotLayout->addWidget(txtLabel[i]);
    }









    lWidget->setLayout(hotLayout);
    mainLayout->addWidget(lWidget);

    rWidget = new QWidget(frame);
    rWidget->setFixedSize((w / 2) - 4, h - 2);
    rWidget->setObjectName("history");
    mainLayout->addWidget(rWidget);

    frame->setLayout(mainLayout);
}