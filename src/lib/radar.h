//
// Created by dinglong on 2024/4/18 18:58
//

#ifndef QQMUSICCOPY_RADAR_H
#define QQMUSICCOPY_RADAR_H

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

class Radar : public QWidget {
Q_OBJECT;
public:
    Radar(QWidget *parent = nullptr);


signals:


public slots:


    void loadQSS();

    void radarTop();

    void radarList();

    QPixmap *getImage(QString url);

protected:

private:
    QLabel *singerName;
    QLabel *itemImg;
    QLabel *typeTxt;
    QLabel *title;
    QWidget *widget;
    QWidget *typeBox;
    QWidget *containerBox;
    QWidget *typeItem[10];
    QWidget *item[55];
    QVBoxLayout *layout;
    QVBoxLayout *contentLayout;
    QVBoxLayout *typeLayout;
    QHBoxLayout *itemLayout;
    QHBoxLayout *typeOutLayout;
    QGridLayout *containerLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};

#endif //QQMUSICCOPY_RADAR_H
