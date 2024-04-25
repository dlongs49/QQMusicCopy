//
// Created by dinglong on 2024/4/18 18:58
//

#ifndef QQMUSICCOPY_RADAR_H
#define QQMUSICCOPY_RADAR_H

#include "../utils/tools.h"

class Radar : public QWidget {
Q_OBJECT;
public:
    Radar(QWidget *parent = nullptr);


signals:


public slots:


    void loadQSS();

    void radarTop();

    void radarListCon();
    void forList();
    QPixmap *getImage(QString url);
    bool eventFilter(QObject *watched, QEvent *event);

protected:

private:
    QJsonArray navList;
    QJsonArray radarList;
    QScrollArea *scrollArea;
    QLabel *singerName;
    QLabel *itemImg;
    QLabel *typeTxt;
    QLabel *title;
    QLabel *bot;
    QLabel *playBox;
    QWidget *widget;
    QWidget *typeBox;
    QWidget *containerBox;
    QWidget *typeItem[11];
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
