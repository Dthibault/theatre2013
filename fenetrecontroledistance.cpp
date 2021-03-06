#include "fenetrecontroledistance.h"
#include "ui_fenetrecontroledistance.h"

FenetreControleDistance::FenetreControleDistance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreControleDistance)
{
    ui->setupUi(this);

    connect(ui->boutonFermer, SIGNAL(clicked()), this, SLOT(fermerFenetre()));
    connect(this, SIGNAL(finished(int)), this, SLOT(fermerFenetre()));


    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();


    this->interfaceConsole = new GestionConsole;
    this->interfaceConsole->start();

    this->etatPriseEnMain = false;

    ui->labelEtatConnexion->setText("<b><span style=\"color: red;\">CONTROLE NON ACTIF</span></b>");

    connect(this->interfaceConsole, SIGNAL(boutonGO()), this, SLOT(debutControle()));
    connect(this->interfaceConsole, SIGNAL(boutonBACK()), this, SLOT(arretControle()));
    connect(this->interfaceConsole, SIGNAL(boutonUP()), this, SLOT(augmenterNumero()));
    connect(this->interfaceConsole, SIGNAL(boutonDOWN()), this, SLOT(baisserNumero()));
    connect(this->interfaceConsole, SIGNAL(envoieSliders(int*)), this, SLOT(modifierSliders(int*)));

    this->numeroActuel = 0;
    this->interfaceConsole->modifierNumero(this->numeroActuel);

    ui->labelNumeroActuel->clear();
    ui->labelNumeroActuel->setText("<b>Appareil sélectionné: </b>"+QString::number(this->numeroActuel));

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(afficherNumeroAssignation(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(modifierNumeroAssignation(int)));

    this->listerAppareils();
}

FenetreControleDistance::~FenetreControleDistance()
{
    this->interfaceConsole->stop();
    delete this->interfaceConsole;

    if(this->etatPriseEnMain)
    {
        GestionDMX *interfaceDMX;
        interfaceDMX = GestionDMX::getInstance();

        interfaceDMX->seDeconnecter();
        interfaceDMX->kill();
    }

    delete ui;
}


bool FenetreControleDistance::configurerAdaptateur()
{

    QString adresseAdapt, uuidAdapt;

    if(!(GestionXML::lireAdaptateur(&adresseAdapt, &uuidAdapt)))
    {
        QMessageBox::information(this, "Aucun adaptateur", "L'adaptateur n'a pas été configuré.");
        return false;
    }
    else
    {
        GestionDMX *interfaceDMX;
        interfaceDMX = GestionDMX::getInstance();
        interfaceDMX->setAdresse(adresseAdapt);

        return true;
    }
}

void FenetreControleDistance::fermerFenetre()
{
    this->close();
}

void FenetreControleDistance::listerAppareils()
{
    QStringList nom, uuid, type;


    GestionXML::lireListeAppareils(&nom, &uuid, &type);

    for(int i=0; i<nom.size(); i++)
    {
        ui->listWidget->addItem(nom[i]);
        this->listeNumero.push_back(QString::number(i+1));
    }

    if(nom.size() > 0)
    {
        ui->listWidget->setCurrentRow(0);
    }
}

void FenetreControleDistance::afficherNumeroAssignation(int numero)
{
    ui->spinBox->setValue(this->listeNumero[numero].toInt());
}

void FenetreControleDistance::modifierNumeroAssignation(int numero)
{
    this->listeNumero[ui->listWidget->currentRow()] = QString::number(numero);
}

void FenetreControleDistance::debutControle()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();


    if(this->configurerAdaptateur())
    {
        this->etatPriseEnMain = true;
        ui->labelEtatConnexion->setText("<b><span style=\"color: green;\">CONTROLE ACTIF</span></b>");

        interfaceDMX->seConnecter();
        interfaceDMX->resetDMX();

        this->numeroActuel = 0;
        this->interfaceConsole->modifierNumero(this->numeroActuel);

        ui->spinBox->setDisabled(true);
    }

}

void FenetreControleDistance::arretControle()
{
    this->etatPriseEnMain = false;
    ui->labelEtatConnexion->setText("<b><span style=\"color: red;\">CONTROLE NON ACTIF</span></b>");

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();


    interfaceDMX->seDeconnecter();

    ui->spinBox->setEnabled(true);
}

void FenetreControleDistance::augmenterNumero()
{
    if(this->etatPriseEnMain)
    {


        if(this->numeroActuel < 99)
        {
            this->numeroActuel++;
            this->interfaceConsole->modifierNumero(this->numeroActuel);
        }
        else
        {
            this->numeroActuel = 0;
            this->interfaceConsole->modifierNumero(this->numeroActuel);
        }

        ui->labelNumeroActuel->clear();
        ui->labelNumeroActuel->setText("<b>Appareil sélectionné: </b>"+QString::number(this->numeroActuel));
    }
}

void FenetreControleDistance::baisserNumero()
{
    if(this->etatPriseEnMain)
    {
        if(this->numeroActuel > 0)
        {
            this->numeroActuel--;
            this->interfaceConsole->modifierNumero(this->numeroActuel);
        }
        else
        {
            this->numeroActuel = 99;
            this->interfaceConsole->modifierNumero(this->numeroActuel);
        }

        ui->labelNumeroActuel->clear();
        ui->labelNumeroActuel->setText("<b>Appareil sélectionné: </b>"+QString::number(this->numeroActuel));
    }
}

void FenetreControleDistance::modifierSliders(int * listeSliders)
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    if(this->etatPriseEnMain)
    {
        QStringList nom, uuid, type;


        GestionXML::lireListeAppareils(&nom, &uuid, &type);


        for(int j=0; j<this->listeNumero.size(); j++)
        {
            if(this->numeroActuel == this->listeNumero[j].toInt())
            {
                QStringList maListeDeCanaux, typeCanaux;
                GestionXML::recupererCanaux(&maListeDeCanaux, &typeCanaux, uuid[j]);

                for(int i=0; i<maListeDeCanaux.size(); i++)
                {
                    interfaceDMX->modifierValeurCanal(maListeDeCanaux[i].toInt(), listeSliders[i]);
                    interfaceDMX->envoyerDMX();
                }
            }
        }

    }
}
