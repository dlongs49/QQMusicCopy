#ifndef QQMUSICCOPY_HOTSEARCH_H
#define QQMUSICCOPY_HOTSEARCH_H
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
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QPixmap>
class HotSearch : public QWidget {
Q_OBJECT;
public:
    HotSearch(QWidget *parent = nullptr);


signals:
public slots:
protected:

private:
    QFrame *frame;
    QPushButton *clearBtn;
    QGraphicsDropShadowEffect *shadow;
    QLabel *hotLabel;
    QLabel *txtLabel[10];
    QLabel *hisTxtLabel[10];
    QLabel *numLabel;
    QLabel *titLabel;
    QLabel *hisbox;
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
    QWidget *widget;
    QWidget *lWidget;
    QWidget *rWidget;
    QWidget *hisWidget;
    QWidget *opearOut;
    QWidget *minimWidget;
    QWidget *maximWidget;
    QWidget *closeWidget;
    QHBoxLayout *layout;
    QHBoxLayout *mainLayout;
    QHBoxLayout *txtLayout;
    QHBoxLayout *titLayout;
    QVBoxLayout *hisTxtLayout;
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
#endif //QQMUSICCOPY_HOTSEARCH_H
