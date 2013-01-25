#include "gestiondmx.h"


GestionDMX::GestionDMX(QObject *parent) :
    QObject(parent)
{
    this->premiereConnexion = false;
}

GestionDMX::~GestionDMX()
{
    delete this->interfaceDMX;
}


bool GestionDMX::seConnecter()
{
    this->interfaceDMX = new EnttecDMXUSB(DMX_USB_PRO, this->adresseDMX.toLocal8Bit().constData());
    this->premiereConnexion = true;

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

void GestionDMX::seDeconnecter()
{
    if(this->premiereConnexion == true)
    {

        delete this->interfaceDMX;
        this->interfaceDMX = new EnttecDMXUSB(DMX_USB_PRO, this->adresseDMX.toLocal8Bit().constData());
    }

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

void GestionDMX::resetDMX()
{
    this->interfaceDMX->ResetCanauxDMX();
    this->interfaceDMX->SendDMX();
}


void GestionDMX::modifierValeurCanal(int canal, int valeur)
{
    this->interfaceDMX->SetCanalDMX(canal, (int)valeur);
}

void GestionDMX::envoyerDMX()
{
    this->interfaceDMX->SendDMX();
}
