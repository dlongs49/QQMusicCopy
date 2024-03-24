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

    hisLayout = new QVBoxLayout;
    hisLayout->setSpacing(0);
    hisLayout->setMargin(0);
    hisLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    titLayout = new QHBoxLayout;
    titLayout->setSpacing(0);
    titLayout->setMargin(0);

    histTit = new QLabel;
    histTit->setText("历史搜索");
    titLayout->addSpacing(12);
    titLayout->addWidget(histTit);

    clearBtn = new QPushButton;
    clearBtn->setText("清除");
    clearBtn->setCursor(Qt::PointingHandCursor);
    clearBtn->setFixedSize(40,20);
    clearBtn->setObjectName("clearBtn");
    titLayout->addWidget(clearBtn);

    hisbox = new QLabel;
    hisbox->setFixedSize(rWidget->width() - 10, 38);
    hisbox->setObjectName("hisTitBox");
    hisbox->setLayout(titLayout);
    hisLayout->addWidget(hisbox);
    hisLayout->addSpacing(4);
    rWidget->setLayout(hisLayout);

    hisTxtLayout = new QVBoxLayout;
    hisTxtLayout->setAlignment(Qt::AlignTop);
    hisTxtLayout->setSpacing(0);
    hisTxtLayout->setMargin(0);


    hisWidget = new QWidget(rWidget);
    hisWidget->setFixedHeight(rWidget->height() - hisbox->height()-8);
    hisListLayout = new QVBoxLayout;
    hisListLayout->setAlignment(Qt::AlignCenter);
    hisListLayout->setMargin(0);
    hisListLayout->setSpacing(0);


    for (int i = 0; i < 10; i++) {
        hisTxtLabel[i] = new QLabel;
        hisTxtLabel[i]->setCursor(Qt::PointingHandCursor);
        hisTxtLabel[i]->setObjectName("hisTxtLabel");
        hisTxtLabel[i]->setText("无名的人");
        hisTxtLabel[i]->setFixedSize(rWidget->width() - 10,30);
        hisTxtLayout->addWidget(hisTxtLabel[i]);
    }



    noHisLabel = new QLabel;
    noHisLabel->setFixedSize(74,60);
    noHisLabel->setScaledContents(true);
    QPixmap nopix(":/resource/images/no_search_his.png");
    noHisLabel->setPixmap(nopix);

    noHisLabel->setContentsMargins(14,0,0,0);
    noHisTxt = new QLabel;
    noHisTxt->setContentsMargins(0,8,0,0);
    noHisTxt->setText("暂无搜索历史记录");

    hisListLayout->addWidget(noHisLabel);
    hisListLayout->addWidget(noHisTxt);

//    hisWidget->setLayout(hisTxtLayout);
    hisWidget->setLayout(hisListLayout);
    hisLayout->addWidget(hisWidget);












    mainLayout->addWidget(rWidget);

    frame->setLayout(mainLayout);
}