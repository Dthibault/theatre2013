#ifndef GESTIONDMX_H
#define GESTIONDMX_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>
#include <string>
#include "enttecdmxusb.h"



class GestionDMX : public QObject
{
    Q_OBJECT

private:
    EnttecDMXUSB *interfaceDMX;

    bool premiereConnexion;

    QString adresseDMX;

public:
    explicit GestionDMX(QObject *parent = 0);
    ~GestionDMX();

    bool seConnecter();
    void setAdresse(QString nom);
    void seDeconnecter();

    QString getNomInterface();
    QString getSerialNumber();
    QString getPort();

    void resetDMX();

    
signals:

    void adaptateurNonPresent();

private slots:


    
};

#endif // GESTIONDMX_H
