//
// Created by dinglong on 2024/3/25 下午11:20
//

#include "settMenu.h"

SettMenu::SettMenu(QWidget *parent) : QWidget(parent) {
    loadQSS();
//    this->hide();
    int h = 596;
    this->setGeometry(500, 44, w + 18, h + 18);
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

    // 九宫格部件
    loadGradItem();
    // 中间部件集合
    loadMiddleItem();
    // 底部部件集合
    loadBottomItem();

    frame->setLayout(mainLayout);
}

void SettMenu::loadGradItem() {
    gridWidget = new QWidget(frame);
    gridWidget->setFixedWidth(228);
    gradLayout = new QGridLayout;
    gradLayout->setSpacing(0);
    gradLayout->setMargin(0);
    gradLayout->setAlignment(Qt::AlignTop);

    QList<QString> iconList;
    iconList << "phone" << "audio" << "bell" << "cloud_disk" << "timing" << "feedback" << "game" << "message"
             << "earprint" << "micro";
    QList<QString> txtList;
    txtList << "传歌到设备" << "音频转码" << "铃声制作" << "音乐网盘" << "定时设置" << "反馈修复" << "游戏优化"
            << "消息中心" << "耳纹音效" << "虚拟麦克风";
    for (int i = 0; i < 10; i++) {
        gradItem[i] = new QLabel;
        gradItem[i]->setToolTip(txtList[i]);
        gradItem[i]->setObjectName("gradItem");
        gradItem[i]->setCursor(Qt::PointingHandCursor);
        gradItem[i]->setFixedSize(76, 76);
        gradItemLayout = new QVBoxLayout;
        gradItemLayout->setSpacing(0);
        gradItemLayout->setMargin(0);
        gradItemLayout->setAlignment(Qt::AlignCenter);
        QPixmap pixmap(":/resource/images/" + iconList[i] + ".png");
        imgLabel = new QLabel;
        imgLabel->setFixedSize(30, 30);
        imgLabel->setScaledContents(true);
        imgLabel->setPixmap(pixmap);
        gradItemLayout->addWidget(imgLabel, 0, Qt::AlignCenter);
        txtLabel = new QLabel;
        txtLabel->setText(txtList[i]);
        txtLabel->setObjectName("txt");

        if (i == 9) {
            newLabel = new QLabel(gradItem[9]);
            newLabel->setObjectName("newTitle");
            newLabel->setText("new");
            newLabel->setAlignment(Qt::AlignCenter);
            newLabel->setGeometry(43, 3, 30, 12);
        }

        gradItemLayout->addSpacing(6);
        gradItemLayout->addWidget(txtLabel);
        gradItem[i]->setLayout(gradItemLayout);
    }
    gradLayout->addWidget(gradItem[0], 1, 1);
    gradLayout->addWidget(gradItem[1], 1, 2);
    gradLayout->addWidget(gradItem[2], 1, 3);
    gradLayout->addWidget(gradItem[3], 2, 1);
    gradLayout->addWidget(gradItem[4], 2, 2);
    gradLayout->addWidget(gradItem[5], 2, 3);
    gradLayout->addWidget(gradItem[6], 3, 1);
    gradLayout->addWidget(gradItem[7], 3, 2);
    gradLayout->addWidget(gradItem[8], 3, 3);
    gradLayout->addWidget(gradItem[9], 4, 1);

    gridWidget->setLayout(gradLayout);
    mainLayout->addSpacing(11);
    mainLayout->addWidget(gridWidget, 0, Qt::AlignHCenter);
    mainLayout->addSpacing(10);
}

