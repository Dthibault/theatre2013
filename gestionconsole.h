#ifndef GESTIONCONSOLE_H
#define GESTIONCONSOLE_H

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include "gestiondmx.h"

#define PORT_ENTTEC 3330

#define TAILLE_ENTETE 4
#define BIT_STATES 6
#define BIT_SLIDERS 15


#define BOUTON_GO 0xFFFFFFEF
#define BOUTON_BACK 0xFFFFFFDF
#define BOUTON_PAGEUP 0x7F
#define BOUTON_PAGEDOWN 0xFFFFFFBF


class GestionConsole : public QObject
{
    Q_OBJECT
public:
    explicit GestionConsole(QObject *parent = 0);
    ~GestionConsole();

    bool start();
    void stop();

    void modifierNumero(int numero);

private:
    QUdpSocket *socket;

    void traitementTrame(QByteArray data);

    int etatSliders[9];


signals:
    void boutonGO();
    void boutonBACK();

    void boutonUP();
    void boutonDOWN();

    void envoieSliders(int*);

private slots:
    void receptionTrame();

};

#endif // GESTIONCONSOLE_H
