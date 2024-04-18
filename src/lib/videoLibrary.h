//
// Created by dinglong on 2024/4/18 14:54
//

#ifndef QQMUSICCOPY_VIDEOLIBRARY_H
#define QQMUSICCOPY_VIDEOLIBRARY_H


#include <QWidget>
#include <QScrollArea>
#include <QList>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <cmath>
#include "./videoRecom.h"
#include "./videoRanking.h"
#include "./videoLibrary.h"

class VideoLibrary : public QWidget {
Q_OBJECT;
public:
    VideoLibrary(QWidget *parent = nullptr);


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
    VideoRanking *videoRanking;
    VideoLibrary *videoLibrary;
};




#endif //QQMUSICCOPY_VIDEOLIBRARY_H
