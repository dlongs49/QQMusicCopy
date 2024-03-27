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
#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <QDebug>
#include <QString>
#include "./topMenu.h"
#include "./popup/hotSearch.h"
#include "./popup/settMenu.h"
#include "./popup/downInfo.h"

class container : public QWidget {
Q_OBJECT;
public:
    container(QWidget *parent = nullptr);

    ~container();

public slots:

    bool handleEmit(bool flag);

    bool showSettPopup(bool flag);
    bool handleDownInfo(bool flag);

    QString emitHandle(QString str);

signals:

    QString mainHandle(QString str);

protected:

private:
    TopMenu *topMenu;
    HotSearch *hotSearch;
    SettMenu *settMenu;
    DownInfo *downInfo;
};

#endif //QTMUSIC_container_H
