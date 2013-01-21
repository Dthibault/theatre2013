#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include "fenetreparametres.h"
#include "fenetregererappareils.h"
#include "gestiondmx.h"
#include "gestionxml.h"

namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();
    
private:
    Ui::FenetrePrincipale *ui;

private slots:
    void ouvrirParametres();
    void ouvrirGererAppareils();

};

#endif // FENETREPRINCIPALE_H
