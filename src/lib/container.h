//
// Created by dinglong on 2023/1/24 22:02
//

#ifndef QTMUSIC_container_H
#define QTMUSIC_container_H

#include <QWidget>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QDebug>
#include <QString>
#include "./topMenu.h"
#include "./popup/hotSearch.h"
#include "./popup/settMenu.h"
#include "./popup/downInfo.h"
#include "./recommend.h"
#include "./musicHouse.h"
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
    QVBoxLayout *containerLayout;
    QWidget *containerBox;


    TopMenu *topMenu;
    HotSearch *hotSearch;
    SettMenu *settMenu;
    DownInfo *downInfo;
    Recommend *recommend;
    MusicHouse *musicHouse;
};

#endif //QTMUSIC_container_H
