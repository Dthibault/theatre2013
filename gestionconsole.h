#ifndef GESTIONCONSOLE_H
#define GESTIONCONSOLE_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QUdpSocket>
#include "gestiondmx.h"

#define PORT_ENTTEC 3330

#define TAILLE_ENTETE 4
#define TAILLE_FIRMWARE 1

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

private slots:
    void receptionTrame();

};

#endif // GESTIONCONSOLE_H
