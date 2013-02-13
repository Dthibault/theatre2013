#ifndef WIDGETGESTIONSEQUENCES_H
#define WIDGETGESTIONSEQUENCES_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <QUuid>
#include <vector>
#include "gestionxml.h"
#include "gestiondmx.h"

namespace Ui {
    class WidgetGestionSequences;
}

class WidgetGestionSequences : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetGestionSequences(QWidget *parent = 0);
    ~WidgetGestionSequences();

private:
    Ui::WidgetGestionSequences *ui;


    GestionDMX *interfaceDMX;

    bool donneesModifier;

    QTreeWidgetItem *precedentItem;

private slots:
    void changementOnglets(int onglet);
};

#endif // WIDGETGESTIONSEQUENCES_H
