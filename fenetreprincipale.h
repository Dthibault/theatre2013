#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include "fenetreparametres.h"
#include "gestiondmx.h"

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

};

#endif // FENETREPRINCIPALE_H
