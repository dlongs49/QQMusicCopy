//
// Created by dinglong on 2024/4/5 12:31
//

#ifndef QQMUSICCOPY_HANDLEMENU_H
#define QQMUSICCOPY_HANDLEMENU_H


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

class HandleMenu : public QWidget {
Q_OBJECT;
public:
    HandleMenu(QWidget *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event);

signals:
public slots:

    void loadQSS();


    void handleTopMenu();

    void handleBomMenu();

protected:

private:
    int w = 210;
    QFrame *frame;
    QGraphicsDropShadowEffect *shadow;
    QLabel *topItem[4];
    QLabel *bomItem[8];
    QLabel *txtLabel;
    QLabel *imgLabel;
    QLabel *leftIcon;
    QLabel *titleLabel;
    QLabel *rightIcon;
    QLabel *newLabel;
    QWidget *gridWidget;
    QWidget *topWidget;
    QWidget *bomWidget;
    QGridLayout *gradLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *topLayout;
    QVBoxLayout *bomLayout;
    QVBoxLayout *gradItemLayout;
    QHBoxLayout *itemLayout;
    QHBoxLayout *bomItemLayout;
    Tools *tools;
};


#endif //QQMUSICCOPY_HANDLEMENU_H
