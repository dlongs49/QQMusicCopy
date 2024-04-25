//
// Created by dinglong on 2024/4/16 11:20
//

#ifndef QQMUSICCOPY_VIDEOCONTENT_H
#define QQMUSICCOPY_VIDEOCONTENT_H

#include "./videoRecom.h"
#include "./videoRanking.h"
#include "./videoLibrary.h"

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
    QHBoxLayout *navLayout;
    QVBoxLayout *layout;
    QVBoxLayout *containerLayout;
    QScrollArea *scrollArea;
    VideoRecom *videoRecom;
    VideoRanking *videoRanking;
    VideoLibrary *videoLibrary;
};



#endif //QQMUSICCOPY_VIDEOCONTENT_H
