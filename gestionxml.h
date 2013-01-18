#ifndef GESTIONXML_H
#define GESTIONXML_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QtXml/QDomDocument>
#include <QTextStream>

#define ADAPTATEURXML "configuration/adaptateur.xml"
#define PASSWORDXML "configuration/password.xml"


class GestionXML : public QObject
{
    Q_OBJECT
public:
    explicit GestionXML(QObject *parent = 0);
    ~GestionXML();

    void ecritureAdaptateur(QString adresse, QString uuid);
    bool lireAdaptateur(QString *adresseAdaptateur, QString *UUIDAdaptateur);

    void ecriturePassword(QString password);
    bool lirePassword(QString *password);

private:

    
signals:
    
public slots:
    
};

#endif // GESTIONXML_H
