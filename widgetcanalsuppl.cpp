#include "widgetcanalsuppl.h"
#include "ui_widgetcanalsuppl.h"

WidgetCanalSuppl::WidgetCanalSuppl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCanalSuppl)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(envoyerChangement(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(verifierCanal()));
}

WidgetCanalSuppl::~WidgetCanalSuppl()
{
    disconnect(ui->horizontalSlider, 0, 0, 0);
    delete ui;
}


void WidgetCanalSuppl::setValeur(int valeur)
{
    ui->spinBox->setValue(valeur);
}


int WidgetCanalSuppl::getNumeroCanal()
{
    return ui->spinBox->value();
}

QString WidgetCanalSuppl::getNomCanal()
{
    return ui->lineEdit->text();
}

void WidgetCanalSuppl::envoyerChangement(int valeur)
{
    emit changementSlider();
}

int WidgetCanalSuppl::getValeurCanal()
{
    return ui->horizontalSlider->value();
}

void WidgetCanalSuppl::verifierCanal()
{
    QStringList listeCanaux;
    GestionXML::recupererToutLesCanaux(&listeCanaux);

    bool canalPris = false;

    for(int i = 0; i<listeCanaux.size(); i++)
    {
        if(ui->spinBox->value() == listeCanaux[i].toInt()) canalPris = true;
    }

    if(canalPris)
    {
        ui->spinBox->setStyleSheet("color:Orange;");
        QTimer::singleShot(100, this, SLOT(afficherAvertissement()));
    }
    else
    {
        ui->spinBox->setStyleSheet("color:black;");
    }
}

void WidgetCanalSuppl::afficherAvertissement()
{
    QToolTip::showText(QCursor::pos(), "Canal déjà utilisé!");
}
