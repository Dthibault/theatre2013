#include "fenetrecontroledistance.h"
#include "ui_fenetrecontroledistance.h"

FenetreControleDistance::FenetreControleDistance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreControleDistance)
{
    ui->setupUi(this);

    connect(ui->boutonFermer, SIGNAL(clicked()), this, SLOT(fermerFenetre()));
    connect(this, SIGNAL(finished(int)), this, SLOT(fermerFenetre()));


    this->interfaceDMX = new GestionDMX;

    this->interfaceConsole = new GestionConsole;
    this->interfaceConsole->start();

    this->etatPriseEnMain = false;

    ui->labelEtatConnexion->setText("<b><span style=\"color: red;\">CONTROLE NON ACTIF</span></b>");

    connect(this->interfaceConsole, SIGNAL(boutonGO()), this, SLOT(debutControle()));
    connect(this->interfaceConsole, SIGNAL(boutonBACK()), this, SLOT(arretControle()));


}

FenetreControleDistance::~FenetreControleDistance()
{
    this->interfaceConsole->stop();
    delete this->interfaceConsole;

    if(this->etatPriseEnMain)
    {
        this->interfaceDMX->seDeconnecter();
    }

    delete ui;
}


bool FenetreControleDistance::configurerAdaptateur()
{
    GestionXML adaptXML;
    QString adresseAdapt, uuidAdapt;

    if(!(adaptXML.lireAdaptateur(&adresseAdapt, &uuidAdapt)))
    {
        QMessageBox::information(this, "Aucun adaptateur", "L'adaptateur n'a pas été configuré.");
        return false;
    }
    else
    {
        this->interfaceDMX->setAdresse(adresseAdapt);
        return true;
    }
}

void FenetreControleDistance::fermerFenetre()
{
    this->close();
}


void FenetreControleDistance::debutControle()
{

    if(this->configurerAdaptateur())
    {
        this->etatPriseEnMain = true;
        ui->labelEtatConnexion->setText("<b><span style=\"color: green;\">CONTROLE ACTIF</span></b>");

        this->interfaceDMX->seConnecter();
        this->interfaceDMX->resetDMX();
    }

}

void FenetreControleDistance::arretControle()
{
    this->etatPriseEnMain = false;
    ui->labelEtatConnexion->setText("<b><span style=\"color: red;\">CONTROLE NON ACTIF</span></b>");

    this->interfaceDMX->seDeconnecter();
}
