#include <QApplication>
#include <QTranslator>
#include <QtGui>
//#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

//    MainWindow fenetre;
//    fenetre.show();


    return app.exec();
}
