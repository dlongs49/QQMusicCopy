//
// Created by dinglong on 2023/1/2.
//

#ifndef DEMO_2_MAINWINDOW_H
#define DEMO_2_MAINWINDOW_H

#include "./lib/rightMenu.h"
#include "./lib/container.h"
#include <QMainWindow>
#include <QPushButton>
#include <QMovie>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QSpacerItem>
#include <QWidget>
#include <QListWidgetItem>
#include <QCursor>
#include <QGraphicsDropShadowEffect>

class MainWindow : public QMainWindow {
Q_OBJECT;
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:

    QString onHandler(QString str);

private:
    QHBoxLayout *layout;
    rightMenu *right_menu;
    container *container_;
    QWidget *widget;
    HotSearch *hotSearch;

};

#endif //DEMO_2_MAINWINDOW_H
