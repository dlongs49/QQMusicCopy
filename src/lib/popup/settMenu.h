//
// Created by dinglong on 2024/3/25 下午11:20
//

#ifndef QQMUSICCOPY_SETTMENU_H
#define QQMUSICCOPY_SETTMENU_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QDebug>
#include <QEvent>
#include <QList>
#include <cmath>
#include "../../utils/tools.h"
class SettMenu : public QWidget {
Q_OBJECT;
public:
    SettMenu(QWidget *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event);

signals:
public slots:

    void loadQSS();

    void loadGradItem();

    void loadMiddleItem();

    void loadBottomItem();

protected:

private:
    int w = 260;
    QFrame *frame;
    QGraphicsDropShadowEffect *shadow;
    QLabel *gradItem[10];
    QLabel *middLabel[2];
    QLabel *bottomLabel[5];
    QLabel *txtLabel;
    QLabel *imgLabel;
    QLabel *leftIcon;
    QLabel *titleLabel;
    QLabel *rightIcon;
    QLabel *newLabel;
    QWidget *gridWidget;
    QWidget *middWidget;
    QWidget *bottomWidget;
    QGridLayout *gradLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *middLayout;
    QVBoxLayout *bottomLayout;
    QVBoxLayout *gradItemLayout;
    QHBoxLayout *itemLayout;
    QHBoxLayout *bomItemLayout;
    Tools *tools;
};


#endif //QQMUSICCOPY_SETTMENU_H
