#include "fenetreajoutlyre.h"
#include "ui_fenetreajoutlyre.h"

FenetreAjoutLyre::FenetreAjoutLyre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreAjoutLyre)
{
    ui->setupUi(this);

    this->interfaceDMX = new GestionDMX;
    this->configurerAdaptateur();

    this->interfaceDMX->seConnecter();
    this->interfaceDMX->resetDMX();

    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(fermer()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(confirmationAppareil()));

    connect(ui->verticalSliderPAN, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderTILT, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderGLOBOS, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderCOULEUR, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));



}

FenetreAjoutLyre::~FenetreAjoutLyre()
{
    this->interfaceDMX->seDeconnecter();

    delete ui;
}



void FenetreAjoutLyre::configurerAdaptateur()
{
    GestionXML adaptXML;
    QString adresseAdapt, uuidAdapt;

    adaptXML.lireAdaptateur(&adresseAdapt, &uuidAdapt);

    this->interfaceDMX->setAdresse(adresseAdapt);

}

void FenetreAjoutLyre::miseAJourDMX()
{
    this->interfaceDMX->modifierValeurCanal(ui->spinBoxPAN->value(), ui->verticalSliderPAN->value());
    this->interfaceDMX->modifierValeurCanal(ui->spinBoxTILT->value(), ui->verticalSliderTILT->value());
    this->interfaceDMX->modifierValeurCanal(ui->spinBoxGLOBOS->value(), ui->verticalSliderGLOBOS->value());
    this->interfaceDMX->modifierValeurCanal(ui->spinBoxCOULEUR->value(), ui->verticalSliderCOULEUR->value());

    this->interfaceDMX->envoyerDMX();
}


void FenetreAjoutLyre::fermer()
{
    this->close();
}

void FenetreAjoutLyre::confirmationAppareil()
{
    bool ok;
    QString nomfichier = QInputDialog::getText(this, "Nom de l'appareil", "Indiquer le nom du nouvel appareil: ", QLineEdit::Normal, QString(), &ok);

    if(ok)
    {
        if(nomfichier.isEmpty())
        {
            QMessageBox::warning(this, "Indiquer un nom valide", "Le champ doit être remplie.");
        }
        else
        {
            GestionXML monXML;


            QMessageBox::information(this, "Succès", "Appareil enregistré avec succès!");
            this->close();

        }
    }
}
