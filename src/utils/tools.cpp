#include "tools.h"

Tools::Tools(QWidget *parent) : QWidget(parent) {

}


// hover 更改图标颜色
QPixmap Tools::hoverPixColor(QPixmap *pix, QString color) {
    QPainter pr(pix);
    pr.setCompositionMode(QPainter::CompositionMode_SourceIn);
    pr.fillRect(pix->rect(), color);
    return *pix;
}
