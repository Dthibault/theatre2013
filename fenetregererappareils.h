#ifndef FENETREGERERAPPAREILS_H
#define FENETREGERERAPPAREILS_H

#include <QDialog>
#include <QString>
#include <QUuid>
#include <QDebug>
#include <QFile>
#include <QCryptographicHash>
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

private slots:

};

#endif // FENETREGERERAPPAREILS_H
