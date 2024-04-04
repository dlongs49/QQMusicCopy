//
// Created by dinglong on 2024/3/28 12:27
//

#ifndef QQMUSICCOPY_RECOMMEND_H
#define QQMUSICCOPY_RECOMMEND_H


#include <QWidget>
#include <QScrollArea>
#include <QList>
#include <QFrame>
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

class Recommend : public QWidget {
Q_OBJECT;
public:
    Recommend(QWidget *parent = nullptr);


signals:

    bool onFocus(bool flag);

    bool onSettPopup(bool flag);

    bool onDownInfo(bool flag);

    bool onHandle(QString str);

public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();

    void RecommTop();
    void RecommTrea();
    void RecommListen();
    void RecommRoam();
    void RecommHeartbeat();
    void RecommProgram();
    QPixmap* getImage(QString url);

protected:

private:
    int move_x = 0;
    QList<QString> recomAttrList;
    QPropertyAnimation *moveAnimation;
    QPropertyAnimation *animation[6];
    QScrollArea *scrollArea;
    QLabel *recomTit;
    QLabel *recomSubTit;
    QLabel *guessTit;
    QLabel *guessSubTit;
    QLabel *playBox;
    QLabel *leftArrow[10];
    QLabel *rightArrow[10];
    QLabel *title;
    QLabel *playCount;
    QLabel *songsLabel;
    QLabel *idenLabel;
    QLabel *authorLabel;
    QLabel *loveBox;
    QLabel *moreBox;
    QLabel *maximizeLabel;
    QLabel *closeLabel;
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
    QWidget *recomConBox;
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
    QPixmap *avatorPix;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPainter *painter;
    QPixmap *l_arrowPix;
    QPixmap *r_arrowPix;
    QPixmap *refreshPix;
    QPixmap *leftArrowPix[10];
    QPixmap *rightArrowPix[10];
    QPixmap *downPix;
    QPixmap *skinPix;
    QPixmap *coverImg;
    QPixmap *recoverPix;
    QPixmap *minimPix;
    QPixmap *maximPix;
    QPixmap *closePix;
    QPainterPath *path;
    Tools *tools;
//    QSizePolicy *policy;
    QSizePolicy *policyHide;
    QString init_color = "#31c27c";
    QString hover_color = "#adadad";

    QString leftArrowImgPath = ":/resource/images/br_lf_arrow.png";
    QString righArrowImgPath = ":/resource/images/br_rh_arrow.png";
    QString refreshImgPath = ":/resource/images/refresh.png";
    QString listenImgPath = ":/resource/images/listen_music.png";
    QString vipImgPath = ":/resource/images/vip.png";
    QString downArrowImgPath = ":/resource/images/down_arrow.png";
    QString skinImgPath = ":/resource/images/skin.png";
    QString settingImgPath = ":/resource/images/setting.png";
    QString recoverImgPath = ":/resource/images/recover.png";
    QString minimImgPath = ":/resource/images/minim.png";
    QString maximImgPath = ":/resource/images/maxim.png";
    QString closeImgPath = ":/resource/images/close.png";
};


#endif //QQMUSICCOPY_RECOMMEND_H
