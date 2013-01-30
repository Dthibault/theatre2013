#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);


    connect(ui->actionParam_tres, SIGNAL(triggered()), this, SLOT(ouvrirParametres()));
    connect(ui->actionG_rer_appareils, SIGNAL(triggered()), this, SLOT(ouvrirGererAppareils()));
    connect(ui->actionCont_le_distant, SIGNAL(triggered()), this, SLOT(ouvrirControleDistance()));
    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));




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
    GestionXML lireApp;
    QString addrApp, uuidApp;

    lireApp.lireAdaptateur(&addrApp, &uuidApp);
    this->interfaceDMX = new GestionDMX;
    this->interfaceDMX->setAdresse(addrApp);


    qDebug() << this->interfaceDMX->estDisponible();

    if(!(lireApp.lireAdaptateur(&addrApp, &uuidApp)) || !(this->interfaceDMX->estDisponible()))
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

    GestionXML lireApp;
    QString addrApp, uuidApp;

    lireApp.lireAdaptateur(&addrApp, &uuidApp);
    this->interfaceDMX = new GestionDMX;
    this->interfaceDMX->setAdresse(addrApp);


    qDebug() << this->interfaceDMX->estDisponible();

    if(!(lireApp.lireAdaptateur(&addrApp, &uuidApp)) || !(this->interfaceDMX->estDisponible()))
    {
        QMessageBox::information(this, "Configuration de l'adaptateur", "Vous devez tout d'abord configurer correctement l'adaptateur ou le connecter.");
    }
    else
    {
        FenetreControleDistance fenetre;
        fenetre.exec();
    }

}
