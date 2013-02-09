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
#include "scenelyre.h"
#include "scenescanner.h"
#include "sceneautres.h"



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
    std::vector<SceneLyre*> maListeDeLyre;
    std::vector<SceneScanner*> maListeDeScanner;
    std::vector<SceneAutres*> maListeAutres;

    GestionDMX *interfaceDMX;

    bool donneesModifier;

    QTreeWidgetItem *precedentItem;


private slots:
    void activerAffichageAppareils();

    void actionDMX(int canal, int valeur);

    void recupererToutesLesValeurs();

    void nouveauScenario();
    void nouvelleScene();

    void supprimerElement();


};

#endif // WIDGETGESTIONSCENES_H
