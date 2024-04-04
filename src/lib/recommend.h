//
// Created by dinglong on 2024/3/28 12:27
//

#ifndef QQMUSICCOPY_RECOMMEND_H
#define QQMUSICCOPY_RECOMMEND_H


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
#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <QSize>
#include <QIcon>
#include <QMouseEvent>
#include <cmath>
#include "../utils/tools.h"
#include "./popup/handleMenu.h"
class Recommend : public QWidget {
Q_OBJECT;
public:
    Recommend(QWidget *parent = nullptr);


signals:


public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();

    void RecommTop();
    void RecommTrea();
    void RecommListen();
    void RecommRoam();
    void RecommHeartbeat();
    void RecommProgram();
    void toggleItem(QWidget *itemBox,QString objName,QEvent *e);
    void showArrow(QObject *o, QEvent *e,int i);
    QLabel * arrowBox(int i, QString type);
    QPixmap* getImage(QString url);

protected:

private:
    int move_x = 0;
    QList<QString> recomAttrList;
    QPropertyAnimation *animation[6];
    QScrollArea *scrollArea;
    QLabel *recomTit;
    QLabel *recomSubTit;
    QLabel *guessTit;
    QLabel *guessSubTit;
    QLabel *playBox;
    QLabel *title;
    QLabel *playCount;
    QLabel *songsLabel;
    QLabel *idenLabel;
    QLabel *authorLabel;
    QLabel *loveBox;
    QLabel *moreBox;
    QLabel *recomImgBox;
    QWidget *widget;
    QWidget *recomOutBox;
    QWidget *recomBox;
    QWidget *wrapconBox[6];
    QWidget *recomItemBox[20];
    QWidget *treaItemBox[20];
    QWidget *roamItemBox[20];
    QWidget *everyItemBox[20];
    QWidget *heartItemBox[20];
    QWidget *programItemBox[20];
    QWidget *maskBox;
    QWidget *recomScrollBox;
    QWidget *titleBox;
    QWidget *rightBox;
    QWidget *floatBox;
    QVBoxLayout *layout;
    QVBoxLayout *recomOutLayout;
    QVBoxLayout *recomItemLayout;
    QVBoxLayout *guessLayout;
    QVBoxLayout *rightLayout;
    QGridLayout *treaLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *recomLayout;
    QHBoxLayout *recomConLayout;
    QHBoxLayout *titLayout;
    QHBoxLayout *listenLayout;
    QHBoxLayout *songsLayout;
    QHBoxLayout *floatLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
    HandleMenu *handleMenu;
};


#endif //QQMUSICCOPY_RECOMMEND_H
