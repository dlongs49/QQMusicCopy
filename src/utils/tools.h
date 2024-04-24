#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QSize>
#include <QFont>
#include <QFontMetrics>
#include <QFontDatabase>
#include <cmath>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
class Tools : public QWidget {
Q_OBJECT
public:
    Tools(QWidget *parent = nullptr);

public slots:

    QPixmap hoverPixColor(QPixmap *pix, QString color);
    QJsonObject toJson(QString json_path);
    QString toStrWan(int playCount);
    QPixmap imgPixRadius(QPixmap *pix, QSize size,int radius);
    QString textElps(QString text,int width,QFont font);
    QFont aliIcon();
private:
};

#endif // TOOLS_H
