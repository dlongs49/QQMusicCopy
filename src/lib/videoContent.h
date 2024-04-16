//
// Created by dinglong on 2024/4/16 11:20
//

#ifndef QQMUSICCOPY_VIDEOCONTENT_H
#define QQMUSICCOPY_VIDEOCONTENT_H

#include <QWidget>
#include <QScrollArea>
#include <QList>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <cmath>
#include "./videoRecom.h"
#include "./houseRanking.h"
#include "./houseSinger.h"

class VideoContent : public QWidget {
Q_OBJECT;
public:
    VideoContent(QWidget *parent = nullptr);


signals:


public slots:

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();

protected:

private:
    QLabel *title;
    QLabel *activeLine;
    QLabel *navItem[4];
    QWidget *widget;
    QWidget *containerBox;
    QWidget *navBox;
    QWidget *recomBox;
    QHBoxLayout *navLayout;
    QVBoxLayout *layout;
    QVBoxLayout *containerLayout;
    QScrollArea *scrollArea;
    VideoRecom *videoRecom;
    HouseRanking *houseRanking;
    HouseSinger *houseSinger;
};



#endif //QQMUSICCOPY_VIDEOCONTENT_H
