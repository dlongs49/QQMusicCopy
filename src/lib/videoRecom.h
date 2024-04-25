//
// Created by dinglong on 2024/4/16 11:51
//

#ifndef QQMUSICCOPY_VIDEORECOM_H
#define QQMUSICCOPY_VIDEORECOM_H

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
    QJsonObject json_data;
    QList<QString> recomAttrList;
    QPropertyAnimation *animation[6];
    QLabel *playSicon;
    QLabel *title;
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
    QWidget *scrollBox;
    QWidget *contentBox;
    QWidget *bannerBox;
    QWidget *wrapconBox[6];
    QWidget *playCountBox;
    QWidget *maskBox;
    QWidget *titleBox;
    QWidget *bannerItem[10];
    QWidget *newestItem[6];
    QWidget *hotItem[6];
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
