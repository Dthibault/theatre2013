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


//    connect(ui->boutonDimmer, SIGNAL(clicked()), this, SLOT(testDimmer()));

//    this->interfaceDMX = new GestionDMX(this);

//    GestionXML monXML;
//    QStringList test1;

//    monXML.recupererCanaux(&test1, "{f163b05a-58bf-46d9-887b-a4e9a0ad8f11}");

//    this->interfaceDMX->setAdresse("/dev/ttyUSB0");
//    this->interfaceDMX->seConnecter();


//    for(int i = 0; i < test1.size(); i++)
//    {
//        this->interfaceDMX->modifierValeurCanal(test1[i].toInt(), 255);
//    }

//    this->interfaceDMX->modifierValeurCanal(4, 128);

//    this->interfaceDMX->modifierValeurCanal(192, 255);
//    this->interfaceDMX->modifierValeurCanal(193, 255);
//    this->interfaceDMX->modifierValeurCanal(194, 255);



//    this->interfaceDMX->modifierValeurCanal(14, 255);
//    this->interfaceDMX->envoyerDMX();

//    qDebug() << test1;

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

//void FenetrePrincipale::testDimmer()
//{
//    this->interfaceDMX->faireDimmerCanal(3, 255);
//    this->interfaceDMX->faireDimmerCanal(2, 255);
//    this->interfaceDMX->faireDimmerCanal(1, 255);
//    this->interfaceDMX->faireDimmerCanal(4, 128);

//    this->interfaceDMX->faireDimmerCanal(192, 255);
//    this->interfaceDMX->faireDimmerCanal(193, 255);
//    this->interfaceDMX->faireDimmerCanal(194, 255);



//}
