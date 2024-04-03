#include "topMenu.h"

TopMenu::TopMenu(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    tools = new Tools();

    this->setFixedSize(820,66);

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
    lLabel->setFixedSize(26, 26);
    lLabel->setFont(tools->aliIcon());
    lLabel->setText(QChar(0xe600));
    lLayout->addSpacing(38);
    lLayout->addWidget(lLabel);
    // 右箭头
    rLabel = new QLabel;
    rLabel->setObjectName("right_arrow");
    rLabel->installEventFilter(this);
    rLabel->setCursor(Qt::PointingHandCursor);
    rLabel->setFixedSize(26, 26);
    rLabel->setFont(tools->aliIcon());
    rLabel->setText(QChar(0xe601));
    lLayout->addSpacing(10);
    lLayout->addWidget(rLabel);
    // 刷新
    refresh = new QLabel;
    refresh->setObjectName("refresh");
    refresh->installEventFilter(this);
    refresh->setCursor(Qt::PointingHandCursor);
    refresh->setFixedHeight(refresh->sizeHint().height());
    refresh->setFont(tools->aliIcon());
    refresh->setText(QChar(0xe65c));
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
    simgLabel->setObjectName("searchIcon");
    simgLabel->setFont(tools->aliIcon());
    simgLabel->setText(QChar(0xe657));
    simgLabel->setFixedSize(18, 18);
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
    rimgLabel->setFont(tools->aliIcon());
    rimgLabel->setText(QChar(0xe617));
    rimgLabel->setFixedSize(30, 30);
    rimgLabel->setAlignment(Qt::AlignCenter);
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
    vipLabel->setFixedSize(20, 20);
    vipLabel->setFont(tools->aliIcon());
    vipLabel->setText(QChar(0xe6a7));
    // 下箭头【切换账号】
    downLabel = new QLabel;
    downLabel->setObjectName("down_arrow");
    downLabel->installEventFilter(this);
    downLabel->setCursor(Qt::PointingHandCursor);
    downLabel->setToolTip("用户信息");
    downLabel->setFont(tools->aliIcon());
    downLabel->setText(QChar(0xe605));
    downLabel->setFixedSize(20, 20);
    downLabel->setAlignment(Qt::AlignCenter);
    // 皮肤
    skinLabel = new QLabel;
    skinLabel->setObjectName("skin");
    skinLabel->installEventFilter(this);
    skinLabel->setCursor(Qt::PointingHandCursor);
    skinLabel->setToolTip("换肤");
    skinLabel->setFixedSize(20, 20);
    skinLabel->setFont(tools->aliIcon());
    skinLabel->setText(QChar(0xe711));
    // 设置
    settingLabel = new QLabel;
    settingLabel->setObjectName("setting");
    settingLabel->installEventFilter(this);
    settingLabel->setCursor(Qt::PointingHandCursor);
    settingLabel->setToolTip("主菜单");
    settingLabel->setFixedSize(20, 20);
    settingLabel->setFont(tools->aliIcon());
    settingLabel->setText(QChar(0xe63d));
    // 恢复
    recoverLabel = new QLabel;
    recoverLabel->setObjectName("recover");
    recoverLabel->installEventFilter(this);
    recoverLabel->setCursor(Qt::PointingHandCursor);
    recoverLabel->setToolTip("开启精简模式");
    recoverLabel->setFixedSize(20, 20);
    recoverLabel->setFont(tools->aliIcon());
    recoverLabel->setText(QChar(0xe638));


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
    minimizeLabel->setAlignment(Qt::AlignCenter);
    minimizeLabel->setFont(tools->aliIcon());
    minimizeLabel->setText(QChar(0xe61d));
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
    maximizeLabel->setAlignment(Qt::AlignCenter);
    maximizeLabel->setFont(tools->aliIcon());
    maximizeLabel->setText(QChar(0xe652));
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
    closeLabel->setAlignment(Qt::AlignCenter);
    closeLabel->setFont(tools->aliIcon());
    closeLabel->setText(QChar(0xe603));
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

}

bool TopMenu::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::MouseButtonPress) {
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e); // 事件转换
        QMouseEvent* mouseEvent = (QMouseEvent*)e;
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


    return QWidget::eventFilter(o, e);
}


void TopMenu::loadQSS() {
    QFile qss(":/resource/qss/topMenu.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    this->setStyleSheet(style);
    qss.close();
}