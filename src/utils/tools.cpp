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

// 图片圆角
QPixmap Tools::imgPixRadius(QPixmap *pix, QSize size, int raidus) {
    int vw = size.width();
    int vh = size.height();
    QPixmap destImage(vw, vh);
    destImage.fill(Qt::transparent);
    QPainter *painter = new QPainter(&destImage);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setRenderHints(QPainter::SmoothPixmapTransform, true);
    QPainterPath *path = new QPainterPath;
    QRect rect(0, 0, vw, vh);
    path->addRoundedRect(rect, raidus, raidus);
    painter->setClipPath(*path);
    painter->drawPixmap(0, 0, vw, vh, *pix);
    painter->end();
    return destImage;
}

// 文字过长省略三个点
QString Tools::textElps(QString text, int width, QFont font) {
    QFontMetrics metrics(font);
    if (metrics.width(text) > width) {
        text = QFontMetrics(font).elidedText(text, Qt::ElideRight, width);
    }
    return text;
}

// 加载阿里矢量图标库
QFont Tools::aliIcon() {
    QFontDatabase fdb;
    int fontId = fdb.addApplicationFont(":/resource/iconfont.ttf");
    QString fontName = fdb.applicationFontFamilies(fontId).at(0);
    QFont iconFont = QFont(fontName);
    iconFont.setHintingPreference(QFont::PreferNoHinting);
    return iconFont;
}

QJsonObject Tools::toJson(QString json_path) {
    QFile file(json_path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "读取json失败";
        return {};
    }
    QByteArray dataByte(file.readAll());
    file.close();

    QJsonParseError jError;
    QJsonDocument json_doc = QJsonDocument::fromJson(dataByte, &jError);

    QJsonObject obj = json_doc.object();
    return obj;
}