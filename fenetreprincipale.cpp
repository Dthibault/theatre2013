#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include <QDebug>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    // Modification de l'emplacement des données personnelles
    QDir::setCurrent(QDir::homePath());

    // Mise en place du service de mot de passe
    bool ok = false;
    QString motDePasse = QInputDialog::getText(this, "Accès Restreint", "<b>Seule les personnes autorisées peuvent utiliser ce programme.</b><br><br>Veuillez saisir le mot de passe.", QLineEdit::Password, QString(), &ok);

    if(!ok)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        QString motDePasseActuel;
        GestionXML::lirePassword(&motDePasseActuel);

        QString cryptReponse = QCryptographicHash::hash(motDePasse.toLocal8Bit().constData(),QCryptographicHash::Sha1).toHex();

        qDebug() << motDePasse;
        qDebug() << cryptReponse;
        if(cryptReponse!=motDePasseActuel)
        {
            QMessageBox::warning(this, "Accès Refusé", "Mot de passe incorrect");
            exit(EXIT_SUCCESS);
        }
    }





    connect(ui->actionParam_tres, SIGNAL(triggered()), this, SLOT(ouvrirParametres()));
    connect(ui->actionG_rer_appareils, SIGNAL(triggered()), this, SLOT(ouvrirGererAppareils()));
    connect(ui->actionCont_le_distant, SIGNAL(triggered()), this, SLOT(ouvrirControleDistance()));
    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    this->boutonModeScenes = new QPushButton("Mode Scènes", this);
    this->boutonModeSequences = new QPushButton("Mode Séquences", this);
    this->boutonFermerMode = new QPushButton("Fermer", this);

    ui->statusbar->addPermanentWidget(this->boutonModeScenes);
    ui->statusbar->addPermanentWidget(this->boutonModeSequences);
    ui->statusbar->addPermanentWidget(this->boutonFermerMode);

    this->boutonFermerMode->setDisabled(true);

    connect(this->boutonModeScenes, SIGNAL(clicked()), this, SLOT(afficherModeScenes()));
    connect(this->boutonModeSequences, SIGNAL(clicked()), this, SLOT(afficherModeSequences()));
    connect(this->boutonFermerMode, SIGNAL(clicked()), this, SLOT(fermerMode()));

    this->typeMode = 0;

}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}


void FenetrePrincipale::ouvrirParametres()
{
    FenetreParametres fenetre;
    fenetre.exec();
}


void FenetrePrincipale::ouvrirGererAppareils()
{

    QString addrApp, uuidApp;

    GestionXML::lireAdaptateur(&addrApp, &uuidApp);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(addrApp);




    if(!(GestionXML::lireAdaptateur(&addrApp, &uuidApp)) || !(interfaceDMX->estDisponible()))
    {
        QMessageBox::information(this, "Configuration de l'adaptateur", "Vous devez tout d'abord configurer correctement l'adaptateur ou le connecter.");
    }
    else
    {
        FenetreGererAppareils fenetre;
        fenetre.exec();
    }
}

void FenetrePrincipale::ouvrirControleDistance()
{


    QString addrApp, uuidApp;

    GestionXML::lireAdaptateur(&addrApp, &uuidApp);
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(addrApp);


    if(!(GestionXML::lireAdaptateur(&addrApp, &uuidApp)) || !(interfaceDMX->estDisponible()))
    {
        QMessageBox::information(this, "Configuration de l'adaptateur", "Vous devez tout d'abord configurer correctement l'adaptateur ou le connecter.");
    }
    else
    {
        FenetreControleDistance fenetre;
        fenetre.exec();
    }

}

void FenetrePrincipale::afficherModeScenes()
{

    QString addrApp, uuidApp;

    GestionXML::lireAdaptateur(&addrApp, &uuidApp);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(addrApp);


    if(!(GestionXML::lireAdaptateur(&addrApp, &uuidApp)) || !(interfaceDMX->estDisponible()))
    {
        QMessageBox::information(this, "Configuration de l'adaptateur", "Vous devez tout d'abord configurer correctement l'adaptateur ou le connecter.");
    }
    else
    {
        ui->horizontalLayout->removeWidget(ui->conteneurGenerale);
        ui->conteneurGenerale->hide();

        this->gestionScenes = new WidgetGestionScenes;
        ui->horizontalLayout->addWidget(this->gestionScenes);

        this->boutonModeScenes->setDisabled(true);
        this->boutonModeSequences->setDisabled(true);
        this->boutonFermerMode->setEnabled(true);

        this->typeMode = 1;

        ui->menuConsole->setDisabled(true);
        ui->actionG_rer_appareils->setDisabled(true);
        ui->actionParam_tres->setDisabled(true);
    }



}

void FenetrePrincipale::afficherModeSequences()
{

    QString addrApp, uuidApp;

    GestionXML::lireAdaptateur(&addrApp, &uuidApp);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(addrApp);


    if(!(GestionXML::lireAdaptateur(&addrApp, &uuidApp)) || !(interfaceDMX->estDisponible()))
    {
        QMessageBox::information(this, "Configuration de l'adaptateur", "Vous devez tout d'abord configurer correctement l'adaptateur ou le connecter.");
    }
    else
    {
        ui->horizontalLayout->removeWidget(ui->conteneurGenerale);
        ui->conteneurGenerale->hide();

        this->gestionSequences = new WidgetGestionSequences;
        ui->horizontalLayout->addWidget(this->gestionSequences);

        this->boutonModeScenes->setDisabled(true);
        this->boutonModeSequences->setDisabled(true);
        this->boutonFermerMode->setEnabled(true);

        this->typeMode = 2;

        ui->menuConsole->setDisabled(true);
        ui->actionG_rer_appareils->setDisabled(true);
        ui->actionParam_tres->setDisabled(true);
    }

}

void FenetrePrincipale::fermerMode()
{
    if(this->typeMode == 1)
    {
        ui->horizontalLayout->removeWidget(this->gestionScenes);
        delete this->gestionScenes;

        ui->menuConsole->setEnabled(true);
        ui->actionG_rer_appareils->setEnabled(true);
        ui->actionParam_tres->setEnabled(true);
    }
    else if(this->typeMode == 2)
    {
        ui->horizontalLayout->removeWidget(this->gestionSequences);
        delete this->gestionSequences;

        ui->menuConsole->setEnabled(true);
        ui->actionG_rer_appareils->setEnabled(true);
        ui->actionParam_tres->setEnabled(true);
    }

    this->boutonModeScenes->setEnabled(true);
    this->boutonModeSequences->setEnabled(true);
    this->boutonFermerMode->setDisabled(true);

    this->typeMode = 0;

    ui->horizontalLayout->addWidget(ui->conteneurGenerale);
    ui->conteneurGenerale->show();

}

