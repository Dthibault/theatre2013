#include "widgetgestionsequences.h"
#include "ui_widgetgestionsequences.h"

WidgetGestionSequences::WidgetGestionSequences(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGestionSequences)
{
    ui->setupUi(this);

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changementOnglets(int)));
}

WidgetGestionSequences::~WidgetGestionSequences()
{
    delete ui;
}


void WidgetGestionSequences::changementOnglets(int onglet)
{
    if(onglet == 1)
    {
        ui->tabWidget->setCurrentIndex(0);
    }
}
