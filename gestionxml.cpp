#include "gestionxml.h"

GestionXML::GestionXML(QObject *parent) :
    QObject(parent)
{
}

GestionXML::~GestionXML()
{

}

bool GestionXML::lireAdaptateur(QString *adresseAdaptateur, QString *UUIDAdaptateur)
{

    QDomDocument documentXML;
    QFile fichierXML(ADAPTATEURXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Adaptateur.xml");
        return false;
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();

        racine = racine.firstChildElement();

        if(racine.isNull())
        {
            return false;
        }
        else
        {
            QDomElement unElement = racine.firstChildElement();
            *adresseAdaptateur = unElement.text(); // On récupère l'adresse

            unElement = unElement.nextSiblingElement();

            *UUIDAdaptateur = unElement.text(); // On récupère l'UUID

            return true;
        }

    }

    fichierXML.close();

}

void GestionXML::effacerAdaptateur()
{
    QFile fichierXML(ADAPTATEURXML);

    if(!(fichierXML.open(QIODevice::WriteOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Adaptateur.xml");
    }
    else
    {
        QTextStream stream(&fichierXML);
        stream << "\n";
    }

    fichierXML.close();
}

void GestionXML::ecritureAdaptateur(QString adresse, QString uuid)
{

    QDomDocument documentXML;
    QFile fichierXML(ADAPTATEURXML);

    if(!(fichierXML.open(QIODevice::WriteOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Adaptateur.xml");
    }
    else
    {
        QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
        documentXML.insertBefore(xmlNode, documentXML.firstChild());

        QDomElement root = documentXML.createElement("theatre2013");
        documentXML.appendChild(root);

        QDomElement adaptateur = documentXML.createElement("adaptateur");
        adaptateur.setAttribute("id", 1);
        root.appendChild(adaptateur);

        QDomElement domAdresse = documentXML.createElement("adresse");
        adaptateur.appendChild(domAdresse);

        QDomText nomText = documentXML.createTextNode(adresse);
        domAdresse.appendChild(nomText);

        QDomElement domuuid = documentXML.createElement("UUID");
        adaptateur.appendChild(domuuid);

        QDomText nomUUID = documentXML.createTextNode(uuid);
        domuuid.appendChild(nomUUID);

        QTextStream stream(&fichierXML);
        documentXML.save(stream, 2);


    }

    fichierXML.close();

}


void GestionXML::ecriturePassword(QString password)
{
    QDomDocument documentXML;
    QFile fichierXML(PASSWORDXML);

    if(!(fichierXML.open(QIODevice::WriteOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Password.xml");
    }
    else
    {
        QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
        documentXML.insertBefore(xmlNode, documentXML.firstChild());

        QDomElement root = documentXML.createElement("theatre2013");
        documentXML.appendChild(root);

        QDomElement domPassword = documentXML.createElement("password");
        domPassword.setAttribute("method", "SHA-1");
        root.appendChild(domPassword);


        QDomText nodePassword = documentXML.createTextNode(password);
        domPassword.appendChild(nodePassword);


        QTextStream stream(&fichierXML);
        documentXML.save(stream, 2);


    }

    fichierXML.close();
}

bool GestionXML::lirePassword(QString *password)
{
    QDomDocument documentXML;
    QFile fichierXML(PASSWORDXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Password.xml");
        return false;
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();

        if(racine.isNull())
        {
            return false;
        }
        else
        {
            QDomElement unElement = racine.firstChildElement();
            *password = unElement.text(); // On récupère l'adresse


            return true;
        }

    }

    fichierXML.close();
}

void GestionXML::lireListeAppareils(QStringList *nom, QStringList *UUID, QStringList *typeAppareil)
{

    QDomDocument documentXML;
    QFile fichierXML(APPAREILSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Appareils.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement peripherique;

        while(!(noeud.isNull()))
        {
            peripherique = noeud.toElement();
            nom->push_back(peripherique.attribute("nom"));
            UUID->push_back(peripherique.attribute("uuid"));
            typeAppareil->push_back(peripherique.attribute("type"));


            noeud = noeud.nextSibling();
        }

    }

    fichierXML.close();
}


void GestionXML::ajouterAppareil(QString nom, QString uuid, QString nbCanal, QString typeAppareil, QStringList numeroCanal, QStringList actionCanal)
{
    QDomDocument documentXML;
    QFile fichierXML(APPAREILSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Appareils.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();

        QDomElement peripherique = documentXML.createElement("peripherique");

        racine.appendChild(peripherique);

        peripherique.setAttribute("nom", nom);
        peripherique.setAttribute("uuid", uuid);
        peripherique.setAttribute("nbCanal", nbCanal);
        peripherique.setAttribute("type", typeAppareil);

        QDomElement canal;
        QDomText action;

        for(int i=0; i<numeroCanal.size(); i++)
        {
             canal = documentXML.createElement("canal");
             canal.setAttribute("id", numeroCanal[i]);

             action = documentXML.createTextNode(actionCanal[i]);
             canal.appendChild(action);

             peripherique.appendChild(canal);
        }

        documentXML.save(out, 2);
        fichierXML.close();

    }
}

void GestionXML::effacerAppareils(QString uuid)
{

    QDomDocument documentXML;
    QFile fichierXML(APPAREILSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Appareils.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement peripherique;

        while(!(noeud.isNull()))
        {
            peripherique = noeud.toElement();

            if(peripherique.attribute("uuid") == uuid)
            {

                racine.removeChild(peripherique);
            }

            noeud = noeud.nextSibling();
        }

        documentXML.save(out, 2);
        fichierXML.close();

    }


}

void GestionXML::recupererCanaux(QStringList *listeCanaux, QStringList *typeCanal, QString uuid)
{
    QDomDocument documentXML;
    QFile fichierXML(APPAREILSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Appareils.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement peripherique;

        QDomNode noeudCanaux;
        QDomElement canauxElement;


        while(!(noeud.isNull()))
        {
            peripherique = noeud.toElement();

            if(peripherique.attribute("uuid") == uuid)
            {
                noeudCanaux = peripherique.firstChild();

                while(!(noeudCanaux.isNull()))
                {
                    canauxElement = noeudCanaux.toElement();

                    listeCanaux->push_back(canauxElement.attribute("id"));
                    typeCanal->push_back(canauxElement.text());

                    noeudCanaux = noeudCanaux.nextSibling();
                }
            }


            noeud = noeud.nextSibling();
        }

    }

    fichierXML.close();
}

void GestionXML::recupererDimmer(QStringList *listeCanaux)
{
    QDomDocument documentXML;
    QFile fichierXML(APPAREILSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Appareils.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement peripherique;

        QDomNode noeudCanaux;
        QDomElement canauxElement;

        while(!(noeud.isNull()))
        {
            peripherique = noeud.toElement();

            noeudCanaux = peripherique.firstChild();

                while(!(noeudCanaux.isNull()))
                {
                    canauxElement = noeudCanaux.toElement();

                    if(canauxElement.text().contains("RED") || canauxElement.text().contains("GREEN") || canauxElement.text().contains("BLUE") || canauxElement.text().contains("DIM") || canauxElement.text().contains("GLOBOS"))
                    {
                        listeCanaux->push_back(canauxElement.attribute("id"));
                    }

                    //listeCanaux->push_back(canauxElement.text());

                    noeudCanaux = noeudCanaux.nextSibling();
                }



            noeud = noeud.nextSibling();
        }

    }

    fichierXML.close();
}

void GestionXML::recupererListeScenarios(QStringList *listeScenarios, QStringList *listeUUID)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENARIOSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenarios.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenarios;

        while(!(noeud.isNull()))
        {
            scenarios = noeud.toElement();
            listeScenarios->push_back(scenarios.attribute("nom"));
            listeUUID->push_back(scenarios.attribute("uuid"));


            noeud = noeud.nextSibling();
        }

    }

    fichierXML.close();
}

void GestionXML::ajouterScenarios(QString nom, QString uuid)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENARIOSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenarios.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();

        QDomElement scenario = documentXML.createElement("scenario");

        racine.appendChild(scenario);

        scenario.setAttribute("nom", nom);
        scenario.setAttribute("uuid", uuid);


        documentXML.save(out, 2);
        fichierXML.close();

    }
}

void GestionXML::recupererListeScenes(QStringList *listeScenes, QStringList *listeUUID, QString scenarioUUID)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenario;



        while(!(noeud.isNull()))
        {
            scenario = noeud.toElement();


            if(scenario.attribute("scenarioUUID") == scenarioUUID)
            {

                listeScenes->push_back(scenario.attribute("nom"));
                listeUUID->push_back(scenario.attribute("uuid"));
            }

            noeud = noeud.nextSibling();
        }
    }

    fichierXML.close();
}

