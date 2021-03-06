#include "fenetreparametres.h"
#include "ui_fenetreparametres.h"



FenetreParametres::FenetreParametres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreParametres)
{
    ui->setupUi(this);



    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(enregistrerDonnees()));


    connect(ui->comboBoxAdaptateurs, SIGNAL(activated(QString)), this, SLOT(switchBouton(QString)));
    connect(ui->boutonInformations, SIGNAL(clicked()), this, SLOT(recupererInformations()));
    connect(ui->boutonDetection, SIGNAL(clicked()), this, SLOT(verifierPeripheriquesSysteme()));

    connect(ui->boutonModifierMDP, SIGNAL(clicked()), this, SLOT(modifierPassword()));
    connect(ui->boutonEffacer, SIGNAL(clicked()), this, SLOT(effacerConfiguration()));




    QString adresse, UUID;
    if(GestionXML::lireAdaptateur(&adresse, &UUID))
    {
        ui->comboBoxAdaptateurs->addItem(adresse);
        ui->boutonInformations->setEnabled(true);
    }
    else
    {
        ui->comboBoxAdaptateurs->addItem("Faire détection");
        ui->boutonInformations->setDisabled(true);
    }

//    qDebug() << QCryptographicHash::hash("data",QCryptographicHash::Sha1).toHex();
//    paramAdaptateurs.ecriturePassword(QCryptographicHash::hash("data",QCryptographicHash::Sha1).toHex());
//    QString lol;
//    paramAdaptateurs.lirePassword(&lol);
//    qDebug() << lol;

}

FenetreParametres::~FenetreParametres()
{
    delete ui;
}


void FenetreParametres::verifierPeripheriquesSysteme()
{
    int nombre = 0, boucle = 0;
    ui->comboBoxAdaptateurs->clear();

    QFile *fichier;

    for(boucle=0;boucle<9;boucle++)
    {
        fichier = new QFile("/dev/ttyUSB"+QString::number(boucle));

        if((fichier->open(QIODevice::ReadOnly)))
        {
            nombre++;
            ui->comboBoxAdaptateurs->addItem("/dev/ttyUSB"+QString::number(boucle));

        }
        delete fichier;
    }

    if(nombre == 0)
    {
        ui->comboBoxAdaptateurs->addItem("Aucun périphérique");
    }
    else
    {
        ui->comboBoxAdaptateurs->setInsertPolicy(QComboBox::InsertAtTop);
        ui->comboBoxAdaptateurs->insertItem(0, "Veuillez choisir");
        ui->comboBoxAdaptateurs->insertSeparator(1);

    }
    ui->comboBoxAdaptateurs->setCurrentIndex(0);
}


void FenetreParametres::switchBouton(QString choix)
{
    if(choix.contains("ttyUSB"))
    {
        ui->boutonInformations->setEnabled(true);
    }
    else
    {
        ui->boutonInformations->setDisabled(true);
        ui->labelNomResult->clear();
        ui->labelPortResult->clear();
        ui->labelSerialResult->clear();
    }
}

void FenetreParametres::recupererInformations()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(ui->comboBoxAdaptateurs->currentText());


    if(interfaceDMX->seConnecter())
    {
        ui->labelNomResult->setText(interfaceDMX->getNomInterface());
        ui->labelSerialResult->setText(interfaceDMX->getSerialNumber());
        ui->labelPortResult->setText(interfaceDMX->getPort());
    }
    else
    {
        ui->labelNomResult->setText("Périphérique NON DMX");
    }

    interfaceDMX->kill();
}


void FenetreParametres::enregistrerDonnees()
{


    if(!(ui->comboBoxAdaptateurs->currentText().contains("ttyUSB")))
    {
        GestionXML::effacerAdaptateur();
    }
    else
    {

        QUuid monUuid = QUuid::createUuid ();
        GestionXML::ecritureAdaptateur(ui->comboBoxAdaptateurs->currentText(), monUuid.toString());
    }
}

void FenetreParametres::modifierPassword()
{


    QString ancienBDD;
    GestionXML::lirePassword(&ancienBDD);

    QString cryptAncienLineEdit = QCryptographicHash::hash(ui->lineEditAncienMDP->text().toLocal8Bit().constData(),QCryptographicHash::Sha1).toHex();

    if(cryptAncienLineEdit != ancienBDD)
    {
        QMessageBox::warning(this,"Ancien mot de passe","L'ancien mot de passe ne correspond pas à celui enregistré.");
    }
    else if(ui->lineEditNouveauMDP->text() != ui->lineEditNouveauMDP2->text())
    {
        QMessageBox::warning(this,"Nouveau mot de passe","Les nouveaux mots de passes ne correspondent pas.");
    }
    else
    {
        QString cryptNouveau = QCryptographicHash::hash(ui->lineEditNouveauMDP->text().toLocal8Bit().constData(),QCryptographicHash::Sha1).toHex();
        GestionXML::ecriturePassword(cryptNouveau);

        QMessageBox::information(this, "Mot de passe modifié", "Mot de passe modifié avec succès!");
    }

}


void FenetreParametres::effacerConfiguration()
{
    int choix = QMessageBox::question(this, "Confirmation", "Confirmez-vous l'effacement de la configuration?", QMessageBox::Yes | QMessageBox::No);

    if(choix == QMessageBox::Yes)
    {

        GestionXML::effacerAdaptateur();

        QMessageBox::information(this, "Configuration effacée", "La configuration a été éffacée.");
        this->close();
    }
}
