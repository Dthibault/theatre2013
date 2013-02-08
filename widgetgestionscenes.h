#ifndef WIDGETGESTIONSCENES_H
#define WIDGETGESTIONSCENES_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <QUuid>
#include <vector>
#include "gestionxml.h"
#include "gestiondmx.h"
#include "sceneparled.h"



namespace Ui {
class WidgetGestionScenes;
}

class WidgetGestionScenes : public QWidget
{
    Q_OBJECT
    
public:
    explicit WidgetGestionScenes(QWidget *parent = 0);
    ~WidgetGestionScenes();

    void afficherListeScenariosEtScenes();

    void interfaceAppareils();

    void etatInterface(bool etat);

    
private:
    Ui::WidgetGestionScenes *ui;

    QMenu *monMenu;
    QAction *menuScenario;
    QAction *menuScene;


    std::vector<QTabWidget*> listeTab;
    std::vector<SceneParLED*> maListeDeParLED;

    GestionDMX *interfaceDMX;

    bool donneesModifier;

    QTreeWidgetItem *precedentItem;


private slots:
    void activerAffichageAppareils();

    void actionDMX(int canal, int valeur);

    void recupererToutesLesValeurs();

    void nouveauScenario();
    void nouvelleScene();


};

#endif // WIDGETGESTIONSCENES_H
