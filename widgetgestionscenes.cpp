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

    connect(menuScenario, SIGNAL(triggered()), this, SLOT(nouveauScenario()));
    connect(menuScene, SIGNAL(triggered()), this, SLOT(nouvelleScene()));

    connect(ui->boutonSupprimer, SIGNAL(clicked()), this, SLOT(supprimerElement()));


    ui->boutonAjouter->setMenu(monMenu);


    this->afficherListeScenariosEtScenes();


    ui->boutonEnregistrer->setDisabled(true);
    this->menuScene->setDisabled(true);

    connect(ui->treeWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(activerAffichageAppareils()));



    QString addrApp, uuidApp;

    GestionXML::lireAdaptateur(&addrApp, &uuidApp);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(addrApp);

    interfaceDMX->seConnecter();
    interfaceDMX->resetDMX();

    this->donneesModifier = false;


}

WidgetGestionScenes::~WidgetGestionScenes()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    interfaceDMX->seDeconnecter();
    interfaceDMX->kill();

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
    ui->treeWidget->clear();

    QStringList nomScenario, uuidScenario;



    GestionXML::recupererListeScenarios(&nomScenario, &uuidScenario);

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
            itemsTreeParent[i]->setText(1, uuidScenario[i]);
            itemsTreeParent[i]->setText(2, uuidScenario[i]);
            itemsTreeParent[i]->setTextColor(0, QColor(Qt::red));


            GestionXML::recupererListeScenes(&listeScenes, &listeScenesUUID, uuidScenario[i]);

            if(listeScenes.size() == 0)
            {
                itemsTreeChild.push_back(new QTreeWidgetItem());
                itemsTreeChild[decalage]->setText(0, "Aucune scènes");
                itemsTreeChild[decalage]->setText(1, "NULL");
                itemsTreeChild[decalage]->setText(2, uuidScenario[i]);


                itemsTreeParent[i]->addChild(itemsTreeChild[decalage]);

                decalage++;
            }
            else
            {
                for(int j=0; j<listeScenes.size(); j++)
                {
                    itemsTreeChild.push_back(new QTreeWidgetItem());
                    itemsTreeChild[decalage]->setText(0, listeScenes[j]);
                    itemsTreeChild[decalage]->setText(1, listeScenesUUID[j]);
                    itemsTreeChild[decalage]->setText(2, uuidScenario[i]);

                    itemsTreeParent[i]->addChild(itemsTreeChild[decalage]);

                    decalage++;
                }


                this->menuScene->setEnabled(true);


            }


            ui->treeWidget->addTopLevelItem(itemsTreeParent[i]);
            ui->treeWidget->expandAll();
        }

        this->etatInterface(true);

        ui->treeWidget->setCurrentItem(itemsTreeParent[0]);

    }
}

void WidgetGestionScenes::interfaceAppareils()
{
    QStringList nom, uuid, type;


    GestionXML::lireListeAppareils(&nom, &uuid, &type);

    int decalagePar = 0;
    int decalageLyre = 0;
    int decalageScanner = 0;
    int decalageAutres = 0;

    for (int i = 0; i<nom.size(); i++)
    {
        this->listeTab.push_back(new QTabWidget(ui->tabWidget));

        if(type[i].contains("PAR"))
        {
            QVBoxLayout *monLayout = new QVBoxLayout();
            QTreeWidgetItem *recup = ui->treeWidget->currentItem();
            this->maListeDeParLED.push_back(new SceneParLED(recup->text(1), uuid[i]));

            monLayout->addWidget(this->maListeDeParLED[decalagePar]);

            this->listeTab[i]->setLayout(monLayout);

            connect(this->maListeDeParLED[decalagePar], SIGNAL(signalDMX(int,int)), this, SLOT(actionDMX(int,int)));

            this->maListeDeParLED[decalagePar]->actionDMX();
            this->donneesModifier = false;

            decalagePar++;

        }


        if(type[i].contains("LYRE"))
        {

            QVBoxLayout *monLayout = new QVBoxLayout();
            QTreeWidgetItem *recup = ui->treeWidget->currentItem();
            this->maListeDeLyre.push_back(new SceneLyre(recup->text(1), uuid[i]));

            monLayout->addWidget(this->maListeDeLyre[decalageLyre]);

            this->listeTab[i]->setLayout(monLayout);

            connect(this->maListeDeLyre[decalageLyre], SIGNAL(signalDMX(int,int)), this, SLOT(actionDMX(int,int)));

            this->maListeDeLyre[decalageLyre]->actionDMX();
            this->donneesModifier = false;

            decalageLyre++;
        }

        if(type[i].contains("SCANNER"))
        {

            QVBoxLayout *monLayout = new QVBoxLayout();
            QTreeWidgetItem *recup = ui->treeWidget->currentItem();
            this->maListeDeScanner.push_back(new SceneScanner(recup->text(1), uuid[i]));

            monLayout->addWidget(this->maListeDeScanner[decalageScanner]);

            this->listeTab[i]->setLayout(monLayout);

            connect(this->maListeDeScanner[decalageScanner], SIGNAL(signalDMX(int,int)), this, SLOT(actionDMX(int,int)));

            this->maListeDeScanner[decalageScanner]->actionDMX();
            this->donneesModifier = false;

            decalageScanner++;
        }

        if(type[i].contains("AUTRE"))
        {

            QVBoxLayout *monLayout = new QVBoxLayout();
            QTreeWidgetItem *recup = ui->treeWidget->currentItem();
            this->maListeAutres.push_back(new SceneAutres(recup->text(1), uuid[i]));

            monLayout->addWidget(this->maListeAutres[decalageAutres]);

            this->listeTab[i]->setLayout(monLayout);

            connect(this->maListeAutres[decalageAutres], SIGNAL(signalDMX(int,int)), this, SLOT(actionDMX(int,int)));

            this->maListeAutres[decalageAutres]->actionDMX();
            this->donneesModifier = false;

            decalageAutres++;
        }

        ui->tabWidget->addTab(this->listeTab[i], nom[i]);
    }
}

