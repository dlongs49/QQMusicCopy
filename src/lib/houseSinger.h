//
// Created by dinglong on 2024/4/13 12:22
//

#ifndef QQMUSICCOPY_HOUSESINGER_H
#define QQMUSICCOPY_HOUSESINGER_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QMouseEvent>
#include <cmath>
#include "../utils/tools.h"

class HouseSinger : public QWidget {
Q_OBJECT;
public:
    HouseSinger(QWidget *parent = nullptr);


signals:


public slots:


    void loadQSS();

    void singerTop();
    void singerList();

    QPixmap *getImage(QString url);

protected:

private:
    QLabel *singerName;
    QLabel *itemImg;
    QWidget *widget;
    QWidget *containerBox;
    QWidget *singerItem[10];
    QWidget *item[55];
    QVBoxLayout *layout;
    QVBoxLayout *contentLayout;
    QHBoxLayout *itemLayout;
    QGridLayout *containerLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};


#endif //QQMUSICCOPY_HOUSESINGER_H
