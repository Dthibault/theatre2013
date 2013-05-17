#include "gestionconsole.h"

GestionConsole::GestionConsole(QObject *parent) :
    QObject(parent)
{
    this->socket = new QUdpSocket(this);

    if(this->socket->bind(QHostAddress::Any, 3330, QUdpSocket::ShareAddress))
    {
        connect(this->socket, SIGNAL(readyRead()), this, SLOT(receptionTrame()));
    }


}

GestionConsole::~GestionConsole()
{
    this->socket->close();
    disconnect(this->socket,0,0,0);

    delete this->socket;
}



void GestionConsole::receptionTrame()
{

    while(this->socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(this->socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 portSender;

        this->socket->readDatagram(datagram.data(), datagram.size(), &sender, &portSender);

        this->traitementTrame(datagram);

    }
}

void GestionConsole::ecrireSocket(QByteArray data)
{
    this->socket->writeDatagram(data, QHostAddress::Broadcast, 3330);
}

void GestionConsole::traitementTrame(QByteArray data)
{
    QByteArray entete;


    for(int i=0;i<TAILLE_ENTETE;i++)
    {
        entete.append(data[i]);
    }

    if(entete.contains("WIDD"))
    {

        int numero = data[37];


        emit modifierNumero(numero);


    }

}



