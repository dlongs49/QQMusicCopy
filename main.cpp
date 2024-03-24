#include <QApplication>
#include <QDir>
#include "src/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QString path = ":/resource/qss/";
    QStringList pathList = QDir(path).entryList(QDir::Files);
    QString strStyle;
    for (auto strFileName: pathList) {
        QFile qss(path + strFileName);
        if (qss.open(QFile::ReadOnly)) {
            strStyle += QLatin1String(qss.readAll());
        }
        qss.close();
    }
    a.setStyleSheet(strStyle);
    MainWindow m;
    m.show();
    return a.exec();
}
