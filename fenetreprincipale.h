#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include "fenetreparametres.h"
#include "fenetregererappareils.h"
#include "fenetrecontroledistance.h"
#include "gestiondmx.h"
#include "gestionxml.h"
#include "widgetgestionscenes.h"
#include "widgetgestionsequences.h"

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

    WidgetGestionScenes *gestionScenes;
    WidgetGestionSequences *gestionSequences;

    QPushButton *boutonModeScenes;
    QPushButton *boutonModeSequences;
    QPushButton *boutonFermerMode;

    int typeMode;

private slots:
    void ouvrirParametres();
    void ouvrirGererAppareils();
    void ouvrirControleDistance();

    void afficherModeScenes();
    void afficherModeSequences();
    void fermerMode();

};

#endif // FENETREPRINCIPALE_H
