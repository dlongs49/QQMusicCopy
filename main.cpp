#include <QApplication>
#include "src/mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc,argv);
//    QFile  qss(":/resource/qss/style.qss");
//    if(qss.open(QFile::ReadOnly)){
//        a.setStyleSheet(qss.readAll());
//    }
//    qss.close();
    MainWindow m;
    m.show();
    return a.exec();
}
