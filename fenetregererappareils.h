#ifndef FENETREGERERAPPAREILS_H
#define FENETREGERERAPPAREILS_H

#include <QDialog>
#include <QString>
#include <QUuid>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include "gestiondmx.h"
#include "gestionxml.h"
#include "fenetreajoutlyre.h"
#include "fenetreajoutpar.h"
#include "fenetrescannerled.h"
#include "fenetreajoutautre.h"

namespace Ui {
class FenetreGererAppareils;
}

class FenetreGererAppareils : public QDialog
{
    Q_OBJECT
    
public:
    explicit FenetreGererAppareils(QWidget *parent = 0);
    ~FenetreGererAppareils();
    
private:
    Ui::FenetreGererAppareils *ui;

    void listerAppareils();

private slots:
    void ouvrirFenetreNouveau();

    void effacerAppareil();
    void modifierAppareil();

};

#endif // FENETREGERERAPPAREILS_H
