#ifndef FENETREAJOUTAUTRE_H
#define FENETREAJOUTAUTRE_H

#include <QDialog>
#include <QString>
#include <QInputDialog>
#include <QUuid>
#include <vector>
#include <QVBoxLayout>
#include "gestionxml.h"
#include "gestionconsole.h"
#include "widgetcanalsuppl.h"

namespace Ui {
    class FenetreAjoutAutre;
}

class FenetreAjoutAutre : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreAjoutAutre(QWidget *parent = 0);
    ~FenetreAjoutAutre();

private:
    Ui::FenetreAjoutAutre *ui;


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

#endif // FENETREAJOUTAUTRE_H
