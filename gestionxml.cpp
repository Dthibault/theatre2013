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

void GestionXML::lireListeAppareils(QStringList *nom, QStringList *UUID)
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

void GestionXML::recupererCanaux(QStringList *listeCanaux, QString uuid)
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

                    noeudCanaux = noeudCanaux.nextSibling();
                }
            }


            noeud = noeud.nextSibling();
        }

    }

    fichierXML.close();
}
