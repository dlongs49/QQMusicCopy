//
// Created by dinglong on 2024/4/5 12:31
//

#include "handleMenu.h"

HandleMenu::HandleMenu(QWidget *parent) : QWidget(parent) {
    loadQSS();
    tools = new Tools();
//    this->hide();
    int h = 436;
    this->setGeometry(210, 14, w + 18, h + 18);
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


    handleTopMenu();
    handleBomMenu();

    frame->setLayout(mainLayout);
}


void HandleMenu::handleTopMenu() {
    topWidget = new QWidget(frame);
    topWidget->setObjectName("topBox");
    topLayout = new QVBoxLayout;
    topLayout->setMargin(0);
    topLayout->setSpacing(0);
    QList<int> iconList = {0xe654,0xe677,0xe6b2,0xe78f};
    QStringList txtList = {"播放", "下一首播放", "播放相似单曲", "播放MV"};
    for (int i = 0; i < txtList.size(); ++i) {
        topItem[i] = new QLabel;
        topItem[i]->setFixedSize(w, 34);
        topItem[i]->setObjectName("topItem");
        topItem[i]->setCursor(Qt::PointingHandCursor);
        itemLayout = new QHBoxLayout;

        leftIcon = new QLabel(topItem[i]);
        leftIcon->setObjectName("leftIcon");
        leftIcon->setGeometry(14, 7, 20, 20);
        leftIcon->setFont(tools->aliIcon());
        leftIcon->setText(QChar(iconList[i]));
        leftIcon->setAlignment(Qt::AlignCenter);

        titleLabel = new QLabel;
        titleLabel->setObjectName("txt");
        titleLabel->setText(txtList[i]);

        itemLayout->addSpacing(36);
        itemLayout->addWidget(titleLabel);
        itemLayout->addSpacing(20);

        topItem[i]->setLayout(itemLayout);
        if (i == 0) {
            topLayout->addSpacing(10);
        }
        topLayout->addWidget(topItem[i]);
        if (i == txtList.size() - 1) {
            topLayout->addSpacing(10);
        }
    }
    topWidget->setLayout(topLayout);
    mainLayout->addWidget(topWidget);
}

void HandleMenu::handleBomMenu() {
    bomWidget = new QWidget(frame);
    bomLayout = new QVBoxLayout;
    bomLayout->setMargin(0);
    bomLayout->setSpacing(0);

    QList<int> iconList = {0xe6a9,0xe608,0xe658,0xe65d,0xe7b7,0,0xe6c0,0};
    QStringList txtList = {"我喜欢 ", "添加到 ", "分享", "下载", "单曲购买", "智能曲谱", "查看评论(1w+)","复制歌曲信息"};
    for (int i = 0; i < txtList.size(); i++) {
        bomItem[i] = new QLabel;
        bomItem[i]->setFixedSize(w, 34);
        bomItem[i]->setObjectName("bomItem");
        bomItem[i]->setCursor(Qt::PointingHandCursor);
        bomItemLayout = new QHBoxLayout;
        bomItemLayout->setAlignment(Qt::AlignVCenter);

        leftIcon = new QLabel(bomItem[i]);
        leftIcon->setScaledContents(true);
        leftIcon->setGeometry(14, 7, 20, 20);
        leftIcon->setObjectName("leftIcon");
        if(iconList[i] !=  0){
            leftIcon->setFont(tools->aliIcon());
            leftIcon->setText(QChar(iconList[i]));
        }
        leftIcon->setAlignment(Qt::AlignCenter);

        titleLabel = new QLabel;
        titleLabel->setObjectName("txt");
        titleLabel->setText(txtList[i]);

        rightIcon = new QLabel;
        rightIcon->setObjectName("arrowIcon");

        if(i == 1 || i == 3 || i == 5){
            rightIcon->setFont(tools->aliIcon());
            rightIcon->setText(QChar(0xe601));
            rightIcon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }

        bomItemLayout->addSpacing(36);
        bomItemLayout->addWidget(titleLabel);
        bomItemLayout->addWidget(rightIcon);
        bomItemLayout->addSpacing(20);

        bomItem[i]->setLayout(bomItemLayout);
        if (i == 0) {
            bomLayout->addSpacing(10);
        }
        bomLayout->addWidget(bomItem[i]);
        if (i == txtList.size() - 1) {
            bomLayout->addSpacing(10);
        }
    }
    bomWidget->setLayout(bomLayout);
    mainLayout->addWidget(bomWidget);
}

bool HandleMenu::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::MouseButtonRelease) {

        return true;
    }
    return false;
}

void HandleMenu::loadQSS() {
    QFile qss(":/resource/qss/handleMenu.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}