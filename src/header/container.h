//
// Created by dinglong on 2023/1/24 22:02
//

#ifndef QTMUSIC_container_H
#define QTMUSIC_container_H
#include <QWidget>
#include <QLabel>

class container : public QWidget{
Q_OBJECT;
public:
    container(QWidget *parent = nullptr);
    ~container();
    QLabel *label;
protected:
private:
};
#endif //QTMUSIC_container_H
