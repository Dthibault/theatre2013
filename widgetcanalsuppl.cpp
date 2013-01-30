#include "widgetcanalsuppl.h"
#include "ui_widgetcanalsuppl.h"

WidgetCanalSuppl::WidgetCanalSuppl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCanalSuppl)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(envoyerChangement(int)));
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
