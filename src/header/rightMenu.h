//
// Created by dinglong on 2023/1/23 19:10
//

#ifndef QTMUSIC_rightMenu_H
#define QTMUSIC_rightMenu_H
#include <QWidget>
#include <QPushButton>
#include <QMovie>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout> // 水平布局组件
#include <QVBoxLayout> // 垂直布局组件
#include <QListWidget> // 列表
#include <QScrollArea> // 滚动容器
#include <QSpacerItem>
#include <QListWidgetItem>
#include <QCursor>
class rightMenu : public QWidget{
Q_OBJECT;
public:
    rightMenu(QWidget *parent = nullptr);
    ~rightMenu();
signals:
    //点击信号
    void clicked();
public slots:
       void customClick();
protected:
    void mousePressEvent(QMouseEvent*);
private:
    QHBoxLayout *layout;
    QListWidget *list[4];
    QLabel *tlabel[4];
    QVBoxLayout *vlayout;
    QScrollArea *sarea;
    QWidget *widget;
    QListWidgetItem *recommend;
//    void setCursor(const QCursor &);

    QPushButton b1;
    QPushButton *b2;
    QMovie *qm_1;
    QLabel *ql_1;
    QLabel *ql_2;
    QPixmap *qp_1;
    void readQssStyle();

    void onlineMusic();

    void myMusic();

    void createSongList();

    void facoriteSonglist();
};
#endif //QTMUSIC_rightMenu_H
