#include "fenetregererappareils.h"
#include "ui_fenetregererappareils.h"

FenetreGererAppareils::FenetreGererAppareils(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreGererAppareils)
{
    ui->setupUi(this);

    connect(ui->boutonFermer, SIGNAL(clicked()), this, SLOT(close()));

    ui->comboBox->addItem("PAR LED");
    ui->comboBox->addItem("Lyre");
    ui->comboBox->addItem("Scanner LED");
    ui->comboBox->addItem("Autre");

    connect(ui->boutonAjouter, SIGNAL(clicked()), this, SLOT(ouvrirFenetreNouveau()));
    connect(ui->boutonEffacer, SIGNAL(clicked()), this, SLOT(effacerAppareil()));


    this->listerAppareils();

}

FenetreGererAppareils::~FenetreGererAppareils()
{
    delete ui;
}


void FenetreGererAppareils::listerAppareils()
{
    QStringList nom, uuid, type;


    GestionXML::lireListeAppareils(&nom, &uuid, &type);

    for(int i=0; i<nom.size(); i++)
    {
        ui->listWidget->addItem(nom[i]);
    }
}

void FenetreGererAppareils::ouvrirFenetreNouveau()
{
    if(ui->comboBox->currentText().contains("Lyre"))
    {
        FenetreAjoutLyre fenetre;
        fenetre.exec();

        ui->listWidget->clear();
        this->listerAppareils();
    }
    else if(ui->comboBox->currentText().contains("PAR LED"))
    {
        FenetreAjoutPar fenetre;
        fenetre.exec();

        ui->listWidget->clear();
        this->listerAppareils();
    }
    else if(ui->comboBox->currentText().contains("Scanner LED"))
    {
        FenetreScannerLED fenetre;
        fenetre.exec();

        ui->listWidget->clear();
        this->listerAppareils();
    }
    else if(ui->comboBox->currentText().contains("Autre"))
    {
        FenetreAjoutAutre fenetre;
        fenetre.exec();

        ui->listWidget->clear();
        this->listerAppareils();
    }

}

void FenetreGererAppareils::effacerAppareil()
{
    QStringList nom, uuid, type;


    GestionXML::lireListeAppareils(&nom, &uuid, &type);


    int choix = QMessageBox::question(this, "Effacer?", "Voulez-vous effacer ce périphérique?", QMessageBox::Yes | QMessageBox::No);

    if(choix == QMessageBox::Yes)
    {
        GestionXML::effacerAppareils(uuid[ui->listWidget->currentRow()]);

        QMessageBox::information(this, "Périphérique effacé", "Le périphérique a été éffacé.");

        ui->listWidget->clear();
        this->listerAppareils();
    }
}
