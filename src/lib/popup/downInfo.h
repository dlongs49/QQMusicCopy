//
// Created by window on 2024/3/27 18:48
//

#ifndef QQMUSICCOPY_DOWNINFO_H
#define QQMUSICCOPY_DOWNINFO_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QDebug>
#include <QEvent>
#include <QList>

class DownInfo : public QWidget {
Q_OBJECT;
public:
    DownInfo(QWidget *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event);

signals:
public slots:

    void loadQSS();

protected:

private:
    int w = 280;
    QFrame *frame;
    QGraphicsDropShadowEffect *shadow;
    QLabel *gradItem[10];
    QLabel *middLabel[2];
    QLabel *bottomLabel[5];
    QLabel *txtLabel;
    QLabel *imgLabel;
    QLabel *leftIcon;
    QLabel *titleLabel;
    QLabel *rightIcon;
    QLabel *newLabel;
    QWidget *gridWidget;
    QWidget *middWidget;
    QWidget *bottomWidget;
    QGridLayout *gradLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *middLayout;
    QVBoxLayout *bottomLayout;
    QVBoxLayout *gradItemLayout;
    QHBoxLayout *itemLayout;
    QHBoxLayout *bomItemLayout;
};

#endif //QQMUSICCOPY_DOWNINFO_H
