#include "fenetreajoutlyre.h"
#include "ui_fenetreajoutlyre.h"

FenetreAjoutLyre::FenetreAjoutLyre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreAjoutLyre)
{
    ui->setupUi(this);
}

FenetreAjoutLyre::~FenetreAjoutLyre()
{
    delete ui;
}
