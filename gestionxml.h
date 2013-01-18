#ifndef GESTIONXML_H
#define GESTIONXML_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QtXml/QDomDocument>
#include <QTextStream>


class GestionXML : public QObject
{
    Q_OBJECT
public:
    explicit GestionXML(QObject *parent = 0);
    ~GestionXML();

    void ecritureAdaptateur(QString adresse, QString uuid);

private:

    
signals:
    
public slots:
    
};

#endif // GESTIONXML_H