void SettMenu::loadMiddleItem() {
    middWidget = new QWidget(frame);
    middWidget->setObjectName("middleBox");
    middLayout = new QVBoxLayout;
    middLayout->setMargin(0);
    middLayout->setSpacing(0);

    QList<QString> txtList;
    txtList << "添加歌曲" << "黑名单设置";
    for (int i = 0; i < 2; i++) {
        middLabel[i] = new QLabel;
        middLabel[i]->setFixedSize(w, 33);
        middLabel[i]->setObjectName("middleSettBox");
        middLabel[i]->setCursor(Qt::PointingHandCursor);
        itemLayout = new QHBoxLayout;

        leftIcon = new QLabel(middLabel[i]);
        leftIcon->setScaledContents(true);
        leftIcon->setGeometry(14,7,20,20);
        if (i == 1) {
            QPixmap leftPix(":/resource/images/blacksett.png");
            leftIcon->setPixmap(leftPix);
        }

        titleLabel = new QLabel;
        titleLabel->setObjectName("txt");
        titleLabel->setText(txtList[i]);
        rightIcon = new QLabel;
        rightIcon->setFixedSize(10, 10);
        if (i == 0) {
            QPixmap arrowPix(":/resource/images/right_small_arrow.png");
            rightIcon->setPixmap(arrowPix);
        }
        rightIcon->setScaledContents(true);
        itemLayout->addSpacing(36);
        itemLayout->addWidget(titleLabel);
        itemLayout->addWidget(rightIcon);
        middLabel[i]->setLayout(itemLayout);
        if (i == 0) {
            middLayout->addSpacing(10);
        }
        middLayout->addWidget(middLabel[i]);
    }
    middWidget->setLayout(middLayout);
    mainLayout->addWidget(middWidget);
}

void SettMenu::loadBottomItem() {
    bottomWidget = new QWidget(frame);
    bottomLayout = new QVBoxLayout;
    bottomLayout->setMargin(0);
    bottomLayout->setSpacing(0);

    QList<QString> txtList;
    txtList << "设置 " << "帮助 " << "升级" << "切换账号" << "退出QQ音乐 ";
    for (int i = 0; i < 5; i++) {
        bottomLabel[i] = new QLabel;
        bottomLabel[i]->setFixedSize(w, 33);
        bottomLabel[i]->setObjectName("bottomSettBox");
        bottomLabel[i]->setCursor(Qt::PointingHandCursor);
        bomItemLayout = new QHBoxLayout;
        bomItemLayout->setAlignment(Qt::AlignVCenter);

        leftIcon = new QLabel(bottomLabel[i]);
        leftIcon->setScaledContents(true);
        leftIcon->setGeometry(14,7,20,20);

        if (i == 0) {
            QPixmap leftPix(":/resource/images/setting_popup.png");
            leftIcon->setPixmap(leftPix);
        }
        if (i == 4) {
            QPixmap leftPix(":/resource/images/tips_warn.png");
            leftIcon->setPixmap(leftPix);
        }
        titleLabel = new QLabel;
        titleLabel->setObjectName("txt");
        titleLabel->setText(txtList[i]);
        rightIcon = new QLabel;
        rightIcon->setFixedSize(10, 10);
        if (i == 1) {
            QPixmap arrowPix(":/resource/images/right_small_arrow.png");
            rightIcon->setPixmap(arrowPix);
        }
        rightIcon->setScaledContents(true);
        bomItemLayout->addSpacing(36);
        bomItemLayout->addWidget(titleLabel);
        bomItemLayout->addWidget(rightIcon);
        bottomLabel[i]->setLayout(bomItemLayout);
        if (i == 0) {
            bottomLayout->addSpacing(10);
        }
        bottomLayout->addWidget(bottomLabel[i]);
        if (i == 4) {
            middLayout->addSpacing(10);
        }
    }
    bottomWidget->setLayout(bottomLayout);
    mainLayout->addWidget(bottomWidget);
}

bool SettMenu::eventFilter(QObject *obj, QEvent *e) {
    if (e->type() == QEvent::MouseButtonRelease) {

        return true;
    }
    return false;
}

void SettMenu::loadQSS() {
    QFile qss(":/resource/qss/settMenu.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}