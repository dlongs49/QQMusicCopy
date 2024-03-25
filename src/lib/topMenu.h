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
#include <QSize>
#include <QIcon>
#include <QMouseEvent>
#include "../utils/tools.h"
class TopMenu : public QWidget {
Q_OBJECT;
public:
    TopMenu(QWidget *parent = nullptr);


signals:
   bool onFocus(bool flag);
public slots:
    bool eventFilter(QObject *watched, QEvent *event);
    void loadQSS();
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
    QLineEdit *searInput;
    QPixmap *avatorPix;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPainter *painter;
    QPixmap *l_arrowPix;
    QPixmap *r_arrowPix;
    QPixmap *refreshPix;
    QPixmap *listenPix;
    QPixmap *vipPix;
    QPixmap *downPix;
    QPixmap *skinPix;
    QPixmap *settingPix;
    QPixmap *recoverPix;
    QPixmap *minimPix;
    QPixmap *maximPix;
    QPixmap *closePix;
    QPainterPath *path;
    Tools *tools;
    QString init_color = "#31c27c";
    QString hover_color = "#adadad";

    QString leftArrowImgPath = ":/resource/images/left_arrow.png";
    QString righArrowImgPath = ":/resource/images/right_arrow.png";
    QString refreshImgPath = ":/resource/images/refresh.png";
    QString listenImgPath = ":/resource/images/listen_music.png";
    QString vipImgPath = ":/resource/images/vip.png";
    QString downArrowImgPath = ":/resource/images/down_arrow.png";
    QString skinImgPath = ":/resource/images/skin.png";
    QString settingImgPath = ":/resource/images/setting.png";
    QString recoverImgPath = ":/resource/images/recover.png";
    QString minimImgPath = ":/resource/images/minim.png";
    QString maximImgPath = ":/resource/images/maxim.png";
    QString closeImgPath = ":/resource/images/close.png";
};

#endif //QQMUSICCOPY_TOPMENU_H
