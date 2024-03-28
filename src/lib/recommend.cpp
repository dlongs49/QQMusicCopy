//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"
Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();

    widget = new QWidget(this);
    widget->setObjectName("topMenuBox");
    widget->setFixedSize(820,66);

    layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    lWidget = new QWidget(this);
    lLayout = new QHBoxLayout;
    lLayout->setAlignment(Qt::AlignLeft);
    lLayout->setSpacing(0);
    lLayout->setMargin(0);

    // 左箭头
    lLabel = new QLabel;
    lLabel->setObjectName("left_arrow");
    lLabel->installEventFilter(this);
    lLabel->setCursor(Qt::PointingHandCursor);
    lLabel->setScaledContents(true);
    lLabel->setFixedSize(26, 26);
    l_arrowPix = new QPixmap;
    l_arrowPix->load(leftArrowImgPath);
    lLabel->setPixmap(*l_arrowPix);
    lLabel->setStyleSheet("padding:4px;");
    lLayout->addSpacing(38);
    lLayout->addWidget(lLabel);
    // 右箭头
    rLabel = new QLabel;
    rLabel->setObjectName("right_arrow");
    rLabel->installEventFilter(this);
    rLabel->setCursor(Qt::PointingHandCursor);
    rLabel->setScaledContents(true);
    rLabel->setFixedSize(26, 26);
    r_arrowPix = new QPixmap;
    r_arrowPix->load(righArrowImgPath);
    rLabel->setPixmap(*r_arrowPix);
    rLabel->setStyleSheet("padding:4px;");
    lLayout->addSpacing(10);
    lLayout->addWidget(rLabel);
    // 刷新
    refresh = new QLabel;
    refresh->setObjectName("refresh");
    refresh->installEventFilter(this);
    refresh->setCursor(Qt::PointingHandCursor);
    refresh->setScaledContents(true);
    refresh->setFixedSize(20, 20);
    refreshPix = new QPixmap;
    refreshPix->load(refreshImgPath);
    refresh->setPixmap(*refreshPix);
    lLayout->addSpacing(14);
    lLayout->addWidget(refresh);
    lLayout->addSpacing(20);

    sLayout = new QHBoxLayout;
    sLayout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    sLayout->setSpacing(0);
    sLayout->setMargin(0);
    sWidget = new QWidget(lWidget);
    sWidget->setCursor(Qt::IBeamCursor);
    int search_w = 130;
    sWidget->setFixedSize(search_w, 32);
    sWidget->setObjectName("searchBox");
    simgLabel = new QLabel;
    QPixmap searchIcon(":/resource/images/search.png");
    simgLabel->setPixmap(searchIcon);
    simgLabel->setFixedSize(16, 18);
    simgLabel->setScaledContents(true);
    simgLabel->setContentsMargins(0, 2, 0, 0);
    txtLabel = new QLabel;
    txtLabel->setObjectName("packHolder");
    txtLabel->setText("搜索音乐");
    searInput = new QLineEdit;
    searInput->setObjectName("searInput");
    searInput->setEchoMode(QLineEdit::Normal);
    searInput->setFixedSize(search_w - 30, 30);
    sLayout->addWidget(searInput);
    searInput->hide();
    sLayout->addWidget(simgLabel);
    sLayout->addSpacing(4);
    sLayout->addWidget(txtLabel);
    sWidget->installEventFilter(this);
    sWidget->setLayout(sLayout);

    // 听歌识曲
    rimgLabel = new QLabel;
    rimgLabel->setObjectName("listen_music");
    rimgLabel->installEventFilter(this);
    rimgLabel->setCursor(Qt::PointingHandCursor);
    listenPix = new QPixmap;
    listenPix->load(listenImgPath);
    rimgLabel->setPixmap(*listenPix);
    rimgLabel->setFixedSize(22, 22);
    rimgLabel->setScaledContents(true);
    lLayout->addWidget(sWidget);
    lLayout->addSpacing(10);
    lLayout->addWidget(rimgLabel);
    lLayout->setSpacing(0);
    lLayout->setMargin(0);
    lWidget->setLayout(lLayout);


    rLayout = new QHBoxLayout;
    rLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    rLayout->setSpacing(0);
    rLayout->setMargin(0);
    rWidget = new QWidget(this);
    rWidget->setMinimumSize(400, widget->size().height());
    // 头像
    avatorLabel = new QLabel;
    avatorLabel->setCursor(Qt::PointingHandCursor);
    avatorLabel->setObjectName("avator");
    avatorLabel->setScaledContents(true);
    avatorLabel->setFixedSize(26, 26);
    avatorPix = new QPixmap;
    // 网络请求图片
    manager = new QNetworkAccessManager;
    reply = manager->get(QNetworkRequest(QUrl("https://www.dillonl.com/u/snow.png")));
    loop = new QEventLoop();
    connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
    loop->exec();
    QByteArray imgData = reply->readAll();
    avatorPix->loadFromData(imgData);

    // 图片圆角
    int vw = avatorLabel->size().width();
    int vh = avatorLabel->size().height();
    QPixmap destImage(vw, vh);
    destImage.fill(Qt::transparent);
    painter = new QPainter(&destImage);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setRenderHints(QPainter::SmoothPixmapTransform, true);
    path = new QPainterPath;
    QRect rect(0, 0, vw, vh);
    path->addRoundedRect(rect, vw / 2, vw / 2);
    painter->setClipPath(*path);
    painter->drawPixmap(0, 0, vw, vh, *avatorPix);
    painter->end();
    avatorLabel->setPixmap(destImage);
    // 昵称
    uname = new QLabel;
    uname->setCursor(Qt::PointingHandCursor);
    uname->setText("冰消叶散");
    uname->setObjectName("uname");
    // 会员
    vipLabel = new QLabel;
    vipLabel->setObjectName("vip");
    vipLabel->installEventFilter(this);
    vipLabel->setCursor(Qt::PointingHandCursor);
    vipLabel->setFixedSize(18, 18);
    vipLabel->setScaledContents(true);
    vipPix = new QPixmap;
    vipPix->load(vipImgPath);
    vipLabel->setPixmap(*vipPix);
    // 下箭头【切换账号】
    downLabel = new QLabel;
    downLabel->setObjectName("down_arrow");
    downLabel->installEventFilter(this);
    downLabel->setCursor(Qt::PointingHandCursor);
    downLabel->setToolTip("用户信息");
    downLabel->setFixedSize(18, 18);
    downLabel->setScaledContents(true);
    downPix = new QPixmap;
    downPix->load(downArrowImgPath);
    downLabel->setPixmap(*downPix);
    // 皮肤
    skinLabel = new QLabel;
    skinLabel->setObjectName("skin");
    skinLabel->installEventFilter(this);
    skinLabel->setCursor(Qt::PointingHandCursor);
    skinLabel->setToolTip("换肤");
    skinLabel->setFixedSize(18, 18);
    skinLabel->setScaledContents(true);
    skinPix = new QPixmap;
    skinPix->load(skinImgPath);
    skinLabel->setPixmap(*skinPix);
    // 设置
    settingLabel = new QLabel;
    settingLabel->setObjectName("setting");
    settingLabel->installEventFilter(this);
    settingLabel->setCursor(Qt::PointingHandCursor);
    settingLabel->setToolTip("主菜单");
    settingLabel->setFixedSize(18, 18);
    settingLabel->setScaledContents(true);
    settingPix = new QPixmap;
    settingPix->load(settingImgPath);
    settingLabel->setPixmap(*settingPix);
    // 恢复
    recoverLabel = new QLabel;
    recoverLabel->setObjectName("recover");
    recoverLabel->installEventFilter(this);
    recoverLabel->setCursor(Qt::PointingHandCursor);
    recoverLabel->setToolTip("开启精简模式");
    recoverLabel->setFixedSize(18, 18);
    recoverLabel->setScaledContents(true);
    recoverPix = new QPixmap;
    recoverPix->load(recoverImgPath);
    recoverLabel->setPixmap(*recoverPix);


    // 最大化 最小化 关闭 布局
    opearOut = new QWidget(this);
    opearOut->setFixedHeight(widget->size().height());
    opearLayout = new QHBoxLayout;
    opearLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    opearLayout->setSpacing(0);
    opearLayout->setMargin(0);
    // 最小化
    int opw = 42;
    int iconX = (opw - 18) / 2;
    minimWidget = new QWidget(opearOut);
    minimWidget->setFixedSize(opw, widget->size().height() - 16);
    minimWidget->setCursor(Qt::PointingHandCursor);
    minimWidget->setToolTip("最小化");
    minimizeLabel = new QLabel(minimWidget);
    minimizeLabel->setObjectName("minim");
    minimizeLabel->installEventFilter(this);
    minimizeLabel->setGeometry(iconX, 24, 18, 18);
    minimizeLabel->setScaledContents(true);
    minimPix = new QPixmap;
    minimPix->load(minimImgPath);
    minimizeLabel->setPixmap(*minimPix);
    opearLayout->addWidget(minimWidget);
    // 最大化
    maximWidget = new QWidget(opearOut);
    maximWidget->setFixedSize(opw, widget->size().height() - 16);
    maximWidget->setCursor(Qt::PointingHandCursor);
    maximWidget->setToolTip("最大化");
    maximizeLabel = new QLabel(maximWidget);
    maximizeLabel->setObjectName("maxim");
    maximizeLabel->installEventFilter(this);
    maximizeLabel->setGeometry(iconX, 24, 18, 18);
    maximizeLabel->setScaledContents(true);
    maximPix = new QPixmap;
    maximPix->load(maximImgPath);
    maximizeLabel->setPixmap(*maximPix);
    opearLayout->addWidget(maximWidget);
    // 关闭
    closeWidget = new QWidget(opearOut);
    closeWidget->setFixedSize(opw, widget->size().height() - 16);
    closeWidget->setCursor(Qt::PointingHandCursor);
    closeWidget->setToolTip("关闭");
    closeLabel = new QLabel(closeWidget);
    closeLabel->setObjectName("close");
    closeLabel->installEventFilter(this);
    closeLabel->setGeometry(iconX, 24, 18, 18);
    closeLabel->setScaledContents(true);
    closePix = new QPixmap;
    closePix->load(closeImgPath);
    closeLabel->setPixmap(*closePix);
    opearLayout->addWidget(closeWidget);

    opearOut->setLayout(opearLayout);
    rLayout->addWidget(avatorLabel);
    rLayout->addSpacing(10);
    rLayout->addWidget(uname);
    rLayout->addSpacing(8);
    rLayout->addWidget(vipLabel);
    rLayout->addSpacing(10);
    rLayout->addWidget(downLabel);
    rLayout->addSpacing(20);
    rLayout->addWidget(skinLabel);
    rLayout->addSpacing(20);
    rLayout->addWidget(settingLabel);
    rLayout->addSpacing(20);
    rLayout->addWidget(recoverLabel);
    rLayout->addSpacing(4);
    rLayout->addWidget(opearOut);
    rWidget->setLayout(rLayout);

    widget->setLayout(layout);
    layout->addWidget(lWidget);
    layout->addWidget(rWidget);
    tools = new Tools();
}

