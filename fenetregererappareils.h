#ifndef FENETREGERERAPPAREILS_H
#define FENETREGERERAPPAREILS_H

#include <QDialog>
#include <QString>
#include <QUuid>
#include <QDebug>
#include <QFile>
#include <QCryptographicHash>
#include "gestionconsole.h"
#include "gestiondmx.h"
#include "gestionxml.h"

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

    GestionConsole *testConsole;

private slots:

};

#endif // FENETREGERERAPPAREILS_H
