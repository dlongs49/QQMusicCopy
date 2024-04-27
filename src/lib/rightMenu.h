//
// Created by dinglong on 2023/1/23 19:10
//

#ifndef QTMUSIC_rightMenu_H
#define QTMUSIC_rightMenu_H

#include "../utils/tools.h"

class rightMenu : public QWidget {
Q_OBJECT;
public:
    rightMenu(QWidget *parent = nullptr);

    ~rightMenu();

signals:

public slots:
    void loadQSS();
    void onlineMusic();
    void myMusic();
    void myPlaySongs();


protected:

private:
    QWidget *widget;
    QWidget *containerBox;
    QWidget *onlineItem[4];
    QWidget *myMusicItem[5];
    QScrollArea *scrollArea;
    QHBoxLayout *itemLayout;
    QVBoxLayout *layout;
    QVBoxLayout *containerLayout;
    QLabel *title;
    QLabel *menuTitle;
    QLabel *iconLabel;
    Tools *tools;
};

#endif //QTMUSIC_rightMenu_H