bool Recommend::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e); // 事件转换
        if (mouseEvent->button() == Qt::LeftButton) {
            if (o->objectName() == "searchBox") {
                simgLabel->hide();
                txtLabel->hide();
                searInput->show();
                searInput->setFocus();
                emit onFocus(true);
                return true;
            }
            if (o->objectName() == "setting") {
                emit onSettPopup(true);
            }
            if (o->objectName() != "setting") {
                emit onSettPopup(false);
            }
            if (o->objectName() == "down_arrow") {
                emit onDownInfo(true);
            }
            if (o->objectName() != "down_arrow") {
                emit onDownInfo(false);
            }
            if (o->objectName() == "maxim") {
                emit onHandle("maxim");
            }
            if (o->objectName() != "searchBox") {
                searInput->clearFocus();
                if (!searInput->hasFocus()) {
                    simgLabel->show();
                    txtLabel->show();
                    searInput->hide();
                    emit onFocus(false);
                }
            }
        }
        if (mouseEvent->button() == Qt::RightButton) {
            emit onSettPopup(false);
            emit onFocus(false);
            emit onDownInfo(false);
        }
        return true;
    }

    // 左箭头
    if (o->objectName() == "left_arrow") {
        if (e->type() == QEvent::Enter) {
            lLabel->setPixmap(tools->hoverPixColor(l_arrowPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            lLabel->setPixmap(leftArrowImgPath);
        }
    }
    // 右箭头
    if (o->objectName() == "right_arrow") {
        if (e->type() == QEvent::Enter) {
            rLabel->setPixmap(tools->hoverPixColor(r_arrowPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            rLabel->setPixmap(righArrowImgPath);
        }
    }
    // 刷新
    if (o->objectName() == "refresh") {
        if (e->type() == QEvent::Enter) {
            refresh->setPixmap(tools->hoverPixColor(refreshPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            refresh->setPixmap(refreshImgPath);
        }
    }
    // 听歌识曲
    if (o->objectName() == "listen_music") {
        if (e->type() == QEvent::Enter) {
            rimgLabel->setPixmap(tools->hoverPixColor(listenPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            rimgLabel->setPixmap(listenImgPath);
        }
    }
    // 听歌识曲
    if (o->objectName() == "vip") {
        if (e->type() == QEvent::Enter) {
            vipLabel->setPixmap(tools->hoverPixColor(vipPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            vipLabel->setPixmap(vipImgPath);
        }
    }
    // 下箭头
    if (o->objectName() == "down_arrow") {
        if (e->type() == QEvent::Enter) {
            downLabel->setPixmap(tools->hoverPixColor(downPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            downLabel->setPixmap(downArrowImgPath);
        }
    }
    // 皮肤
    if (o->objectName() == "skin") {
        if (e->type() == QEvent::Enter) {
            skinLabel->setPixmap(tools->hoverPixColor(skinPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            skinLabel->setPixmap(skinImgPath);
        }
    }
    // 设置
    if (o->objectName() == "setting") {
        if (e->type() == QEvent::Enter) {
            settingLabel->setPixmap(tools->hoverPixColor(settingPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            settingLabel->setPixmap(settingImgPath);
        }
    }
    // 设置
    if (o->objectName() == "recover") {
        if (e->type() == QEvent::Enter) {
            recoverLabel->setPixmap(tools->hoverPixColor(recoverPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            recoverLabel->setPixmap(recoverImgPath);
        }
    }
    // 最小化
    if (o->objectName() == "minim") {
        if (e->type() == QEvent::Enter) {
            minimizeLabel->setPixmap(tools->hoverPixColor(minimPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            minimizeLabel->setPixmap(minimImgPath);
        }
    }
    // 最大化
    if (o->objectName() == "maxim") {
        if (e->type() == QEvent::Enter) {
            maximizeLabel->setPixmap(tools->hoverPixColor(maximPix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            maximizeLabel->setPixmap(maximImgPath);
        }
    }
    // 关闭
    if (o->objectName() == "close") {
        if (e->type() == QEvent::Enter) {
            closeLabel->setPixmap(tools->hoverPixColor(closePix, init_color));
        }
        if (e->type() == QEvent::Leave) {
            closeLabel->setPixmap(QPixmap(closeImgPath));
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