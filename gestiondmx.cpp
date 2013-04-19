#include "gestiondmx.h"

template <typename T>
T *Singleton<T>::_singleton = NULL;


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

bool GestionDMX::estDisponible()
{
    this->interfaceDMX = new EnttecDMXUSB(DMX_USB_PRO, this->adresseDMX.toLocal8Bit().constData());
    return this->interfaceDMX->IsAvailable();
}

void GestionDMX::faireDimmerCanal(int canal, int valeur)
{
    this->monThreadDimmer = new GestionDimmer(this, canal, valeur);

    connect(this->monThreadDimmer, SIGNAL(nouvelleValeur(int,int)), this, SLOT(envoyerDimmerCanal(int,int)));

    this->monThreadDimmer->start();
}

void GestionDMX::envoyerDimmerCanal(int canal, int valeur)
{
    this->interfaceDMX->SetCanalDMX(canal, (int)valeur);
    this->envoyerDMX();
}

template <>
GestionDMX* Singleton<GestionDMX>::_singleton = NULL;


GestionDimmer::GestionDimmer(QObject *parent, int canal, int valeur)
{
    this->valeurActuelle = valeur;
    this->canalActuel = canal;
}


void GestionDimmer::run()
{
    while(this->valeurActuelle > 0)
    {
        this->valeurActuelle = this->valeurActuelle - 4;

        if(this->valeurActuelle < 0) this->valeurActuelle = 0;

        emit nouvelleValeur(this->canalActuel, this->valeurActuelle);

        msleep(100);
    }
}
