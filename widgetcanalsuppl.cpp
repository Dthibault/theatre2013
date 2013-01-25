#include "widgetcanalsuppl.h"
#include "ui_widgetcanalsuppl.h"

WidgetCanalSuppl::WidgetCanalSuppl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetCanalSuppl)
{
    ui->setupUi(this);
}

WidgetCanalSuppl::~WidgetCanalSuppl()
{
    delete ui;
}
