#include "fenetreajoutpar.h"
#include "ui_fenetreajoutpar.h"

FenetreAjoutPar::FenetreAjoutPar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreAjoutPar)
{
    ui->setupUi(this);


    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    this->configurerAdaptateur();

    interfaceDMX->seConnecter();
    interfaceDMX->resetDMX();

    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(fermer()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(confirmationAppareil()));

    connect(ui->verticalSliderRED, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderGREEN, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));
    connect(ui->verticalSliderBLUE, SIGNAL(valueChanged(int)), this, SLOT(miseAJourDMX()));

    connect(ui->spinBoxSuppl, SIGNAL(valueChanged(int)), this, SLOT(modifierNombreWidgetSuppl()));

    this->nbAjouts = 0;

    this->layoutSuppl = new QVBoxLayout;
    //ui->conteneurSuppl2->setLayout(this->layoutSuppl);
    ui->scrollAreaWidgetContents->setLayout(this->layoutSuppl);
}

FenetreAjoutPar::~FenetreAjoutPar()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    interfaceDMX->seDeconnecter();
    interfaceDMX->kill();

    delete ui;
}


void FenetreAjoutPar::configurerAdaptateur()
{

    QString adresseAdapt, uuidAdapt;

    GestionXML::lireAdaptateur(&adresseAdapt, &uuidAdapt);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(adresseAdapt);



}

void FenetreAjoutPar::miseAJourDMX()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    interfaceDMX->modifierValeurCanal(ui->spinBoxRED->value(), ui->verticalSliderRED->value());
    interfaceDMX->modifierValeurCanal(ui->spinBoxGREEN->value(), ui->verticalSliderGREEN->value());
    interfaceDMX->modifierValeurCanal(ui->spinBoxBLUE->value(), ui->verticalSliderBLUE->value());

    if(this->nbAjouts > 0)
    {
        for(int i=0; i<this->nbAjouts; i++)
        {
            interfaceDMX->modifierValeurCanal(this->listeWidgetSuppl[i]->getNumeroCanal(), this->listeWidgetSuppl[i]->getValeurCanal());
        }
    }

    interfaceDMX->envoyerDMX();


}


void FenetreAjoutPar::fermer()
{
    this->close();
}

void FenetreAjoutPar::confirmationAppareil()
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

            nbCanal.push_back(QString::number(ui->spinBoxRED->value()));
            nbCanal.push_back(QString::number(ui->spinBoxGREEN->value()));
            nbCanal.push_back(QString::number(ui->spinBoxBLUE->value()));

            actionCanal.push_back("RED");
            actionCanal.push_back("GREEN");
            actionCanal.push_back("BLUE");


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


            GestionXML::ajouterAppareil(nomfichier, monUuid.toString(), QString::number(nombreCanals), "PAR LED", nbCanal, actionCanal);

            QMessageBox::information(this, "Succès", "Appareil enregistré avec succès!");
            this->close();

        }
    }
}

void FenetreAjoutPar::modifierNombreWidgetSuppl()
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
