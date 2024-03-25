#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class Tools : public QWidget {
Q_OBJECT
public:
    Tools(QWidget *parent = nullptr);
public slots:
    QPixmap hoverPixColor(QPixmap *pix,QString color);
private:
};

#endif // TOOLS_H
