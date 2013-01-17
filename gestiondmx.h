#ifndef GESTIONDMX_H
#define GESTIONDMX_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>
#include "enttecdmxusb.h"

class GestionDMX : public QObject
{
    Q_OBJECT

private:
    EnttecDMXUSB *interfaceDMX;


    QString adresseDMX;




public:
    explicit GestionDMX(QObject *parent = 0);
    ~GestionDMX();

    bool seConnecter();

    
signals:


private slots:


    
};

#endif // GESTIONDMX_H
