//
// Created by dinglong on 2024/4/10 17:04
//

#ifndef QQMUSICCOPY_HOUSERANKING_H
#define QQMUSICCOPY_HOUSERANKING_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QMouseEvent>
#include <cmath>
#include "../utils/tools.h"

class HouseRanking : public QWidget {
Q_OBJECT;
public:
    HouseRanking(QWidget *parent = nullptr);


signals:


public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();

    void rankingTop();
    void regional();
    void feature();
    void globa();
    void toggleTopItem(QWidget *itemBox, QString objName, QEvent *e);
    void toggleItem(QWidget *itemBox, QString objName, QEvent *e);

    QPixmap *getImage(QString url);

protected:

private:
    QLabel *title;
    QLabel *playBox;
    QLabel *itemImg;
    QLabel *playSicon;
    QLabel *playCount;
    QLabel *songItem[3];
    QWidget *widget;
    QWidget *containerBox;
    QWidget *playCountBox;
    QWidget *maskBox;
    QWidget *containerVBox;
    QWidget *rightListBox;
    QWidget *item[10];
    QWidget *regItem[10];
    QWidget *feaItem[10];
    QWidget *globItem[10];
    QVBoxLayout *layout;
    QVBoxLayout *rightListLayout;
    QVBoxLayout *containerVLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *playCountLayout;
    QHBoxLayout *containerHLayout;
    QGridLayout *containerLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};

#endif //QQMUSICCOPY_HOUSERANKING_H
