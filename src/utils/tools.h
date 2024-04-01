#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QSize>

class Tools : public QWidget {
Q_OBJECT
public:
    Tools(QWidget *parent = nullptr);

public slots:

    QPixmap hoverPixColor(QPixmap *pix, QString color);

    QPixmap imgPixRadius(QPixmap *pix, QSize size,int radius);

private:
};

#endif // TOOLS_H
