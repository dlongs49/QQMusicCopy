//
// Created by dinglong on 2024/4/5 下午 02:50
//

#ifndef QQMUSICCOPY_SONGINFO_H
#define QQMUSICCOPY_SONGINFO_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

class SongInfo : public QWidget {
Q_OBJECT;
public:
    SongInfo(QWidget *parent = nullptr);

signals:
public slots:

    void loadQSS();

protected:

private:
    int w = 350;
    QFrame *frame;
    QGraphicsDropShadowEffect *shadow;
    QLabel *bomItem[2];
    QLabel *titleLabel;
    QWidget *bomWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *bomLayout;
};
#endif //QQMUSICCOPY_SONGINFO_H
