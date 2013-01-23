#include "fenetrecontroledistance.h"
#include "ui_fenetrecontroledistance.h"

FenetreControleDistance::FenetreControleDistance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreControleDistance)
{
    ui->setupUi(this);

    connect(ui->boutonFermer, SIGNAL(clicked()), this, SLOT(fermerFenetre()));
    connect(this, SIGNAL(finished(int)), this, SLOT(fermerFenetre()));

    this->interfaceConsole = new GestionConsole;
    this->interfaceConsole->start();
}

FenetreControleDistance::~FenetreControleDistance()
{
    this->interfaceConsole->stop();
    delete this->interfaceConsole;

    delete ui;
}


void FenetreControleDistance::fermerFenetre()
{
    this->close();
}
