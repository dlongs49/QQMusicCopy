//
// Created by dinglong on 2024/3/28 12:27
//

#include "recommend.h"
Recommend::Recommend(QWidget *parent) : QWidget(parent) {
    installEventFilter(this);
    loadQSS();
    this->setFixedSize(820,166);

    widget = new QWidget(this);
    widget->setFixedSize(820,166);
//    widget->setStyleSheet("background:#f0f");
    layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
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