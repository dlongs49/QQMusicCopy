//
// Created by dinglong on 2024/3/25 下午11:20
//

#include "settMenu.h"

SettMenu::SettMenu(QWidget *parent) : QWidget(parent) {
    loadQSS();
//    this->hide();
    int w = 260;
    int h = 590;
    this->setGeometry(150, 44, w + 18, h + 18);
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
    // 九宫格布局
    gridWidget = new QWidget(frame);
    gridWidget->setFixedWidth(228);
    gradLayout = new QGridLayout;
    gradLayout->setSpacing(0);
    gradLayout->setMargin(0);
    gradLayout->setAlignment(Qt::AlignTop);

    QList<QString> iconList;
    iconList << "phone"<< "audio"<< "bell"<< "cloud_disk"<< "timing"<< "feedback"<< "game"<< "message"<< "earprint"<< "micro";
    QList<QString> txtList;
    txtList << "传歌到设备"<< "音频转码"<< "铃声制作"<< "音乐网盘"<< "定时设置"<< "反馈修复"<< "游戏优化"<< "消息中心"<< "耳纹音效"<< "虚拟麦克风";
    for (int i = 0; i < 10; i++) {
        gradItem[i] = new QLabel;
        gradItem[i]->setToolTip(txtList[i]);
        gradItem[i] ->setObjectName("gradItem");
        gradItem[i]->setCursor(Qt::PointingHandCursor);
        gradItem[i]->setFixedSize(76,76);
        gradItemLayout = new QVBoxLayout;
        gradItemLayout->setSpacing(0);
        gradItemLayout->setMargin(0);
        gradItemLayout->setAlignment(Qt::AlignCenter);
        QPixmap pixmap(":/resource/images/"+iconList[i]+".png");
        imgLabel = new QLabel;
        imgLabel->setFixedSize(30,30);
        imgLabel->setScaledContents(true);
        imgLabel->setPixmap(pixmap);
        gradItemLayout->addWidget(imgLabel,0,Qt::AlignCenter);
        txtLabel = new QLabel;
        txtLabel->setText(txtList[i]);
        txtLabel->setObjectName("txt");
        gradItemLayout->addSpacing(6);
        gradItemLayout->addWidget(txtLabel);
        gradItem[i]->setLayout(gradItemLayout);
    }
    gradLayout->addWidget(gradItem[0],1,1);
    gradLayout->addWidget(gradItem[1],1,2);
    gradLayout->addWidget(gradItem[2],1,3);
    gradLayout->addWidget(gradItem[3],2,1);
    gradLayout->addWidget(gradItem[4],2,2);
    gradLayout->addWidget(gradItem[5],2,3);
    gradLayout->addWidget(gradItem[6],3,1);
    gradLayout->addWidget(gradItem[7],3,2);
    gradLayout->addWidget(gradItem[8],3,3);
    gradLayout->addWidget(gradItem[9],4,1);

    gridWidget->setLayout(gradLayout);
    mainLayout->addSpacing(11);
    mainLayout->addWidget(gridWidget);

    // 分块布局
    middWidget = new QWidget(frame);
    middWidget->setFixedSize(w,60);
    middWidget->setStyleSheet("background:#ff0");

    middLayout = new QHBoxLayout;
    middLayout->setMargin(0);
    middLayout->setSpacing(0);
    leftIcon = new QLabel;
    leftIcon->setScaledContents(true);
    leftIcon->setFixedSize(20,20);
    QPixmap leftPix(":/");
    leftIcon->setPixmap(leftPix);
    titleLabel = new QLabel;
    titleLabel->setText("添加歌曲");
    rightIcon = new QLabel;
    rightIcon->setFixedSize(20,20);
    QPixmap arrowPix(":/resource/images/right_arrow.png");
    rightIcon->setPixmap(arrowPix);
    rightIcon->setScaledContents(true);
    middLayout->addWidget(leftIcon);
    middLayout->addWidget(titleLabel);
    middLayout->addWidget(rightIcon);
    middWidget->setLayout(middLayout);


    mainLayout->addWidget(middWidget);





    frame->setLayout(mainLayout);
}

bool SettMenu::eventFilter(QObject *obj, QEvent *e) {
    if (e->type() == QEvent::MouseButtonRelease) {
        clearBtn->setCursor(Qt::PointingHandCursor);
        clearBtn->setObjectName("clearBtn");
        clearBtn->style()->polish(clearBtn);
        hisWidget->show();
        noWidget->hide();
        return true;
    }
    return false;
}

void SettMenu::handleClear() {
    hisWidget->hide();
    noWidget->show();
    if (!hisWidget->isVisible()) {
        clearBtn->setCursor(Qt::ArrowCursor);
        clearBtn->setObjectName("disableBtn");
        clearBtn->style()->polish(clearBtn);
    }
}

void SettMenu::loadQSS() {
    QFile qss(":/resource/qss/settMenu.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}