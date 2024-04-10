//
// Created by dinglong on 2024/4/6 12:41
//

#ifndef QQMUSICCOPY_MUSICHOUSE_H
#define QQMUSICCOPY_MUSICHOUSE_H

#include <QWidget>
#include <QScrollArea>
#include <QList>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <cmath>
#include "./houseSelected.h"
#include "./houseRanking.h"

class MusicHouse : public QWidget {
Q_OBJECT;
public:
    MusicHouse(QWidget *parent = nullptr);


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
    HouseSelected *houseSelected;
    HouseRanking *houseRanking;
};


#endif //QQMUSICCOPY_MUSICHOUSE_H