void GestionXML::ajouterScenes(QString nom, QString uuid, QString uuidScenario)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();

        QDomElement scenario = documentXML.createElement("scene");

        racine.appendChild(scenario);

        scenario.setAttribute("nom", nom);
        scenario.setAttribute("uuid", uuid);
        scenario.setAttribute("scenarioUUID", uuidScenario);


        documentXML.save(out, 2);
        fichierXML.close();

    }
}

void GestionXML::enregistrerValeursScenes(QStringList canal, QStringList valeur, QString uuidScene)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);

        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();

        QDomNode noeud = racine.firstChild();
        QDomElement scene;

        QDomNode noeudCanal;
        QDomElement sceneCanal;

        while(!(noeud.isNull()))
        {
            scene = noeud.toElement();

            if(scene.attribute("uuid") == uuidScene)
            {

                noeudCanal = scene.firstChild();
                while(!(noeudCanal.isNull()))
                {
                    scene.removeChild(noeudCanal);
                    noeudCanal = scene.firstChild();
                }

                for(int i =0; i<canal.size(); i++)
                {
                    sceneCanal = documentXML.createElement("canal");
                    sceneCanal.setAttribute("id", canal[i]);
                    sceneCanal.setAttribute("valeur",valeur[i]);

                    scene.appendChild(sceneCanal);

                }



            }

            noeud = noeud.nextSibling();
        }

        documentXML.save(out, 2);
        fichierXML.close();
    }


}

