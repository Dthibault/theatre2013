#ifndef GESTIONXML_H
#define GESTIONXML_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QtXml/QDomDocument>
#include <QTextStream>

#define ADAPTATEURXML "configuration_dmx/adaptateur.xml"
#define PASSWORDXML "configuration_dmx/password.xml"
#define APPAREILSXML "configuration_dmx/appareils.xml"
#define SCENARIOSXML "configuration_dmx/scenarios.xml"
#define SCENESXML "configuration_dmx/scenes.xml"
#define SEQUENCESXML "configuration_dmx/sequences.xml"


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
    void ajouterScenes(QString nom, QString uuid, QString uuidScenario);

    void enregistrerValeursScenes(QStringList canal, QStringList valeur, QString uuidScene);
    void recupererValeursScenes(QStringList *canal, QStringList *valeur, QString uuidScene);


    void supprimerScenario(QString uuid);
    void supprimerScenesAssociees(QString uuidScenario);
    void supprimerScene(QString uuid);

    void recupererSequences(QStringList *listeSequences, QStringList *listeUUID);
    void ajouterSequence(QString nom, QString uuid);
    void supprimerSequence(QString uuid);

    void afficherListeScenes(QStringList *listeScenes, QStringList *listeUUIDscene, QStringList *listeUUID);

    void recupererContenueSequence(QString uuidSequence, QStringList *temporisation, QStringList *listeUUIDscene, QStringList *listeUUID);
    QString recupererNomScene(QString uuid);
    void ajouterSceneDeSequence(QString uuidSequence, QString uuidScene, QString nouvelUUID, QString temporisation);
    void supprimerSceneDeSequence(QString uuidSequence, QString uuidScene);
    void supprimerSceneDeSequenceExterne(QString uuidScene);

private:


    
signals:
    
public slots:
    
};

#endif // GESTIONXML_H
