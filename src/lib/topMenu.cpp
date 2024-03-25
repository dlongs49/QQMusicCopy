#include "topMenu.h"

TopMenu::TopMenu(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

//    layout->setAlignment(Qt::AlignJustify);
    widget = new QWidget(this);

    widget->setFixedHeight(66);
    widget->setFixedWidth(820);

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
    larrowPix = new QPixmap;
    larrowPix->load(":/resource/images/left_arrow.png");
    lLabel->setPixmap(*larrowPix);
    lLabel->setStyleSheet("padding:4px;");
    lLayout->addSpacing(38);
    lLayout->addWidget(lLabel);
    // 右箭头
    rLabel = new QLabel;
    rLabel->setCursor(Qt::PointingHandCursor);
    rLabel->setScaledContents(true);
    rLabel->setFixedSize(26, 26);
    QPixmap rPixmap(":/resource/images/right_arrow.png");
    rLabel->setPixmap(rPixmap);
    rLabel->setStyleSheet("padding:4px;");
    lLayout->addSpacing(10);
    lLayout->addWidget(rLabel);
    // 刷新
    refresh = new QLabel;
    refresh->setCursor(Qt::PointingHandCursor);
    refresh->setScaledContents(true);
    refresh->setFixedSize(20, 20);
    QPixmap refreshPix(":/resource/images/refresh.png");
    refresh->setPixmap(refreshPix);
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
    rimgLabel->setCursor(Qt::PointingHandCursor);
    QPixmap rasImg(":/resource/images/listen_music.png");
    rimgLabel->setPixmap(rasImg);
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
    avatorLabel->setObjectName("avator");
    avatorLabel->setScaledContents(true);
    avatorLabel->setFixedSize(26, 26);
    avatorPix = new QPixmap();
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
    uname->setText("冰消叶散");
    uname->setObjectName("uname");
    // 会员
    vipLabel = new QLabel;
    vipLabel->setFixedSize(18, 18);
    vipLabel->setScaledContents(true);
    QPixmap vipIcon(":/resource/images/vip.png");
    vipLabel->setPixmap(vipIcon);
    // 下箭头【切换账号】
    downLabel = new QLabel;
    downLabel->setCursor(Qt::PointingHandCursor);
    downLabel->setToolTip("用户信息");
    downLabel->setFixedSize(18, 18);
    downLabel->setScaledContents(true);
    QPixmap downIcon(":/resource/images/down_arrow.png");
    downLabel->setPixmap(downIcon);
    // 皮肤
    skinLabel = new QLabel;
    skinLabel->setCursor(Qt::PointingHandCursor);
    skinLabel->setToolTip("换肤");
    skinLabel->setFixedSize(18, 18);
    skinLabel->setScaledContents(true);
    QPixmap skinIcon(":/resource/images/skin.png");
    skinLabel->setPixmap(skinIcon);
    // 设置
    settingLabel = new QLabel;
    settingLabel->setCursor(Qt::PointingHandCursor);
    settingLabel->setToolTip("主菜单");
    settingLabel->setFixedSize(18, 18);
    settingLabel->setScaledContents(true);
    QPixmap settingIcon(":/resource/images/setting.png");
    settingLabel->setPixmap(settingIcon);
    // 恢复
    recoverLabel = new QLabel;
    recoverLabel->setCursor(Qt::PointingHandCursor);
    recoverLabel->setToolTip("开启精简模式");
    recoverLabel->setFixedSize(18, 18);
    recoverLabel->setScaledContents(true);
    QPixmap recoverIcon(":/resource/images/recover.png");
    recoverLabel->setPixmap(recoverIcon);


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
    minimizeLabel->setGeometry(iconX, 24, 18, 18);
    minimizeLabel->setScaledContents(true);
    QPixmap minimIcon(":/resource/images/minim.png");
    minimizeLabel->setPixmap(minimIcon);
    opearLayout->addWidget(minimWidget);
    // 最大化
    maximWidget = new QWidget(opearOut);
    maximWidget->setFixedSize(opw, widget->size().height() - 16);
    maximWidget->setCursor(Qt::PointingHandCursor);
    maximWidget->setToolTip("最大化");
    maximizeLabel = new QLabel(maximWidget);
    maximizeLabel->setGeometry(iconX, 24, 18, 18);
    maximizeLabel->setScaledContents(true);
    QPixmap maximIcon(":/resource/images/maxim.png");
    maximizeLabel->setPixmap(maximIcon);
    opearLayout->addWidget(maximWidget);
    // 关闭
    closeWidget = new QWidget(opearOut);
    closeWidget->setFixedSize(opw, widget->size().height() - 16);
    closeWidget->setCursor(Qt::PointingHandCursor);
    closeWidget->setToolTip("关闭");
    closeLabel = new QLabel(closeWidget);
    closeLabel->setGeometry(iconX, 24, 18, 18);
    closeLabel->setScaledContents(true);
    QPixmap closeIcon(":/resource/images/close.png");
    closeLabel->setPixmap(closeIcon);
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
bool TopMenu::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e); // 事件转换
        if (mouseEvent->button() == Qt::LeftButton) {
            if(o->objectName() == "searchBox"){
                simgLabel->hide();
                txtLabel->hide();
                searInput->show();
                searInput->setFocus();
                emit onFocus(true);
                return true;
            }
            if(o->objectName() != "searchBox"){
                searInput->clearFocus();
                if(!searInput->hasFocus()){
                    simgLabel->show();
                    txtLabel->show();
                    searInput->hide();
                    emit onFocus(false);
                }
            }
        }
        return true;
    }

    if(o->objectName() == "left_arrow"){
        if (e->type() == QEvent::Enter) {
            lLabel->setPixmap(tools->hoverPixColor(larrowPix,init_color));
        }
        if(e->type() == QEvent::Leave){
            lLabel->setPixmap(tools->hoverPixColor(larrowPix,hover_color));
        }
    }




    return QWidget::eventFilter(o, e);
}