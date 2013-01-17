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
