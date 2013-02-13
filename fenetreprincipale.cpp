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

void FenetrePrincipale::afficherModeScenes()
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
