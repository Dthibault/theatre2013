#include "widgetgestionsequences.h"
#include "ui_widgetgestionsequences.h"

WidgetGestionSequences::WidgetGestionSequences(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGestionSequences)
{
    ui->setupUi(this);

    this->timerPrincipal = new QTimer(this);
    connect(this->timerPrincipal, SIGNAL(timeout()), this, SLOT(declenchementSequence()));
    connect(ui->boutonPlayPause, SIGNAL(clicked()), this, SLOT(demarrerTimer()));
    connect(ui->boutonStop, SIGNAL(clicked()), this, SLOT(stopTimer()));

    this->etatDemarrageSequence = false;
    this->etatPause = false;

    ui->labelEtatSequence->setText("<h3> </h3>");

    connect(ui->boutonAjouter, SIGNAL(clicked()), this, SLOT(ajouterSequence()));
    connect(ui->boutonSupprimer, SIGNAL(clicked()), this, SLOT(supprimerSequence()));

    connect(ui->treeWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(changementIndex()));



    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Nom de la scène"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Temporisation"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Supprimer"));

    ui->tableWidget->setColumnWidth(0, 300);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    this->afficherListeSequences();

    connect(ui->boutonAjouterScene, SIGNAL(clicked()), this, SLOT(ajouterScene()));

    ui->labelSceneActuel->setText("Aucune");

    ui->conteneurDroite->setDisabled(true);

}

WidgetGestionSequences::~WidgetGestionSequences()
{
    QString addrApp, uuidApp;


    GestionXML::lireAdaptateur(&addrApp, &uuidApp);

    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();
    interfaceDMX->setAdresse(addrApp);

    interfaceDMX->seConnecter();
    interfaceDMX->resetDMX();

    interfaceDMX->seDeconnecter();

    interfaceDMX->kill();

    delete ui;
}





void WidgetGestionSequences::etatInterface(bool etat)
{
    if(etat)
    {

        ui->boutonSupprimer->setEnabled(true);
    }
    else
    {

        ui->boutonSupprimer->setDisabled(true);
    }
}

void WidgetGestionSequences::ajouterSequence()
{
    QUuid monUUID = QUuid::createUuid();

    bool ok;
    QString nomSequence = QInputDialog::getText(this, "Nom de la séquence", "Indiquer le nom de la nouvelle séquence: ", QLineEdit::Normal, QString(), &ok);

    if(ok)
    {

        GestionXML::ajouterSequence(nomSequence, monUUID.toString());

        this->afficherListeSequences();

    }
}

void WidgetGestionSequences::supprimerSequence()
{

    QTreeWidgetItem *recup = ui->treeWidget->currentItem();

    int choix = QMessageBox::warning(this, "Attention", "Vous allez supprimer une séquence. Confirmez-vous cette action?", QMessageBox::Yes | QMessageBox::No);

    if(choix == QMessageBox::Yes)
    {
        GestionXML::supprimerSequence(recup->text(1));
        this->afficherListeSequences();

    }
}

void WidgetGestionSequences::afficherListeSequences()
{

    QStringList listeSequences, listeUUID;
    GestionXML::recupererSequences(&listeSequences, &listeUUID);

    std::vector<QTreeWidgetItem *> itemsTreeParent;

    ui->treeWidget->clear();

    if(listeSequences.size() == 0)
    {
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);

        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Nom de la scène"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Temporisation"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Supprimer"));

        ui->tableWidget->setColumnWidth(0, 300);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);



    }


    for(int i = 0; i<listeSequences.size(); i++)
    {
        itemsTreeParent.push_back(new QTreeWidgetItem());
        itemsTreeParent[i]->setText(0, listeSequences[i]);
        itemsTreeParent[i]->setText(1, listeUUID[i]);

        ui->treeWidget->addTopLevelItem(itemsTreeParent[i]);
        ui->treeWidget->expandAll();
    }


}

