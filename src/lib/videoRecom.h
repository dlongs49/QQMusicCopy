//
// Created by dinglong on 2024/4/16 11:51
//

#ifndef QQMUSICCOPY_VIDEORECOM_H
#define QQMUSICCOPY_VIDEORECOM_H


#include <QWidget>
#include <QScrollArea>
#include <QList>
#include <QLabel>
#include <QHBoxLayout>
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

class VideoRecom : public QWidget {
Q_OBJECT;
public:
    VideoRecom(QWidget *parent = nullptr);


signals:


public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();

    void bannerTop();
    void newest();
    void hotList();
    void assemble();
    void indiv();
    void toggleItem(QWidget *itemBox, QString objName, QEvent *e);

    void showArrow(QObject *o, QEvent *e, int i);

    QLabel *arrowBox(int i, QString type);

    QPixmap *getImage(QString url);

protected:

private:
    int move_x = 0;
    QJsonObject json_data;
    QList<QString> recomAttrList;
    QPropertyAnimation *animation[6];
    QScrollArea *scrollArea;
    QLabel *playSicon;
    QLabel *titleLabel;
    QLabel *title;
    QLabel *subTitle;
    QLabel *exTitle;
    QLabel *author;
    QLabel *playBox;
    QLabel *bannerImg;
    QLabel *playCount;
    QLabel *moreTitle;
    QLabel *arrowTitle;
    QLabel *l;
    QLabel *ll;
    QLabel *itemImg;
    QLabel *rightMoreBox;
    QWidget *widget;
    QWidget *containerBox;
    QWidget *leftTitBox;
    QWidget *scrollBox;
    QWidget *contentBox;
    QWidget *bannerBox;
    QWidget *wrapconBox[6];
    QLabel *latestNavItem[6];
    QWidget *playCountBox;
    QWidget *maskBox;
    QWidget *latestNavBox;
    QWidget *titleBox;
    QWidget *bomBox;
    QWidget *bannerItem[10];
    QWidget *newestItem[6];
    QWidget *hotItem[6];
    QWidget *listenBookItem[6];
    QWidget *assemItem[6];
    QWidget *indivItem[66];
    QVBoxLayout *layout;
    QVBoxLayout *containerLayout;
    QVBoxLayout *bannerImgLayout;
    QVBoxLayout *itemLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *bannerLayout;
    QHBoxLayout *playCountLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *titLeftLayout;
    QHBoxLayout *moreRightLayout;
    QGridLayout *indivLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};


#endif //QQMUSICCOPY_VIDEORECOM_H
