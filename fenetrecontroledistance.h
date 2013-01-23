#ifndef FENETRECONTROLEDISTANCE_H
#define FENETRECONTROLEDISTANCE_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include "gestionconsole.h"

namespace Ui {
    class FenetreControleDistance;
}

class FenetreControleDistance : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreControleDistance(QWidget *parent = 0);
    ~FenetreControleDistance();

private:
    Ui::FenetreControleDistance *ui;

    GestionConsole *interfaceConsole;

private slots:
    void fermerFenetre();
};

#endif // FENETRECONTROLEDISTANCE_H
