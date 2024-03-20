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
    QLabel *refresh;
    QWidget *widget;
    QWidget *lWidget;
    QWidget *rWidget;
    QLineEdit *input;
    QHBoxLayout *layout;
    QHBoxLayout *lLayout;
protected:
private:
};
#endif //QTMUSIC_container_H
