//
// Created by dinglong on 2024/4/18 14:54
//

#ifndef QQMUSICCOPY_VIDEOLIBRARY_H
#define QQMUSICCOPY_VIDEOLIBRARY_H

#include <QPushButton>
#include "../utils/tools.h"
class VideoLibrary : public QWidget {
Q_OBJECT;
public:
    VideoLibrary(QWidget *parent = nullptr);


signals:


public slots:

    void tagList();

    void allMV();

    bool eventFilter(QObject *watched, QEvent *event);

    void loadQSS();
    void clickNation(int i);
    void clickCategory(int i);
    QPixmap *getImage(QString url);

    void toggleItem(QWidget *itemBox, QString objName, QEvent *e);

protected:

private:
    QStringList areaList = {"全部", "内地","港台","欧美","韩国","日本"};
    QStringList distList = {"全部", "MV","现场","翻唱","舞蹈","影视","综艺","儿歌"};
    QJsonObject json_data;
    QPropertyAnimation *animation;
    QLabel *author;
    QLabel *playBox;
    QLabel *rNavTit[2];
    QPushButton *areaBtn[6];
    QPushButton *distBtn[8];
    QLabel *itemImg;
    QLabel *rightBox;
    QLabel *title;
    QWidget *widget;
    QWidget *containerBox;
    QWidget *contentBox;
    QWidget *bannerBox;
    QWidget *wrapconBox;
    QWidget *mvItem[66];
    QWidget *maskBox;
    QWidget *titleBox;
    QWidget *areaBox;
    QWidget *distBox;
    QVBoxLayout *layout;
    QVBoxLayout *containerLayout;
    QVBoxLayout *itemLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *areaLayout;
    QHBoxLayout *distLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *titLeftLayout;
    QHBoxLayout *rightLayout;
    QGridLayout *mvLayout;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QPixmap *coverImg;
    Tools *tools;
};


#endif //QQMUSICCOPY_VIDEOLIBRARY_H
