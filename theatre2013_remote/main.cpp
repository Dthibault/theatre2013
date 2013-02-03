#include <QApplication>
#include <QTranslator>
#include <QtGui>
#include <QLocale>
#include <QLibraryInfo>
#include "fenetreprincipale.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    app.setApplicationName("Théâtre 2013 - Remote");


    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QString locale = QLocale::system().name().section('_',0,0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    FenetrePrincipale fenetre;
    fenetre.show();



    return app.exec();
}
