//
// Created by dinglong on 2024/4/17 下午 09:08
//

#ifndef QQMUSICCOPY_VIDEORANKING_H
#define QQMUSICCOPY_VIDEORANKING_H


#include <QPropertyAnimation>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QMouseEvent>
#include <QDateTime>
#include "../utils/tools.h"

class VideoRanking : public QWidget {
Q_OBJECT;
public:
    VideoRanking(QWidget *parent = nullptr);


signals:


public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();

    void rankingTop();
    void rankList();
    void toggleItem(QWidget *itemBox, QString objName, QEvent *e);

    QPixmap *getImage(QString url);

protected:

private:
    QJsonObject json_data;
    QLabel *title;
    QLabel *playBox;
    QLabel *itemImg;
    QLabel *dateTit;
    QLabel *sort;
    QLabel *num;
    QLabel *songItem[3];
    QWidget *widget;
    QWidget *containerBox;
    QWidget *rightBox;
    QWidget *maskBox;
    QWidget *item[20];
    QVBoxLayout *layout;
    QVBoxLayout *rightLayout;
    QVBoxLayout *containerVLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *containerLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};



#endif //QQMUSICCOPY_VIDEORANKING_H
