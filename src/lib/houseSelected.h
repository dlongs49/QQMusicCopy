//
// Created by dinglong on 2024/4/6 下午 02:49
//

#ifndef QQMUSICCOPY_HOUSESELECTED_H
#define QQMUSICCOPY_HOUSESELECTED_H


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
#include "./popup/songInfo.h"

class HouseSelected : public QWidget {
Q_OBJECT;
public:
    HouseSelected(QWidget *parent = nullptr);


signals:


public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();

    void bannerTop();
    void officialPlayList();
    void listenBook();
    void classPrefe();
    void toggleItem(QWidget *itemBox, QString objName, QEvent *e);

    void showArrow(QObject *o, QEvent *e, int i);

    QLabel *arrowBox(int i, QString type);

    QPixmap *getImage(QString url);

protected:

private:
    int move_x = 0;
    QList<QString> recomAttrList;
    QPropertyAnimation *animation[6];
    QScrollArea *scrollArea;
    QLabel *navItem[5];
    QLabel *recomTit;
    QLabel *tagLabel;
    QLabel *titleLabel;
    QLabel *activeLine;
    QLabel *recomSubTit;
    QLabel *title;
    QLabel *subTitle;
    QLabel *guessSubTit;
    QLabel *playBox;
    QLabel *bannerImg;
    QLabel *playCount;
    QLabel *moreTitle;
    QLabel *arrowTitle;
    QLabel *itemImg;
    QLabel *loveBox;
    QLabel *rightMoreBox;
    QLabel *moreBox;
    QLabel *recomImgBox;
    QWidget *widget;
    QWidget *containerBox;
    QWidget *scrollBox;
    QWidget *contentBox;
    QWidget *recomBox;
    QWidget *bannerBox;
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
    QWidget *leftTitBox;
    QWidget *bomBox;
    QWidget *bannerItem[10];
    QWidget *officialItem[6];
    QWidget *listenBookItem[6];
    QWidget *classItem[6];
    QVBoxLayout *layout;
    QVBoxLayout *containerLayout;
    QVBoxLayout *recomOutLayout;
    QVBoxLayout *bannerImgLayout;
    QVBoxLayout *itemLayout;
    QVBoxLayout *rightLayout;
    QGridLayout *treaLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *bannerLayout;
    QHBoxLayout *bomLayout;
    QHBoxLayout *contentBoxLayout;
    QHBoxLayout *recomLayout;
    QHBoxLayout *recomConLayout;
    QHBoxLayout *titLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *titLeftLayout;
    QHBoxLayout *moreRightLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
    HandleMenu *handleMenu;
    SongInfo *songInfo;
};

#endif //QQMUSICCOPY_HOUSESELECTED_H
