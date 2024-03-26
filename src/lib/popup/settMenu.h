//
// Created by dinglong on 2024/3/25 下午11:20
//

#ifndef QQMUSICCOPY_SETTMENU_H
#define QQMUSICCOPY_SETTMENU_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QEvent>
#include <QProxyStyle >
#include <QList>

class SettMenu : public QWidget {
Q_OBJECT;
public:
    SettMenu(QWidget *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event);

signals:
public slots:

    void handleClear();

    void loadQSS();

protected:

private:
    QFrame *frame;
    QPushButton *clearBtn;
    QGraphicsDropShadowEffect *shadow;
    QLabel *hotLabel;
    QLabel *gradItem[10];
    QLabel *hisTxtLabel[10];
    QLabel *txtLabel;
    QLabel *imgLabel;
    QLabel *histTit;
    QLabel *noHisLabel;
    QLabel *noHisTxt;
    QLabel *downLabel;
    QLabel *skinLabel;
    QLabel *settingLabel;
    QLabel *recoverLabel;
    QLabel *minimizeLabel;
    QLabel *maximizeLabel;
    QLabel *closeLabel;
    QWidget *gridWidget;
    QWidget *widget;
    QWidget *lWidget;
    QWidget *rWidget;
    QWidget *hisWidget;
    QWidget *noWidget;
    QWidget *minimWidget;
    QWidget *maximWidget;
    QWidget *closeWidget;
    QGridLayout *gradLayout;
    QHBoxLayout *layout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *txtLayout;
    QHBoxLayout *titLayout;
    QVBoxLayout *gradItemLayout;
    QVBoxLayout *hotLayout;
    QVBoxLayout *hisLayout;
    QVBoxLayout *hisListLayout;
    QLineEdit *searInput;
    QPixmap *avatorPix;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
    QEventLoop *loop;
    QByteArray *byteArray;
    QPainter *painter;
    QPainterPath *path;
};


#endif //QQMUSICCOPY_SETTMENU_H
