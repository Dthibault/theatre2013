#include "widgetgestionscenes.h"
#include "ui_widgetgestionscenes.h"

WidgetGestionScenes::WidgetGestionScenes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGestionScenes)
{
    ui->setupUi(this);

    this->etatInterface(false);

    monMenu = new QMenu(this);
    menuScenario = new QAction(this);
    menuScene = new QAction(this);

    menuScenario->setText("Nouveau scénario");
    menuScene->setText("Nouvelle scène");

    monMenu->addAction(menuScenario);
    monMenu->addAction(menuScene);



    ui->boutonAjouter->setMenu(monMenu);


    this->afficherListeScenariosEtScenes();

    connect(ui->treeWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(activerAffichageAppareils()));


    GestionXML lireApp;
    QString addrApp, uuidApp;

    lireApp.lireAdaptateur(&addrApp, &uuidApp);

    this->interfaceDMX = new GestionDMX;
    this->interfaceDMX->setAdresse(addrApp);

    this->interfaceDMX->seConnecter();
    this->interfaceDMX->resetDMX();



}

WidgetGestionScenes::~WidgetGestionScenes()
{
    this->interfaceDMX->seDeconnecter();

    delete ui;
}

void WidgetGestionScenes::etatInterface(bool etat)
{
    if(etat)
    {
        ui->treeWidget->setEnabled(true);
        ui->boutonEnregistrer->setEnabled(true);
        ui->boutonSupprimer->setEnabled(true);
        ui->tabWidget->setEnabled(true);
    }
    else
    {
        ui->treeWidget->setDisabled(true);
        ui->boutonEnregistrer->setDisabled(true);
        ui->boutonSupprimer->setDisabled(true);
        ui->tabWidget->setDisabled(true);
    }
}

void WidgetGestionScenes::afficherListeScenariosEtScenes()
{
    QStringList nomScenario, uuidScenario;

    GestionXML monXML;

    monXML.recupererListeScenarios(&nomScenario, &uuidScenario);

    if(nomScenario.size() == 0)
    {
        menuScene->setDisabled(true);
        this->etatInterface(false);
    }
    else
    {

        std::vector<QTreeWidgetItem *> itemsTreeParent;
        std::vector<QTreeWidgetItem *> itemsTreeChild;
        int decalage = 0;

        QStringList listeScenes, listeScenesUUID;

        for(int i = 0; i<nomScenario.size(); i++)
        {

            listeScenes.clear();
            listeScenesUUID.clear();

            itemsTreeParent.push_back(new QTreeWidgetItem());
            itemsTreeParent[i]->setText(0, nomScenario[i]);

            monXML.recupererListeScenes(&listeScenes, &listeScenesUUID, uuidScenario[i]);

            if(listeScenes.size() == 0)
            {
                itemsTreeChild.push_back(new QTreeWidgetItem());
                itemsTreeChild[decalage]->setText(0, "Aucune scènes");

                itemsTreeParent[i]->addChild(itemsTreeChild[decalage]);

                decalage++;
            }
            else
            {
                for(int j=0; j<listeScenes.size(); j++)
                {
                    itemsTreeChild.push_back(new QTreeWidgetItem());
                    itemsTreeChild[decalage]->setText(0, listeScenes[j]);

                    itemsTreeParent[i]->addChild(itemsTreeChild[decalage]);

                    decalage++;
                }


            }


            ui->treeWidget->addTopLevelItem(itemsTreeParent[i]);
            ui->treeWidget->expandAll();
        }

        this->etatInterface(true);

    }
}

void WidgetGestionScenes::interfaceAppareils()
{
    QStringList nom, uuid, type;

    GestionXML monXML;
    monXML.lireListeAppareils(&nom, &uuid, &type);

    int decalage = 0;

    for (int i = 0; i<nom.size(); i++)
    {
        this->listeTab.push_back(new QTabWidget(ui->tabWidget));

        if(type[i].contains("PAR"))
        {
            QVBoxLayout *monLayout = new QVBoxLayout();
            this->maListeDeParLED.push_back(new SceneParLED(uuid[i]));

            monLayout->addWidget(this->maListeDeParLED[decalage]);

            this->listeTab[i]->setLayout(monLayout);

            connect(this->maListeDeParLED[decalage], SIGNAL(signalDMX(int,int)), this, SLOT(actionDMX(int,int)));

            decalage++;

        }




        ui->tabWidget->addTab(this->listeTab[i], nom[i]);
    }
}

void WidgetGestionScenes::activerAffichageAppareils()
{
    if(this->listeTab.size() != 0)
    {
        this->listeTab.clear();
        this->maListeDeParLED.clear();

        ui->tabWidget->clear();
    }
    this->interfaceAppareils();
}

void WidgetGestionScenes::actionDMX(int canal, int valeur)
{
    this->interfaceDMX->modifierValeurCanal(canal, valeur);
    this->interfaceDMX->envoyerDMX();
}
