//
// Created by dinglong on 2023/1/24 22:02
//

#ifndef QTMUSIC_container_H
#define QTMUSIC_container_H
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
class container : public QWidget{
Q_OBJECT;
public:
    container(QWidget *parent = nullptr);
    ~container();
    QLabel *lLabel;
    QLabel *rLabel;
    QLabel *refresh;
    QWidget *widget;
    QLabel *simgLabel;
    QLabel *txtLabel;
    QLabel *rimgLabel;
    QLabel *avatorLabel;
    QWidget *lWidget;
    QWidget *rWidget;
    QWidget *sWidget;
    QLineEdit *searInput;
    QHBoxLayout *layout;
    QHBoxLayout *lLayout;
    QHBoxLayout *sLayout;
    QHBoxLayout *rLayout;
    QPixmap *avatorPix;
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
    QEventLoop *loop;
    QByteArray *byteArray;
protected:
private:
};
#endif //QTMUSIC_container_H
