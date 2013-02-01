#include "gestionconsole.h"

GestionConsole::GestionConsole(QObject *parent) :
    QObject(parent)
{
    this->socket = new QUdpSocket(this);

    if(this->socket->bind(QHostAddress::Any, 3330, QUdpSocket::ShareAddress))
    {
        connect(this->socket, SIGNAL(readyRead()), this, SLOT(receptionTrame()));
        qDebug() << "Socket connecté";
    }
    else
    {
        qDebug() << "Erreur de socket";
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

        qDebug() << data[37] << data[38];
        emit modifierNumero(numero);



//        QByteArray firmware;
//        int lettreD = data[15];

//        firmware.setNum(data[15], 16);

//        qDebug() << "\nDecimal: " << lettreD << " / Hexa: " << firmware << "/ Resultat:" << QByteArray::fromHex(firmware);

//        if(data[6] == 0x7f)
//        {
//            qDebug() << "\nUP";
//        }
    }

}



