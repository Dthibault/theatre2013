#ifndef FENETREAJOUTLYRE_H
#define FENETREAJOUTLYRE_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include "gestionxml.h"
#include "gestionconsole.h"

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
};

#endif // FENETREAJOUTLYRE_H
