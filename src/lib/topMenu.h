#ifndef QQMUSICCOPY_TOPMENU_H
#define QQMUSICCOPY_TOPMENU_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
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
#include <QMouseEvent>
#include "./popup/hotSearch.h"

class TopMenu : public QWidget {
Q_OBJECT;
public:
    TopMenu(QWidget *parent = nullptr);


signals:


public slots:

    void mousePressEvent(QMouseEvent  *e);
    bool eventFilter(QObject *watched, QEvent *event);
    void onBlur();
protected:

private:
    QLabel *lLabel;
    QLabel *rLabel;
    QLabel *refresh;
    QLabel *simgLabel;
    QLabel *txtLabel;
    QLabel *rimgLabel;
    QLabel *avatorLabel;
    QLabel *uname;
    QLabel *vipLabel;
    QLabel *downLabel;
    QLabel *skinLabel;
    QLabel *settingLabel;
    QLabel *recoverLabel;
    QLabel *minimizeLabel;
    QLabel *maximizeLabel;
    QLabel *closeLabel;
    QWidget *widget;
    QWidget *lWidget;
    QWidget *rWidget;
    QWidget *sWidget;
    QWidget *opearOut;
    QWidget *minimWidget;
    QWidget *maximWidget;
    QWidget *closeWidget;
    QHBoxLayout *layout;
    QHBoxLayout *lLayout;
    QHBoxLayout *sLayout;
    QHBoxLayout *rLayout;
    QHBoxLayout *opearLayout;
    QVBoxLayout *minimLayout;
    QLineEdit *searInput;
    QPixmap *avatorPix;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
    QEventLoop *loop;
    QByteArray *byteArray;
    QPainter *painter;
    QPainterPath *path;
    HotSearch *hotSearch;
};

#endif //QQMUSICCOPY_TOPMENU_H
