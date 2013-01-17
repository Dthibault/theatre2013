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
    this->interfaceDMX = new EnttecDMXUSB(DMX_USB_PRO, this->adresseDMX.toLocal8Bit().constData());

    if(this->interfaceDMX->IsAvailable())
    {
        return true;
    }
    else
    {
        emit adaptateurNonPresent();

        delete this->interfaceDMX;
        return false;
    }
}


