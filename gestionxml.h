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
#define APPAREILSXML "configuration/appareils.xml"
#define SCENARIOSXML "configuration/scenarios.xml"
#define SCENESXML "configuration/scenes.xml"


class GestionXML : public QObject
{
    Q_OBJECT
public:
    explicit GestionXML(QObject *parent = 0);
    ~GestionXML();

    void ecritureAdaptateur(QString adresse, QString uuid);
    bool lireAdaptateur(QString *adresseAdaptateur, QString *UUIDAdaptateur);
    void effacerAdaptateur();

    void ecriturePassword(QString password);
    bool lirePassword(QString *password);

    void lireListeAppareils(QStringList *nom, QStringList *UUID, QStringList *typeAppareil);

    void ajouterAppareil(QString nom, QString uuid, QString nbCanal, QString typeAppareil, QStringList numeroCanal, QStringList actionCanal);
    void effacerAppareils(QString uuid);

    void recupererCanaux(QStringList *listeCanaux, QStringList *typeCanal, QString uuid);

    void recupererDimmer(QStringList *listeCanaux);

    void recupererListeScenarios(QStringList *listeScenarios, QStringList *listeUUID);
    void ajouterScenarios(QString nom, QString uuid);

    void recupererListeScenes(QStringList *listeScenes, QStringList *listeUUID, QString scenarioUUID);

private:


    
signals:
    
public slots:
    
};

#endif // GESTIONXML_H
