#ifndef WIDGETGESTIONSCENES_H
#define WIDGETGESTIONSCENES_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <vector>
#include "gestiondmx.h"
#include "gestionxml.h"


namespace Ui {
class WidgetGestionScenes;
}

class WidgetGestionScenes : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetGestionScenes(QWidget *parent = 0);
    ~WidgetGestionScenes();
    
private:
    Ui::WidgetGestionScenes *ui;

    QMenu *monMenu;
    QAction *menuScenario;
    QAction *menuScene;

    GestionDMX *interfaceDMX;

    std::vector<QTabWidget*> listeTab;
};

#endif // WIDGETGESTIONSCENES_H
