#ifndef GESTIONXML_H
#define GESTIONXML_H

#include <QObject>
#include <QString>
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

    static void ecritureAdaptateur(QString adresse, QString uuid);
    static bool lireAdaptateur(QString *adresseAdaptateur, QString *UUIDAdaptateur);
    static void effacerAdaptateur();

    static void ecriturePassword(QString password);
    static bool lirePassword(QString *password);

    static void lireListeAppareils(QStringList *nom, QStringList *UUID, QStringList *typeAppareil);

    static void ajouterAppareil(QString nom, QString uuid, QString nbCanal, QString typeAppareil, QStringList numeroCanal, QStringList actionCanal);
    static void effacerAppareils(QString uuid);

    static void recupererCanaux(QStringList *listeCanaux, QStringList *typeCanal, QString uuid);

    static void recupererDimmer(QStringList *listeCanaux);
    static void recupererToutLesCanaux(QStringList *listeCanaux);

    static void recupererListeScenarios(QStringList *listeScenarios, QStringList *listeUUID);
    static void ajouterScenarios(QString nom, QString uuid);

    static void recupererListeScenes(QStringList *listeScenes, QStringList *listeUUID, QString scenarioUUID);
    static void ajouterScenes(QString nom, QString uuid, QString uuidScenario);

    static void enregistrerValeursScenes(QStringList canal, QStringList valeur, QString uuidScene);
    static void recupererValeursScenes(QStringList *canal, QStringList *valeur, QString uuidScene);


    static void supprimerScenario(QString uuid);
    static void supprimerScenesAssociees(QString uuidScenario);
    static void supprimerScene(QString uuid);

    static void recupererSequences(QStringList *listeSequences, QStringList *listeUUID);
    static void ajouterSequence(QString nom, QString uuid);
    static void supprimerSequence(QString uuid);

    static void afficherListeScenes(QStringList *listeScenes, QStringList *listeUUIDscene, QStringList *listeUUID);

    static void recupererContenueSequence(QString uuidSequence, QStringList *temporisation, QStringList *listeUUIDscene, QStringList *listeUUID);
    static QString recupererNomScene(QString uuid);
    static void ajouterSceneDeSequence(QString uuidSequence, QString uuidScene, QString nouvelUUID, QString temporisation);
    static void supprimerSceneDeSequence(QString uuidSequence, QString uuidScene);
    static void supprimerSceneDeSequenceExterne(QString uuidScene);

private:


    
signals:
    
public slots:
    
};

#endif // GESTIONXML_H
