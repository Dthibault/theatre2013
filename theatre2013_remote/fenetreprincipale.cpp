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
    connect(ui->PageDown, SIGNAL(clicked()), this, SLOT(envoyerTrame()));
    connect(ui->PageUp, SIGNAL(clicked()), this, SLOT(envoyerTrame()));


    this->maConsole = new GestionConsole;

    connect(this->maConsole, SIGNAL(modifierNumero(int)), this, SLOT(modifierNumero(int)));

    connect(ui->verticalSlider_1, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_4, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_5, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_6, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_7, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_8, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_9, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));
    connect(ui->verticalSlider_10, SIGNAL(valueChanged(int)), this, SLOT(envoyerTrame()));

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

    if(emetteurCasted)
    {
        if(emetteurCasted->objectName().contains("boutonGO"))
        {
            trame[decalage++] = BOUTON_GO;
        }
        else if(emetteurCasted->objectName().contains("boutonBACK"))
        {
            trame[decalage++] = BOUTON_BACK;
        }
        else if(emetteurCasted->objectName().contains("PageUp"))
        {
            trame[decalage++] = BOUTON_PAGEUP;
        }
        else if(emetteurCasted->objectName().contains("PageDown"))
        {
            trame[decalage++] = BOUTON_PAGEDOWN;
        }
    }



    decalage = 15;

    trame[decalage++] = ui->verticalSlider_1->value();
    trame[decalage++] = ui->verticalSlider_2->value();
    trame[decalage++] = ui->verticalSlider_3->value();
    trame[decalage++] = ui->verticalSlider_4->value();
    trame[decalage++] = ui->verticalSlider_5->value();
    trame[decalage++] = ui->verticalSlider_6->value();
    trame[decalage++] = ui->verticalSlider_7->value();
    trame[decalage++] = ui->verticalSlider_8->value();
    trame[decalage++] = ui->verticalSlider_9->value();
    trame[decalage++] = ui->verticalSlider_10->value();


    this->maConsole->ecrireSocket(trame);


}


void FenetrePrincipale::modifierNumero(int numero)
{

    ui->lcdNumber->display(numero);
}