void WidgetGestionScenes::activerAffichageAppareils()
{

    if(this->donneesModifier)
    {
        int choix = QMessageBox::warning(this, "Attention", "Voulez-vous passer à une autre scène sans enregistrer la scène actuelle? Les modifications seront perdues.", QMessageBox::Yes | QMessageBox::No);

        if(choix == QMessageBox::Yes)
        {

            this->donneesModifier = false;

            bool estUnScenario = false;

            QTreeWidgetItem *recup = ui->treeWidget->currentItem();

            QStringList nomScenario, uuidScenario;


            GestionXML::recupererListeScenarios(&nomScenario, &uuidScenario);

            for(int i = 0; i<uuidScenario.size(); i++)
            {
                if(recup->text(1).contains(uuidScenario[i])) estUnScenario = true;
            }

            if(recup->text(1).contains("NULL")) estUnScenario = true;


            if(this->listeTab.size() != 0)
            {
                this->listeTab.clear();
                this->maListeDeParLED.clear();
                this->maListeDeLyre.clear();
                this->maListeDeScanner.clear();
                this->maListeAutres.clear();

                ui->tabWidget->clear();
            }

            if(!estUnScenario)
            {
                this->interfaceAppareils();
                connect(ui->boutonEnregistrer, SIGNAL(clicked()), this, SLOT(recupererToutesLesValeurs()));
                ui->boutonEnregistrer->setEnabled(true);



                this->menuScene->setDisabled(true);
            }
            else
            {
                disconnect(ui->boutonEnregistrer, 0, 0, 0);
                ui->boutonEnregistrer->setDisabled(true);

                this->menuScene->setEnabled(true);
            }

        }
        else
        {
            ui->treeWidget->setCurrentItem(this->precedentItem);
        }

    }
    else
    {
        bool estUnScenario = false;

        QTreeWidgetItem *recup = ui->treeWidget->currentItem();

        QStringList nomScenario, uuidScenario;


        GestionXML::recupererListeScenarios(&nomScenario, &uuidScenario);

        for(int i = 0; i<uuidScenario.size(); i++)
        {
            if(recup->text(1).contains(uuidScenario[i])) estUnScenario = true;
        }

        if(recup->text(1).contains("NULL")) estUnScenario = true;


        if(this->listeTab.size() != 0)
        {
            this->listeTab.clear();
            this->maListeDeParLED.clear();
            this->maListeDeLyre.clear();
            this->maListeDeScanner.clear();
            this->maListeAutres.clear();

            ui->tabWidget->clear();
        }

        if(!estUnScenario)
        {
            this->interfaceAppareils();
            connect(ui->boutonEnregistrer, SIGNAL(clicked()), this, SLOT(recupererToutesLesValeurs()));
            ui->boutonEnregistrer->setEnabled(true);



            this->menuScene->setDisabled(true);
        }
        else
        {
            disconnect(ui->boutonEnregistrer, 0, 0, 0);
            ui->boutonEnregistrer->setDisabled(true);

            this->menuScene->setEnabled(true);
        }

    }

    this->precedentItem = ui->treeWidget->currentItem();



}

