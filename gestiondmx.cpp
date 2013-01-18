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

void GestionDMX::setAdresse(QString nom)
{
    this->adresseDMX = nom;
}


QString GestionDMX::getNomInterface()
{
    string recup = this->interfaceDMX->GetNomInterface();
    return recup.c_str();
}

QString GestionDMX::getSerialNumber()
{
    string recup = this->interfaceDMX->GetSerialNumber();
    return recup.c_str();
}

QString GestionDMX::getPort()
{
    string recup = this->interfaceDMX->GetPortInterface();
    return recup.c_str();
}

