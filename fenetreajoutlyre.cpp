#include "fenetreajoutlyre.h"
#include "ui_fenetreajoutlyre.h"

FenetreAjoutLyre::FenetreAjoutLyre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreAjoutLyre)
{
    ui->setupUi(this);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    this->configurerAdaptateur();

    interfaceDMX->seConnecter();
    interfaceDMX->resetDMX();

    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(fermer()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(confirmationAppareil()));

    connect(ui->verticalSliderPAN, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderTILT, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderGLOBOS, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderCOULEUR, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));

    connect(ui->spinBoxPAN, SIGNAL(valueChanged(int)), this, SLOT(verifierCanal()));
    connect(ui->spinBoxTILT, SIGNAL(valueChanged(int)), this, SLOT(verifierCanal()));
    connect(ui->spinBoxCOULEUR, SIGNAL(valueChanged(int)), this, SLOT(verifierCanal()));
    connect(ui->spinBoxGLOBOS, SIGNAL(valueChanged(int)), this, SLOT(verifierCanal()));

    connect(ui->spinBoxSuppl, SIGNAL(valueChanged(int)), this, SLOT(modifierNombreWidgetSuppl()));

    this->nbAjouts = 0;

    this->layoutSuppl = new QVBoxLayout;
    //ui->conteneurSuppl2->setLayout(this->layoutSuppl);
    ui->scrollAreaWidgetContents->setLayout(this->layoutSuppl);

}

FenetreAjoutLyre::~FenetreAjoutLyre()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    interfaceDMX->seDeconnecter();
    interfaceDMX->kill();

    delete ui;
}



void FenetreAjoutLyre::configurerAdaptateur()
{

    QString adresseAdapt, uuidAdapt;

    GestionXML::lireAdaptateur(&adresseAdapt, &uuidAdapt);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(adresseAdapt);


}

void FenetreAjoutLyre::miseAJourDMX()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    interfaceDMX->modifierValeurCanal(ui->spinBoxPAN->value(), ui->verticalSliderPAN->value());
    interfaceDMX->modifierValeurCanal(ui->spinBoxTILT->value(), ui->verticalSliderTILT->value());
    interfaceDMX->modifierValeurCanal(ui->spinBoxGLOBOS->value(), ui->verticalSliderGLOBOS->value());
    interfaceDMX->modifierValeurCanal(ui->spinBoxCOULEUR->value(), ui->verticalSliderCOULEUR->value());

    if(this->nbAjouts > 0)
    {
        for(int i=0; i<this->nbAjouts; i++)
        {
            interfaceDMX->modifierValeurCanal(this->listeWidgetSuppl[i]->getNumeroCanal(), this->listeWidgetSuppl[i]->getValeurCanal());
        }
    }

    interfaceDMX->envoyerDMX();


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

            QStringList nbCanal, actionCanal;

            nbCanal.push_back(QString::number(ui->spinBoxPAN->value()));
            nbCanal.push_back(QString::number(ui->spinBoxTILT->value()));
            nbCanal.push_back(QString::number(ui->spinBoxGLOBOS->value()));
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
            int nombreCanals = 4+this->nbAjouts;


            GestionXML::ajouterAppareil(nomfichier, monUuid.toString(), QString::number(nombreCanals), "LYRE", nbCanal, actionCanal);

            QMessageBox::information(this, "Succès", "Appareil enregistré avec succès!");
            this->close();

        }
    }
}

void FenetreAjoutLyre::modifierNombreWidgetSuppl()
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

void FenetreAjoutLyre::verifierCanal()
{
    QStringList listeCanaux;
    GestionXML::recupererToutLesCanaux(&listeCanaux);

    bool existantPAN = false;
    bool existantTILT = false;
    bool existantCOULEUR = false;
    bool existantGLOBOS = false;

    for(int i = 0; i<listeCanaux.size(); i++)
    {
        if(ui->spinBoxPAN->value() == listeCanaux[i].toInt()) existantPAN = true;
        if(ui->spinBoxTILT->value() == listeCanaux[i].toInt()) existantTILT = true;
        if(ui->spinBoxCOULEUR->value() == listeCanaux[i].toInt()) existantCOULEUR = true;
        if(ui->spinBoxGLOBOS->value() == listeCanaux[i].toInt()) existantGLOBOS = true;
    }

    if(existantPAN)
    {
        ui->spinBoxPAN->setStyleSheet("color: Orange;");
    }
    else
    {
        ui->spinBoxPAN->setStyleSheet("color: black");
    }

    if(existantTILT)
    {
        ui->spinBoxTILT->setStyleSheet("color: Orange;");
    }
    else
    {
        ui->spinBoxTILT->setStyleSheet("color: black");
    }

    if(existantCOULEUR)
    {
        ui->spinBoxCOULEUR->setStyleSheet("color: Orange;");
    }
    else
    {
        ui->spinBoxCOULEUR->setStyleSheet("color: black");
    }

    if(existantGLOBOS)
    {
        ui->spinBoxGLOBOS->setStyleSheet("color: Orange;");
    }
    else
    {
        ui->spinBoxGLOBOS->setStyleSheet("color: black");
    }
}
