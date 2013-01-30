#include "fenetrescannerled.h"
#include "ui_fenetrescannerled.h"

FenetreScannerLED::FenetreScannerLED(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreScannerLED)
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
    connect(ui->verticalSliderCOULEUR, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));

    connect(ui->spinBoxSuppl, SIGNAL(valueChanged(int)), this, SLOT(modifierNombreWidgetSuppl()));

    this->nbAjouts = 0;

    this->layoutSuppl = new QVBoxLayout;

    ui->scrollAreaWidgetContents->setLayout(this->layoutSuppl);
}

FenetreScannerLED::~FenetreScannerLED()
{
    this->interfaceDMX->seDeconnecter();

    delete ui;
}


void FenetreScannerLED::configurerAdaptateur()
{
    GestionXML adaptXML;
    QString adresseAdapt, uuidAdapt;

    adaptXML.lireAdaptateur(&adresseAdapt, &uuidAdapt);

    this->interfaceDMX->setAdresse(adresseAdapt);

}

void FenetreScannerLED::miseAJourDMX()
{
    this->interfaceDMX->modifierValeurCanal(ui->spinBoxPAN->value(), ui->verticalSliderPAN->value());
    this->interfaceDMX->modifierValeurCanal(ui->spinBoxTILT->value(), ui->verticalSliderTILT->value());
    this->interfaceDMX->modifierValeurCanal(ui->spinBoxCOULEUR->value(), ui->verticalSliderCOULEUR->value());

    if(this->nbAjouts > 0)
    {
        for(int i=0; i<this->nbAjouts; i++)
        {
            this->interfaceDMX->modifierValeurCanal(this->listeWidgetSuppl[i]->getNumeroCanal(), this->listeWidgetSuppl[i]->getValeurCanal());
        }
    }

    this->interfaceDMX->envoyerDMX();


}


void FenetreScannerLED::fermer()
{
    this->close();
}

void FenetreScannerLED::confirmationAppareil()
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
            QStringList nbCanal, actionCanal;

            nbCanal.push_back(QString::number(ui->spinBoxPAN->value()));
            nbCanal.push_back(QString::number(ui->spinBoxTILT->value()));
            nbCanal.push_back(QString::number(ui->spinBoxCOULEUR->value()));

            actionCanal.push_back("PAN");
            actionCanal.push_back("TILT");
            actionCanal.push_back("GLOBOS");
            actionCanal.push_back("COULEUR");

            for(int i=0; i<this->nbAjouts; i++)
            {
                nbCanal.push_back(QString::number(this->listeWidgetSuppl[i]->getNumeroCanal()));

                if(this->listeWidgetSuppl[i]->getNomCanal().isEmpty())
                {
                    actionCanal.push_back("SUPPL");
                }
                else
                {
                    actionCanal.push_back(this->listeWidgetSuppl[i]->getNomCanal());
                }
            }

            QUuid monUuid = QUuid::createUuid();
            int nombreCanals = 3+this->nbAjouts;


            monXML.ajouterAppareil(nomfichier, monUuid.toString(), QString::number(nombreCanals), "LYRE", nbCanal, actionCanal);

            QMessageBox::information(this, "Succès", "Appareil enregistré avec succès!");
            this->close();

        }
    }
}

void FenetreScannerLED::modifierNombreWidgetSuppl()
{
    if(ui->spinBoxSuppl->value() >= 0)
    {


        if(ui->spinBoxSuppl->value() > this->nbAjouts)
        {

            this->listeWidgetSuppl.push_back(new WidgetCanalSuppl);

            this->layoutSuppl->addWidget(this->listeWidgetSuppl[this->nbAjouts]);
            this->listeWidgetSuppl[this->nbAjouts]->setValeur(this->nbAjouts+1);

            connect(this->listeWidgetSuppl[this->nbAjouts], SIGNAL(changementSlider()), this, SLOT(miseAJourDMX()));


            this->nbAjouts++;
        }
        else if(ui->spinBoxSuppl->value() < this->nbAjouts)
        {
            this->layoutSuppl->removeWidget(this->listeWidgetSuppl[this->nbAjouts]);




            this->listeWidgetSuppl.pop_back();
            delete this->listeWidgetSuppl[ui->spinBoxSuppl->value()];

            this->nbAjouts--;
        }
    }
}

