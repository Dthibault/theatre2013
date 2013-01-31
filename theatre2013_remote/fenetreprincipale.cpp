#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}
