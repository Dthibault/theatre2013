#ifndef GESTIONCONSOLE_H
#define GESTIONCONSOLE_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QUdpSocket>
#include "gestiondmx.h"

#define PORT_ENTTEC 3330

#define TAILLE_ENTETE 4
#define BIT_STATES 6


#define BOUTON_GO 0xFFFFFFEF
#define BOUTON_BACK 0xFFFFFFDF


class GestionConsole : public QObject
{
    Q_OBJECT
public:
    explicit GestionConsole(QObject *parent = 0);
    ~GestionConsole();

    bool start();
    void stop();

private:
    QUdpSocket *socket;

    GestionDMX *interfaceDMX;

    void traitementTrame(QByteArray data);
    int testlol;


signals:
    void boutonGO();
    void boutonBACK();

private slots:
    void receptionTrame();

};

#endif // GESTIONCONSOLE_H
