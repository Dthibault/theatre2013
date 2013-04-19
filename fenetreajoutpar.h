#ifndef FENETREAJOUTPAR_H
#define FENETREAJOUTPAR_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QInputDialog>
#include <QUuid>
#include <vector>
#include <QVBoxLayout>
#include "gestionxml.h"
#include "gestionconsole.h"
#include "widgetcanalsuppl.h"

namespace Ui {
    class FenetreAjoutPar;
}

class FenetreAjoutPar : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreAjoutPar(QWidget *parent = 0);
    ~FenetreAjoutPar();

private:
    Ui::FenetreAjoutPar *ui;



    void configurerAdaptateur();

    std::vector<WidgetCanalSuppl*> listeWidgetSuppl;
    int nbAjouts;

    QVBoxLayout *layoutSuppl;


private slots:
    void fermer();

    void miseAJourDMX();

    void confirmationAppareil();

    void modifierNombreWidgetSuppl();
};

#endif // FENETREAJOUTPAR_H
