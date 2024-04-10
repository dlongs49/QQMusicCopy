//
// Created by dinglong on 2024/4/10 17:04
//

#ifndef QQMUSICCOPY_HOUSERANKING_H
#define QQMUSICCOPY_HOUSERANKING_H

#include <QWidget>
#include <QScrollArea>
#include <QList>
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QSizePolicy>
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
    void toggleItem(QWidget *itemBox, QString objName, QEvent *e);

    QPixmap *getImage(QString url);

protected:

private:
    int move_x = 0;
    QList<QString> recomAttrList;
    QPropertyAnimation *animation[6];
    QScrollArea *scrollArea;
    QLabel *tagLabel;
    QLabel *titleLabel;
    QLabel *title;
    QLabel *subTitle;
    QLabel *exTitle;
    QLabel *playBox;
    QLabel *moreTitle;
    QLabel *arrowTitle;
    QLabel *itemImg;
    QLabel *playSicon;
    QLabel *playCount;
    QWidget *widget;
    QWidget *containerBox;
    QWidget *contentBox;
    QWidget *playCountBox;
    QWidget *wrapconBox[6];
    QLabel *latestNavItem[6];
    QWidget *maskBox;
    QWidget *latestNavBox;
    QWidget *titleBox;
    QWidget *leftTitBox;
    QWidget *rightSongBox;
    QWidget *item[10];
    QWidget *officialItem[6];
    QWidget *listenBookItem[6];
    QWidget *classItem[6];
    QWidget *latestItem[6];
    QVBoxLayout *layout;
    QVBoxLayout *bannerImgLayout;
    QVBoxLayout *itemLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *bannerLayout;
    QHBoxLayout *bomLayout;
    QHBoxLayout *playCountLayout;
    QHBoxLayout *titLeftLayout;
    QHBoxLayout *moreRightLayout;
    QHBoxLayout *latestNavLayout;
    QGridLayout *containerLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};

#endif //QQMUSICCOPY_HOUSERANKING_H
