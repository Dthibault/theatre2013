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

    if(!(lireApp.lireAdaptateur(&addrApp, &uuidApp)))
    {
        QMessageBox::information(this, "Configuration de l'adaptateur", "Vous devez tout d'abord configurer correctement l'adaptateur.");
    }
    else
    {
        FenetreGererAppareils fenetre;
        fenetre.exec();
    }
}

void FenetrePrincipale::ouvrirControleDistance()
{
    FenetreControleDistance fenetre;
    fenetre.exec();
}