void WidgetGestionScenes::actionDMX(int canal, int valeur)
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    interfaceDMX->modifierValeurCanal(canal, valeur);
    interfaceDMX->envoyerDMX();

    this->donneesModifier = true;
}

void WidgetGestionScenes::recupererToutesLesValeurs()
{
    this->donneesModifier = false;

    QStringList canal, valeur;

    if(this->maListeDeParLED.size() > 0)
    {
        for(int i = 0; i<this->maListeDeParLED.size(); i++)
        {
            this->maListeDeParLED[i]->recupererValeurs(&canal, &valeur);
        }
    }

    if(this->maListeDeLyre.size() > 0)
    {
        for(int i = 0; i<this->maListeDeLyre.size(); i++)
        {
            this->maListeDeLyre[i]->recupererValeurs(&canal, &valeur);
        }
    }

    if(this->maListeDeScanner.size() > 0)
    {
        for(int i = 0; i<this->maListeDeScanner.size(); i++)
        {
            this->maListeDeScanner[i]->recupererValeurs(&canal, &valeur);
        }
    }

    if(this->maListeAutres.size() > 0)
    {
        for(int i = 0; i<this->maListeAutres.size(); i++)
        {
            this->maListeAutres[i]->recupererValeurs(&canal, &valeur);
        }
    }



    QTreeWidgetItem *recup = ui->treeWidget->currentItem();
    GestionXML::enregistrerValeursScenes(canal, valeur, recup->text(1));
}

void WidgetGestionScenes::nouveauScenario()
{
    QUuid monUUID = QUuid::createUuid();

    bool ok;
    QString nomScenario = QInputDialog::getText(this, "Nom du scénario", "Indiquer le nom du nouveau scénario: ", QLineEdit::Normal, QString(), &ok);

    if(ok)
    {

        GestionXML::ajouterScenarios(nomScenario, monUUID.toString());

        this->afficherListeScenariosEtScenes();
    }
}

void WidgetGestionScenes::nouvelleScene()
{
    QUuid monUUID = QUuid::createUuid();

    bool ok;
    QString nomScenario = QInputDialog::getText(this, "Nom de la scène", "Indiquer le nom de la nouvelle scène: ", QLineEdit::Normal, QString(), &ok);

    if(ok)
    {
        QTreeWidgetItem *recup = ui->treeWidget->currentItem();


        GestionXML::ajouterScenes(nomScenario, monUUID.toString(), recup->text(2));

        this->afficherListeScenariosEtScenes();

    }
}

void WidgetGestionScenes::supprimerElement()
{
    bool estUnScenario = false;

    QTreeWidgetItem *recup = ui->treeWidget->currentItem();

    QStringList nomScenario, uuidScenario;


    GestionXML::recupererListeScenarios(&nomScenario, &uuidScenario);

    for(int i = 0; i<uuidScenario.size(); i++)
    {
        if(recup->text(1).contains(uuidScenario[i])) estUnScenario = true;
    }

    if(recup->text(1).contains("NULL")) estUnScenario = true;


    if(estUnScenario)
    {
        int choix = QMessageBox::warning(this, "Attention", "Vous allez supprimer un scénario ainsi que les scènes associées. Confirmez-vous cette action?", QMessageBox::Yes | QMessageBox::No);

        if(choix == QMessageBox::Yes)
        {
            QStringList listeScenes, listeUUID;
            GestionXML::recupererListeScenes(&listeScenes, &listeUUID, recup->text(1));

            for(int j = 0; j<listeScenes.size(); j++)
            {
                GestionXML::supprimerSceneDeSequenceExterne(listeUUID[j]);
            }

            GestionXML::supprimerScenario(recup->text(1));
            this->afficherListeScenariosEtScenes();
        }
    }
    else
    {
        int choix = QMessageBox::warning(this, "Attention", "Vous allez supprimer une scène. Confirmez-vous cette action?", QMessageBox::Yes | QMessageBox::No);

        if(choix == QMessageBox::Yes)
        {
            GestionXML::supprimerScene(recup->text(1));
            GestionXML::supprimerSceneDeSequenceExterne(recup->text(1));
            this->afficherListeScenariosEtScenes();
            this->activerAffichageAppareils();
        }

    }
}