void GestionXML::recupererValeursScenes(QStringList *canal, QStringList *valeur, QString uuidScene)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);


        QDomElement racine = documentXML.documentElement();

        QDomNode noeud = racine.firstChild();
        QDomElement scene;

        QDomNode noeudCanal;
        QDomElement sceneCanal;

        while(!(noeud.isNull()))
        {
            scene = noeud.toElement();

            if(scene.attribute("uuid") == uuidScene)
            {

                noeudCanal = scene.firstChild();

                while(!(noeudCanal.isNull()))
                {
                    sceneCanal = noeudCanal.toElement();

                    canal->push_back(sceneCanal.attribute("id"));
                    valeur->push_back(sceneCanal.attribute("valeur"));

                    noeudCanal = noeudCanal.nextSibling();

                }

            }

            noeud = noeud.nextSibling();
        }
    }
}

void GestionXML::supprimerScenario(QString uuid)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENARIOSXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenarios.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenario;

        while(!(noeud.isNull()))
        {
            scenario = noeud.toElement();

            if(scenario.attribute("uuid") == uuid)
            {

                racine.removeChild(scenario);
            }

            noeud = noeud.nextSibling();
        }

        documentXML.save(out, 2);
        fichierXML.close();

    }

    this->supprimerScenesAssociees(uuid);

}

void GestionXML::supprimerScenesAssociees(QString uuidScenario)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenario;
        std::vector<QDomElement>listeDeScenes;

        while(!(noeud.isNull()))
        {
            scenario = noeud.toElement();
            qDebug() << scenario.attribute("nom");

            if(scenario.attribute("scenarioUUID") == uuidScenario)
            {
                listeDeScenes.push_back(scenario);
                //racine.removeChild(scenario);
            }

            noeud = noeud.nextSibling();
        }

        for(int i = 0; i<listeDeScenes.size(); i++)
        {
            racine.removeChild(listeDeScenes[i]);
        }

        documentXML.save(out, 2);
        fichierXML.close();

    }

}


