#include "gestionconsole.h"

GestionConsole::GestionConsole(QObject *parent) :
    QObject(parent)
{
    this->socket = new QUdpSocket(this);
}

GestionConsole::~GestionConsole()
{
    delete this->socket;
}


bool GestionConsole::start()
{
    if(this->socket->bind(QHostAddress::Any, 3330))
    {
        connect(this->socket, SIGNAL(readyRead()), this, SLOT(receptionTrame()));

        qDebug() << "Socket connecté";
//        this->interfaceDMX = new EnttecDMXUSB(DMX_USB_PRO, "/dev/ttyUSB0");
//        this->interfaceDMX->ResetCanauxDMX();
//        this->interfaceDMX->SendDMX();

        return true;
    }
    else
    {
        qDebug() << "Erreur de socket";

        return false;
    }

}

void GestionConsole::stop()
{
    this->socket->close();
    disconnect(this->socket,0,0,0);
    qDebug() << "Socket déconnecté";
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

void GestionConsole::traitementTrame(QByteArray data)
{
    QByteArray entete;


    for(int i=0;i<TAILLE_ENTETE;i++)
    {
        entete.append(data[i]);
    }

    if(entete.contains("WODD"))
    {

        switch(data[BIT_STATES])
        {
            case BOUTON_GO: emit boutonGO(); break;
            case BOUTON_BACK: emit boutonBACK(); break;
        }



//QByteArray firmware;
//        int lettreD = data[6];

//        firmware.setNum(data[6], 16);

//        qDebug() << "\nDecimal: " << lettreD << " / Hexa: " << firmware << "/ Resultat:" << QByteArray::fromHex(firmware);

//        if(data[6] == 0x7f)
//        {
//            qDebug() << "\nUP";
//        }

//        this->interfaceDMX->SetCanalDMX(14, int(data[15]));
//        this->interfaceDMX->SetCanalDMX(13, int(data[16]));
//        this->interfaceDMX->SetCanalDMX(11, int(data[17]));
//        this->interfaceDMX->SetCanalDMX(12, int(data[18]));
//        this->interfaceDMX->SendDMX();
    }

}
