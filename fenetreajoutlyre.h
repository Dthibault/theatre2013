#ifndef FENETREAJOUTLYRE_H
#define FENETREAJOUTLYRE_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QInputDialog>
#include <vector>
#include "gestionxml.h"
#include "gestionconsole.h"
#include "widgetcanalsuppl.h"

namespace Ui {
    class FenetreAjoutLyre;
}

class FenetreAjoutLyre : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreAjoutLyre(QWidget *parent = 0);
    ~FenetreAjoutLyre();



private:
    Ui::FenetreAjoutLyre *ui;

    GestionDMX *interfaceDMX;

    void configurerAdaptateur();

    std::vector<WidgetCanalSuppl*> listeWidgetSuppl;

private slots:
    void fermer();

    void miseAJourDMX();

    void confirmationAppareil();
};

#endif // FENETREAJOUTLYRE_H
