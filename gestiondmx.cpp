#include "gestiondmx.h"


GestionDMX::GestionDMX(QObject *parent) :
    QObject(parent)
{
    this->adresseDMX = "/dev/ttyUSB0";
}

GestionDMX::~GestionDMX()
{
    delete this->interfaceDMX;
}


bool GestionDMX::seConnecter()
{
    qDebug() << "\nLancé";
    this->interfaceDMX = new EnttecDMXUSB(DMX_USB_PRO, "/dev/ttyUSB0");
    qDebug() << "Présent: " << this->interfaceDMX->IsAvailable() << "\n";
}


