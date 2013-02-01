#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(ui->boutonGO, SIGNAL(clicked()), this, SLOT(envoyerTrame()));
    connect(ui->boutonBACK, SIGNAL(clicked()), this, SLOT(envoyerTrame()));


    this->maConsole = new GestionConsole;

    connect(this->maConsole, SIGNAL(modifierNumero(int)), this, SLOT(modifierNumero(int)));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete this->maConsole;

    delete ui;
}



void FenetrePrincipale::envoyerTrame()
{

    QByteArray trame;

    for(int i=0; i<TAILLE_ENVOIE; i++)
    {
        trame[i] = 0x00;
    }

    int decalage = 0;

    trame[decalage++] = 'W';
    trame[decalage++] = 'O';
    trame[decalage++] = 'D';
    trame[decalage++] = 'D';
    trame[decalage++] = 0x00;
    trame[decalage++] = 0x01;




    QObject * emetteur = sender();
    QPushButton * emetteurCasted = qobject_cast<QPushButton*>(emetteur);

    if(emetteurCasted->objectName().contains("boutonGO"))
    {
        trame[decalage++] = BOUTON_GO;
    }
    else if(emetteurCasted->objectName().contains("boutonBACK"))
    {
        trame[decalage++] = BOUTON_BACK;
    }






    this->maConsole->ecrireSocket(trame);


    //qDebug() << "Taille: " << trame.size() << "\nTrame: " << trame;
}


void FenetrePrincipale::modifierNumero(int numero)
{
    qDebug() << numero;
    ui->lcdNumber->display(numero);
}
