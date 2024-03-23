#include "hotSearch.h"

HotSearch::HotSearch(QWidget *parent) : QWidget(parent) {
    int w = 476;
    int h = 376;
    this->resize(w + 18, h + 18);
    frame = new QFrame(this);
    frame->setGeometry(9, 9, w, h);
    frame->setObjectName("searchFrame");
    shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(1, 1);
    shadow->setColor(QColor("#c0c0c0"));
    shadow->setBlurRadius(14);
    frame->setGraphicsEffect(shadow);

    
}