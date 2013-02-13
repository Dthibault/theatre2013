#include "widgetgestionsequences.h"
#include "ui_widgetgestionsequences.h"

WidgetGestionSequences::WidgetGestionSequences(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGestionSequences)
{
    ui->setupUi(this);

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changementOnglets(int)));
    connect(ui->boutonAjouter, SIGNAL(clicked()), this, SLOT(ajouterSequence()));
    connect(ui->boutonSupprimer, SIGNAL(clicked()), this, SLOT(supprimerSequence()));

    connect(ui->treeWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(changementIndex()));

    ui->tabWidget->setDisabled(true);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Nom de la scène"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Temporisation"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Supprimer"));

    ui->tableWidget->setColumnWidth(0, 300);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    this->afficherListeSequences();

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

void WidgetGestionSequences::etatInterface(bool etat)
{
    if(etat)
    {
        ui->tabWidget->setEnabled(true);
        ui->boutonEnregistrer->setEnabled(true);
        ui->boutonSupprimer->setEnabled(true);
    }
    else
    {
        ui->tabWidget->setDisabled(true);
        ui->boutonEnregistrer->setDisabled(true);
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
        GestionXML monXML;
        monXML.ajouterSequence(nomSequence, monUUID.toString());

        this->afficherListeSequences();
    }
}

void WidgetGestionSequences::supprimerSequence()
{
    GestionXML monXML;
    QTreeWidgetItem *recup = ui->treeWidget->currentItem();

    int choix = QMessageBox::warning(this, "Attention", "Vous allez supprimer une séquence. Confirmez-vous cette action?", QMessageBox::Yes | QMessageBox::No);

    if(choix == QMessageBox::Yes)
    {
        monXML.supprimerSequence(recup->text(1));
        this->afficherListeSequences();
    }
}

void WidgetGestionSequences::afficherListeSequences()
{
    GestionXML monXML;
    QStringList listeSequences, listeUUID;
    monXML.recupererSequences(&listeSequences, &listeUUID);

    std::vector<QTreeWidgetItem *> itemsTreeParent;

    ui->treeWidget->clear();

    if(listeSequences.size() == 0)
    {

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

    GestionXML monXML;
    QStringList listeScenes, listeUUIDscene, listeUUID;
    monXML.afficherListeScenes(&listeScenes, &listeUUIDscene, &listeUUID);



    this->listeUUID = listeUUID;

    ui->comboBox->addItems(listeScenes);



}

void WidgetGestionSequences::changementIndex()
{
    ui->tabWidget->setEnabled(true);

    this->afficherListeScenes();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    QTreeWidgetItem *recup = ui->treeWidget->currentItem();

    GestionXML monXML;
    QStringList listeUUID, listeTempo, listeUUIDscene;
    monXML.recupererContenueSequence(recup->text(1), &listeTempo, &listeUUIDscene, &listeUUID);



    this->listeUUIDsequence = listeUUID;


    for(int i = 0; i<listeUUID.size(); i++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(monXML.recupererNomScene(listeUUIDscene[i]));
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
    }


        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Nom de la scène"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Temporisation"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Supprimer"));

        ui->tableWidget->setColumnWidth(0, 300);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);


}

void WidgetGestionSequences::supprimerScene()
{
    QObject * emetteur = sender();
    QPushButton * emetteurCasted = qobject_cast<QPushButton*>(emetteur);

    if(emetteurCasted)
    {
//        qDebug() << emetteurCasted->objectName();
//        qDebug() << this->listeUUIDsequence[emetteurCasted->objectName().toInt()];
        GestionXML monXML;



        this->changementIndex();
    }
}