void WidgetGestionSequences::afficherListeScenes()
{
    this->listeUUID.clear();

    ui->comboBox->clear();


    QStringList listeScenes, listeUUIDscene, listeUUID;
    GestionXML::afficherListeScenes(&listeScenes, &listeUUIDscene, &listeUUID);



    this->listeUUID = listeUUID;

    ui->comboBox->addItems(listeScenes);



}

void WidgetGestionSequences::changementIndex()
{

    ui->conteneurDroite->setDisabled(false);

    this->afficherListeScenes();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    QTreeWidgetItem *recup = ui->treeWidget->currentItem();


    QStringList listeUUID, listeTempo, listeUUIDscene;
    GestionXML::recupererContenueSequence(recup->text(1), &listeTempo, &listeUUIDscene, &listeUUID);

    int temps = 0;

    this->listeUUIDsequence = listeUUID;


    for(int i = 0; i<listeUUID.size(); i++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(GestionXML::recupererNomScene(listeUUIDscene[i]));
        QTableWidgetItem *newItem2 = new QTableWidgetItem(listeTempo[i]);
        QPushButton *boutonSupprimer = new QPushButton("Supprimer", ui->tableWidget);

//        boutonSupprimer->setMaximumWidth(50);
//        boutonSupprimer->setMinimumWidth(50);
        boutonSupprimer->setIcon(QIcon(":/new/images/images/boutonSupprimer.png"));
        boutonSupprimer->setObjectName(QString::number(i));

        connect(boutonSupprimer, SIGNAL(clicked()), this, SLOT(supprimerScene()));

        newItem->setTextAlignment(Qt::AlignHCenter);
        newItem2->setTextAlignment(Qt::AlignHCenter);

        ui->tableWidget->setRowCount(i+1);

        ui->tableWidget->setItem(i, 0, newItem);
        ui->tableWidget->setItem(i, 1, newItem2);
        ui->tableWidget->setCellWidget(i, 2, boutonSupprimer);

        temps = temps+listeTempo[i].toInt();
    }


        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Nom de la scène"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Temporisation"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Supprimer"));

        ui->tableWidget->setColumnWidth(0, 300);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

        this->actualiserTempsTotal(temps);
}

void WidgetGestionSequences::supprimerScene()
{
    QObject * emetteur = sender();
    QPushButton * emetteurCasted = qobject_cast<QPushButton*>(emetteur);

    if(emetteurCasted)
    {



        QTreeWidgetItem *recup = ui->treeWidget->currentItem();

        GestionXML::supprimerSceneDeSequence(recup->text(1), this->listeUUIDsequence[emetteurCasted->objectName().toInt()]);



        this->changementIndex();
    }
}

void WidgetGestionSequences::ajouterScene()
{
    if(ui->spinBox->value() <= 0)
    {
        QMessageBox::information(this, "Erreur temporisation", "Veuillez mettre une temporisation supérieure à 0 seconde.");
    }
    else
    {

        QUuid monUUID = QUuid::createUuid();

        QTreeWidgetItem *recup = ui->treeWidget->currentItem();



        GestionXML::ajouterSceneDeSequence(recup->text(1), this->listeUUID[ui->comboBox->currentIndex()], monUUID.toString(), QString::number(ui->spinBox->value()));

        this->changementIndex();
    }
}

void WidgetGestionSequences::actualiserTempsTotal(int temps)
{
    this->tempsTotal = temps;
    ui->progressBar->setMaximum(temps);

}

