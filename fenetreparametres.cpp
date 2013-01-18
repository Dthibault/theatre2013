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



    GestionXML paramAdaptateurs;
    QString adresse, UUID;
    if(paramAdaptateurs.lireAdaptateur(&adresse, &UUID))
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
    this->interfaceDMX = new GestionDMX;
    this->interfaceDMX->setAdresse(ui->comboBoxAdaptateurs->currentText());

    if(this->interfaceDMX->seConnecter())
    {
        ui->labelNomResult->setText(this->interfaceDMX->getNomInterface());
        ui->labelSerialResult->setText(this->interfaceDMX->getSerialNumber());
        ui->labelPortResult->setText(this->interfaceDMX->getPort());
    }
    else
    {
        ui->labelNomResult->setText("Périphérique NON DMX");
    }

    delete this->interfaceDMX;
}


void FenetreParametres::enregistrerDonnees()
{
    GestionXML paramAdaptateurs;
    QUuid monUuid = QUuid::createUuid ();
    paramAdaptateurs.ecritureAdaptateur(ui->comboBoxAdaptateurs->currentText(), monUuid.toString());
}

void FenetreParametres::modifierPassword()
{
    GestionXML passwordBDD;

    QString ancienBDD;
    passwordBDD.lirePassword(&ancienBDD);

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
        passwordBDD.ecriturePassword(cryptNouveau);

        QMessageBox::information(this, "Mot de passe modifié", "Mot de passe modifié avec succès!");
    }

}
