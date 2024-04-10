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
#include <QMouseEvent>
#include <cmath>
#include "../utils/tools.h"

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
    void latestIssue();
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
    QLabel *tagLabel;
    QLabel *titleLabel;
    QLabel *title;
    QLabel *subTitle;
    QLabel *playBox;
    QLabel *bannerImg;
    QLabel *playCount;
    QLabel *moreTitle;
    QLabel *arrowTitle;
    QLabel *itemImg;
    QLabel *rightMoreBox;
    QWidget *widget;
    QWidget *containerBox;
    QWidget *scrollBox;
    QWidget *contentBox;
    QWidget *bannerBox;
    QWidget *wrapconBox[6];
    QLabel *latestNavItem[6];
    QWidget *maskBox;
    QWidget *latestNavBox;
    QWidget *titleBox;
    QWidget *leftTitBox;
    QWidget *bomBox;
    QWidget *bannerItem[10];
    QWidget *officialItem[6];
    QWidget *listenBookItem[6];
    QWidget *classItem[6];
    QWidget *latestItem[6];
    QVBoxLayout *layout;
    QVBoxLayout *containerLayout;
    QVBoxLayout *bannerImgLayout;
    QVBoxLayout *itemLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *bannerLayout;
    QHBoxLayout *bomLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *titLeftLayout;
    QHBoxLayout *moreRightLayout;
    QHBoxLayout *latestNavLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};

#endif //QQMUSICCOPY_HOUSESELECTED_H
