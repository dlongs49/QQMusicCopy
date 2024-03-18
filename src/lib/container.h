//
// Created by dinglong on 2023/1/24 22:02
//

#ifndef QTMUSIC_container_H
#define QTMUSIC_container_H
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFile>
class container : public QWidget{
Q_OBJECT;
public:
    container(QWidget *parent = nullptr);
    ~container();
    QLabel *lLabel;
    QLabel *rLabel;
    QWidget *widget;
    QLineEdit *input;
    QHBoxLayout *layout;
protected:
private:
    void readQssStyle();
};
#endif //QTMUSIC_container_H
