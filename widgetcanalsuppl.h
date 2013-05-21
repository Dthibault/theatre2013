#ifndef WIDGETCANALSUPPL_H
#define WIDGETCANALSUPPL_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QToolTip>
#include "gestionxml.h"


namespace Ui {
    class WidgetCanalSuppl;
}

class WidgetCanalSuppl : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCanalSuppl(QWidget *parent = 0);
    ~WidgetCanalSuppl();

    void setValeur(int valeur);
    int getNumeroCanal();
    int getValeurCanal();


    QString getNomCanal();

private:
    Ui::WidgetCanalSuppl *ui;

signals:
    void changementSlider();

private slots:

    void envoyerChangement(int);

    void verifierCanal();
    void afficherAvertissement();

};

#endif // WIDGETCANALSUPPL_H
