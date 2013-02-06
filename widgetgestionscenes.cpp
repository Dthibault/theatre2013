#include "widgetgestionscenes.h"
#include "ui_widgetgestionscenes.h"

WidgetGestionScenes::WidgetGestionScenes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGestionScenes)
{
    ui->setupUi(this);

    ui->treeWidget->setDisabled(true);
    ui->boutonEnregistrer->setDisabled(true);
    ui->boutonSupprimer->setDisabled(true);
    ui->tabWidget->setDisabled(true);

    monMenu = new QMenu(this);
    menuScenario = new QAction(this);
    menuScene = new QAction(this);

    menuScenario->setText("Nouveau scénario");
    menuScene->setText("Nouvelle scène");

    monMenu->addAction(menuScenario);
    monMenu->addAction(menuScene);

    menuScene->setDisabled(true);

    ui->boutonAjouter->setMenu(monMenu);




}

WidgetGestionScenes::~WidgetGestionScenes()
{
    delete ui;
}