void WidgetGestionSequences::demarrerTimer()
{
    if(this->etatDemarrageSequence)
    {


        if(this->etatPause)
        {
            this->timerPrincipal->start(1000);
            this->etatPause = false;

            ui->boutonPlayPause->setText("Pause");
        }
        else
        {
            this->timerPrincipal->stop();
            this->etatPause = true;

            ui->boutonPlayPause->setText("Play");
        }
    }
    else
    {
        this->tempsDecompteTotal = 0;
        this->tempsTemporaire = 0;
        this->timerPrincipal->start(1000);
        this->etatDemarrageSequence = true;
        ui->treeWidget->setDisabled(true);

        ui->boutonPlayPause->setText("Pause");

        this->sceneActuel = 0;

        QString addrApp, uuidApp;


        GestionXML::lireAdaptateur(&addrApp, &uuidApp);

        GestionDMX *interfaceDMX;
        interfaceDMX = GestionDMX::getInstance();
        interfaceDMX->setAdresse(addrApp);

        interfaceDMX->seConnecter();
        interfaceDMX->resetDMX();

        this->switchMessage = false;

    }

    ui->conteneurScenes->setDisabled(true);


    for(int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        QWidget *monBouton = ui->tableWidget->cellWidget(i,2);
        monBouton->setDisabled(true);
    }

    ui->tableWidget->setCurrentCell(0,0);
}


void WidgetGestionSequences::stopTimer()
{
    GestionDMX *interfaceDMX;
    interfaceDMX = GestionDMX::getInstance();

    this->timerPrincipal->stop();

    ui->treeWidget->setEnabled(true);
    this->tempsTemporaire = 0;
    this->tempsDecompteTotal = 0;

    if(this->etatDemarrageSequence)
    {

        interfaceDMX->resetDMX();
        interfaceDMX->kill();
    }

    ui->conteneurScenes->setDisabled(false);
    ui->tableWidget->setDisabled(false);

    this->etatPause = false;
    this->etatDemarrageSequence = false;

    ui->boutonPlayPause->setText("Play");

    ui->labelEtatSequence->setText("<h3>Séquence terminée!</h3>");
    ui->labelEtatSequence->setStyleSheet("color: green;");

    for(int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        QWidget *monBouton = ui->tableWidget->cellWidget(i,2);
        monBouton->setDisabled(false);
    }

}


void WidgetGestionSequences::declenchementSequence()
{

    if(this->switchMessage)
    {
        ui->labelEtatSequence->setText("<h3> </h3>");
        this->switchMessage = false;
    }
    else
    {
        ui->labelEtatSequence->setText("<h3>Lecture en cours!</h3>");
        ui->labelEtatSequence->setStyleSheet("color: red;");
        this->switchMessage = true;
    }


    if(this->tempsDecompteTotal >= this->tempsTotal)
    {
        ui->progressBar->setValue(this->tempsTotal);
        this->stopTimer();
    }
    else
    {
        QTreeWidgetItem *recup = ui->treeWidget->currentItem();


        QStringList listeUUIDScenes, listeUUID, temporisation;
        GestionXML::recupererContenueSequence(recup->text(1), &temporisation, &listeUUIDScenes, &listeUUID);

        if(this->tempsTemporaire >= temporisation[this->sceneActuel].toInt())
        {
            this->tempsTemporaire = 0;
            this->sceneActuel++;
        }

        ui->labelSceneActuel->setText(GestionXML::recupererNomScene(listeUUIDScenes[this->sceneActuel]));

        QStringList listeCanaux, listeValeurs;
        GestionXML::recupererValeursScenes(&listeCanaux, &listeValeurs, listeUUIDScenes[this->sceneActuel]);

        GestionDMX *interfaceDMX;
        interfaceDMX = GestionDMX::getInstance();

        for(int i = 0; i<listeValeurs.size(); i++)
        {
            interfaceDMX->modifierValeurCanal(listeCanaux[i].toInt(), listeValeurs[i].toInt());
        }

        interfaceDMX->envoyerDMX();

        ui->progressBar->setValue(this->tempsDecompteTotal);
        this->tempsDecompteTotal++;
        this->tempsTemporaire++;
    }

    ui->tableWidget->setCurrentCell(this->sceneActuel,0);
}
