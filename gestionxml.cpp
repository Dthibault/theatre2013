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
    }
    else
    {
        documentXML.setContent(&fichierXML, false);
        QDomElement racine = documentXML.documentElement();

        if(racine.isNull())
        {
            qDebug() << "Mais c'est vide";
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
    QStringList resultat;

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

        if(!(racine.isNull()))
        {

            QDomElement unElement = racine.firstChildElement();
            unElement = racine.lastChildElement();

            nom->push_back(unElement.attribute("nom")); // Le nom du périphérique


        }

    }

    fichierXML.close();
}
