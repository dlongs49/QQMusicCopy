#include <QApplication>
#include <QDir>
#include "src/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QFile qss(":/resource/qss/style.qss");
    qss.open(QFile::ReadOnly);
    QString style = QLatin1String(qss.readAll());
    a.setStyleSheet(style);
    qss.close();

    MainWindow m;
    m.show();
    return a.exec();
}
