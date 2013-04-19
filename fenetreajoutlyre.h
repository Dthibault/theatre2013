#ifndef FENETREAJOUTLYRE_H
#define FENETREAJOUTLYRE_H

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

#endif // FENETREAJOUTLYRE_H
