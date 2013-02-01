#ifndef GESTIONCONSOLE_H
#define GESTIONCONSOLE_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QUdpSocket>


#define PORT_ENTTEC 3330

#define TAILLE_ENTETE 4
#define BIT_STATES 6
#define BIT_SLIDERS 15
#define TAILLE_ENVOIE 41


#define BOUTON_GO 0xFFFFFFEF
#define BOUTON_BACK 0xFFFFFFDF
#define BOUTON_PAGEUP 0x7F
#define BOUTON_PAGEDOWN 0xFFFFFFBF


class GestionConsole : public QObject
{
    Q_OBJECT
public:
    explicit GestionConsole(QObject *parent = 0);
    ~GestionConsole();

    void ecrireSocket(QByteArray data);

private:
    QUdpSocket *socket;

    void traitementTrame(QByteArray data);

private slots:
    void receptionTrame();

signals:
    void modifierNumero(int);

};

#endif // GESTIONCONSOLE_H