void GestionXML::supprimerScene(QString uuid)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenario;

        while(!(noeud.isNull()))
        {
            scenario = noeud.toElement();

            if(scenario.attribute("uuid") == uuid)
            {

                racine.removeChild(scenario);
            }

            noeud = noeud.nextSibling();
        }

        documentXML.save(out, 2);
        fichierXML.close();

    }
}

void GestionXML::recupererSequences(QStringList *listeSequences, QStringList *listeUUID)
{
    QDomDocument documentXML;
    QFile fichierXML(SEQUENCESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Sequences.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenario;



        while(!(noeud.isNull()))
        {
            scenario = noeud.toElement();

            listeSequences->push_back(scenario.attribute("nom"));
            listeUUID->push_back(scenario.attribute("uuid"));

            noeud = noeud.nextSibling();
        }
    }

    fichierXML.close();
}

void GestionXML::ajouterSequence(QString nom, QString uuid)
{
    QDomDocument documentXML;
    QFile fichierXML(SEQUENCESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Sequences.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();

        QDomElement scenario = documentXML.createElement("sequence");

        racine.appendChild(scenario);

        scenario.setAttribute("nom", nom);
        scenario.setAttribute("uuid", uuid);


        documentXML.save(out, 2);
        fichierXML.close();

    }
}

void GestionXML::supprimerSequence(QString uuid)
{
    QDomDocument documentXML;
    QFile fichierXML(SEQUENCESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Sequences.xml");
    }
    else
    {

        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);

        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenario;

        while(!(noeud.isNull()))
        {
            scenario = noeud.toElement();

            if(scenario.attribute("uuid") == uuid)
            {

                racine.removeChild(scenario);
            }

            noeud = noeud.nextSibling();
        }

        documentXML.save(out, 2);
        fichierXML.close();

    }
}

void GestionXML::afficherListeScenes(QStringList *listeScenes, QStringList *listeUUIDscene, QStringList *listeUUID)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();
        QDomNode noeud = racine.firstChild();

        QDomElement scenario;



        while(!(noeud.isNull()))
        {
            scenario = noeud.toElement();

            listeScenes->push_back(scenario.attribute("nom"));
            listeUUIDscene->push_back(scenario.attribute("uuidScene"));
            listeUUID->push_back(scenario.attribute("uuid"));



            noeud = noeud.nextSibling();
        }
    }

    fichierXML.close();
}

void GestionXML::recupererContenueSequence(QString uuidSequence, QStringList *temporisation, QStringList *listeUUIDscene, QStringList *listeUUID)
{
    QDomDocument documentXML;
    QFile fichierXML(SEQUENCESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Sequences.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);


        QDomElement racine = documentXML.documentElement();

        QDomNode noeud = racine.firstChild();
        QDomElement scene;

        QDomNode noeudCanal;
        QDomElement sceneCanal;

        while(!(noeud.isNull()))
        {
            scene = noeud.toElement();

            if(scene.attribute("uuid") == uuidSequence)
            {

                noeudCanal = scene.firstChild();

                while(!(noeudCanal.isNull()))
                {
                    sceneCanal = noeudCanal.toElement();

                    listeUUIDscene->push_back(sceneCanal.attribute("uuidScene"));
                    listeUUID->push_back(sceneCanal.attribute("uuid"));
                    temporisation->push_back(sceneCanal.attribute("temporisation"));

                    noeudCanal = noeudCanal.nextSibling();

                }

            }

            noeud = noeud.nextSibling();
        }
    }
}

QString GestionXML::recupererNomScene(QString uuid)
{
    QDomDocument documentXML;
    QFile fichierXML(SCENESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Scenes.xml");
    }
    else
    {
        documentXML.setContent(&fichierXML, false);


        QDomElement racine = documentXML.documentElement();

        QDomNode noeud = racine.firstChild();
        QDomElement scene;

        QDomNode noeudCanal;
        QDomElement sceneCanal;

        while(!(noeud.isNull()))
        {
            scene = noeud.toElement();

            if(scene.attribute("uuid") == uuid)
            {

                noeudCanal = scene.firstChild();

                return scene.attribute("nom");

            }

            noeud = noeud.nextSibling();
        }
    }
}

