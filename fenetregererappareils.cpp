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

}

FenetreGererAppareils::~FenetreGererAppareils()
{
    delete ui;
}
