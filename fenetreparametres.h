#ifndef FENETREPARAMETRES_H
#define FENETREPARAMETRES_H

#include <QDialog>
#include <QString>
#include <QUuid>
#include <QDebug>
#include <QFile>
#include "gestiondmx.h"
#include "gestionxml.h"

namespace Ui {
class FenetreParametres;
}

class FenetreParametres : public QDialog
{
    Q_OBJECT
    
public:
    explicit FenetreParametres(QWidget *parent = 0);
    ~FenetreParametres();
    
private:
    Ui::FenetreParametres *ui;

    GestionDMX *interfaceDMX;


private slots:
    void switchBouton(QString choix);

    void recupererInformations();

    void verifierPeripheriquesSysteme();

    void enregistrerDonnees();
};

#endif // FENETREPARAMETRES_H
