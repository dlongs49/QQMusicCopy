//
// Created by dinglong on 2024/3/27 18:48
//

#ifndef QQMUSICCOPY_DOWNINFO_H
#define QQMUSICCOPY_DOWNINFO_H

#include <QWidget>
#include <QFile>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QEvent>

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
    QLabel *numLabel;
    QLabel *titLabel;
    QLabel *songsLabel;
    QLabel *followLabel;
    QLabel *vermLabel;
    QLabel *lineLabel;
    QPushButton *homeBtn;
    QPushButton *toggleBtn;
    QWidget *pointsWidget;
    QWidget *statisWidget;
    QWidget *opearWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *pointsLayout;
    QHBoxLayout *statisLayout;
    QHBoxLayout *opearLayout;
};

#endif //QQMUSICCOPY_DOWNINFO_H