void GestionXML::ajouterSceneDeSequence(QString uuidSequence, QString uuidScene, QString nouvelUUID, QString temporisation)
{
    QDomDocument documentXML;
    QFile fichierXML(SEQUENCESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Sequences.xml");
    }
    else
    {
        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);
        QDomElement racine = documentXML.documentElement();

        QDomNode noeud = racine.firstChild();
        QDomElement scene;

        QDomNode noeudCanal;
        QDomElement sceneCanal;

        while(!(noeud.isNull()))
        {
            scene = noeud.toElement();

            if(scene.attribute("uuid") == uuidSequence)
            {

                sceneCanal = documentXML.createElement("scene");
                sceneCanal.setAttribute("uuidScene", uuidScene);
                sceneCanal.setAttribute("uuid", nouvelUUID);
                sceneCanal.setAttribute("temporisation", temporisation);

                scene.appendChild(sceneCanal);

            }

            noeud = noeud.nextSibling();
        }
        documentXML.save(out, 2);
        fichierXML.close();
    }
}

void GestionXML::supprimerSceneDeSequence(QString uuidSequence, QString uuidScene)
{
    QDomDocument documentXML;
    QFile fichierXML(SEQUENCESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Sequences.xml");
    }
    else
    {
        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);
        QDomElement racine = documentXML.documentElement();

        QDomNode noeud = racine.firstChild();
        QDomElement scene;

        QDomNode noeudCanal;
        QDomElement sceneCanal;

        while(!(noeud.isNull()))
        {
            scene = noeud.toElement();

            if(scene.attribute("uuid") == uuidSequence)
            {

                noeudCanal = scene.firstChild();

                while(!(noeudCanal.isNull()))
                {
                    sceneCanal = noeudCanal.toElement();

                    if(sceneCanal.attribute("uuid") == uuidScene)
                    {
                        scene.removeChild(sceneCanal);
                    }

                    noeudCanal = noeudCanal.nextSibling();

                }

            }

            noeud = noeud.nextSibling();
        }
        documentXML.save(out, 2);
        fichierXML.close();
    }
}

void GestionXML::supprimerSceneDeSequenceExterne(QString uuidScene)
{
    QDomDocument documentXML;
    QFile fichierXML(SEQUENCESXML);

    if(!(fichierXML.open(QIODevice::ReadOnly)))
    {
        QMessageBox::warning(0,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Sequences.xml");
    }
    else
    {
        if(!(documentXML.setContent(&fichierXML)))
        {
            QDomNode xmlNode = documentXML.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
            documentXML.insertBefore(xmlNode, documentXML.firstChild());

            QDomElement root = documentXML.createElement("theatre2013");
            documentXML.appendChild(root);
        }


        fichierXML.close();
        fichierXML.open(QIODevice::WriteOnly);

        QTextStream out;
        out.setDevice(&fichierXML);
        QDomElement racine = documentXML.documentElement();

        QDomNode noeud = racine.firstChild();
        QDomElement scene;

        QDomNode noeudCanal;
        QDomElement sceneCanal;
        std::vector<QDomElement>listeDeScenes;

        while(!(noeud.isNull()))
        {
            scene = noeud.toElement();

            noeudCanal = scene.firstChild();

                while(!(noeudCanal.isNull()))
                {
                    sceneCanal = noeudCanal.toElement();

                    if(sceneCanal.attribute("uuidScene") == uuidScene)
                    {
                        listeDeScenes.push_back(sceneCanal);
                        //scene.removeChild(sceneCanal);
                    }

                    noeudCanal = noeudCanal.nextSibling();

                }



            noeud = noeud.nextSibling();
        }

        for(int j = 0; j<listeDeScenes.size(); j++)
        {
            scene.removeChild(listeDeScenes[j]);
        }

        documentXML.save(out, 2);
        fichierXML.close();
    }
}
