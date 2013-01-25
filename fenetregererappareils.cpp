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
    ui->comboBox->addItem("Scanner");

    connect(ui->boutonAjouter, SIGNAL(clicked()), this, SLOT(ouvrirFenetreNouveau()));


    this->listerAppareils();

}

FenetreGererAppareils::~FenetreGererAppareils()
{
    delete ui;
}


void FenetreGererAppareils::listerAppareils()
{
    QStringList nom, uuid;

    GestionXML monXML;
    monXML.lireListeAppareils(&nom, &uuid);

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
    }

}
