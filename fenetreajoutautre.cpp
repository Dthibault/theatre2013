#include "fenetreajoutautre.h"
#include "ui_fenetreajoutautre.h"

FenetreAjoutAutre::FenetreAjoutAutre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreAjoutAutre)
{
    ui->setupUi(this);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    this->configurerAdaptateur();

    interfaceDMX->seConnecter();
    interfaceDMX->resetDMX();

    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(fermer()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(confirmationAppareil()));

    connect(ui->spinBoxSuppl, SIGNAL(valueChanged(int)), this, SLOT(modifierNombreWidgetSuppl()));

    this->nbAjouts = 0;

    this->layoutSuppl = new QVBoxLayout;

    ui->scrollAreaWidgetContents->setLayout(this->layoutSuppl);
}

FenetreAjoutAutre::~FenetreAjoutAutre()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    interfaceDMX->seDeconnecter();
    interfaceDMX->kill();

    delete ui;
}


void FenetreAjoutAutre::configurerAdaptateur()
{

    QString adresseAdapt, uuidAdapt;

    GestionXML::lireAdaptateur(&adresseAdapt, &uuidAdapt);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(adresseAdapt);


}

void FenetreAjoutAutre::miseAJourDMX()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();


    if(this->nbAjouts > 0)
    {
        for(int i=0; i<this->nbAjouts; i++)
        {
            interfaceDMX->modifierValeurCanal(this->listeWidgetSuppl[i]->getNumeroCanal(), this->listeWidgetSuppl[i]->getValeurCanal());
        }
    }

    interfaceDMX->envoyerDMX();


}


void FenetreAjoutAutre::fermer()
{
    this->close();
}

void FenetreAjoutAutre::confirmationAppareil()
{

    if(ui->spinBoxSuppl->value() == 0)
    {
        QMessageBox::information(this, "Problème", "Merci de renseigner au moins un canal.");
    }
    else
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
                int nombreCanals = this->nbAjouts;


                GestionXML::ajouterAppareil(nomfichier, monUuid.toString(), QString::number(nombreCanals), "AUTRE", nbCanal, actionCanal);

                QMessageBox::information(this, "Succès", "Appareil enregistré avec succès!");
                this->close();

            }
        }

    }

}

void FenetreAjoutAutre::modifierNombreWidgetSuppl()
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
