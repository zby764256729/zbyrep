#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("����ͼ���ѯ");
    w.setFixedSize( w.width (),w.height ());
    w.show();
    
    return a.exec();
}
