#include "fenetreparametres.h"
#include "ui_fenetreparametres.h"

FenetreParametres::FenetreParametres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreParametres)
{
    ui->setupUi(this);

    ui->boutonInformations->setDisabled(true);

//    QUuid monUuid = QUuid::createUuid ();
//    qDebug() << "\n\nMon UUID: " << monUuid.toString() << "\n\n";

    this->verifierPeripheriquesSysteme();

    connect(ui->comboBoxAdaptateurs, SIGNAL(activated(QString)), this, SLOT(switchBouton(QString)));
    connect(ui->boutonInformations, SIGNAL(clicked()), this, SLOT(recupererInformations()));
}

FenetreParametres::~FenetreParametres()
{
    delete ui;
}


void FenetreParametres::verifierPeripheriquesSysteme()
{
    int nombre = 0, boucle = 0;

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
}
