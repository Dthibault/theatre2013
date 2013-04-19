#ifndef WIDGETGESTIONSEQUENCES_H
#define WIDGETGESTIONSEQUENCES_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <QUuid>
#include <QTimer>
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

    int tempsTotal;
    int tempsDecompteTotal;
    int tempsTemporaire;

    bool etatPause;
    bool etatDemarrageSequence;

    bool switchMessage;

    int sceneActuel;

    QTimer *timerPrincipal;



    bool donneesModifier;

    QTreeWidgetItem *precedentItem;

    void afficherListeSequences();
    void afficherListeScenes();

    QStringList listeUUID;
    QStringList listeUUIDsequence;
    QStringList listeTempo;

    void etatInterface(bool etat);



    void actualiserTempsTotal(int temps);

private slots:


    void ajouterSequence();
    void supprimerSequence();

    void changementIndex();

    void ajouterScene();
    void supprimerScene();

    void demarrerTimer();
    void stopTimer();

    void declenchementSequence();

};

#endif // WIDGETGESTIONSEQUENCES_H
