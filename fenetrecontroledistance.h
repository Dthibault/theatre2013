#ifndef FENETRECONTROLEDISTANCE_H
#define FENETRECONTROLEDISTANCE_H

#include <QDialog>
#include <QString>
#include "gestionxml.h"
#include "gestionconsole.h"
#include "gestiondmx.h"

namespace Ui {
    class FenetreControleDistance;
}

class FenetreControleDistance : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreControleDistance(QWidget *parent = 0);
    ~FenetreControleDistance();

private:
    Ui::FenetreControleDistance *ui;

    GestionConsole *interfaceConsole;


    bool configurerAdaptateur();

    bool etatPriseEnMain;

    int numeroActuel;

    void listerAppareils();

    QStringList listeNumero;

private slots:
    void fermerFenetre();

    void afficherNumeroAssignation(int numero);
    void modifierNumeroAssignation(int numero);

    void debutControle();
    void arretControle();

    void augmenterNumero();
    void baisserNumero();

    void modifierSliders(int*);
};

#endif // FENETRECONTROLEDISTANCE_H
