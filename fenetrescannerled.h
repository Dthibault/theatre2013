#ifndef FENETRESCANNERLED_H
#define FENETRESCANNERLED_H

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
    class FenetreScannerLED;
}

class FenetreScannerLED : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreScannerLED(QWidget *parent = 0);
    ~FenetreScannerLED();

private:
    Ui::FenetreScannerLED *ui;


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

#endif // FENETRESCANNERLED_H
