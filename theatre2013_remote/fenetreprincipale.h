#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include "gestionconsole.h"


namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

    GestionConsole *maConsole;

private:
    Ui::FenetrePrincipale *ui;

private slots:
    void envoyerTrame();

    void modifierNumero(int);
};

#endif // FENETREPRINCIPALE_H
