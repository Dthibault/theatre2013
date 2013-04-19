#ifndef GESTIONDMX_H
#define GESTIONDMX_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>
#include <string>
#include "enttecdmxusb.h"

class GestionDimmer : public QThread
{
    Q_OBJECT

public:
    explicit GestionDimmer(QObject *parent = 0, int canal = 0, int valeur = 255);

private:
    int valeurActuelle;
    int canalActuel;

protected:
    void run();

signals:
    void nouvelleValeur(int, int);
};


template <typename T>
class Singleton
{
protected:
    Singleton(){};
    ~Singleton(){};

public:

    static T *getInstance()
    {
        if(NULL == _singleton) _singleton = new T;

        return (static_cast<T*> (_singleton));
    }

    static void kill()
    {
        if (NULL != _singleton)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }

private:
    static T *_singleton;

};


class GestionDMX : public QObject, public Singleton<GestionDMX>
{
    friend class Singleton<GestionDMX>;

    Q_OBJECT

private:
    EnttecDMXUSB *interfaceDMX;

    bool premiereConnexion;

    QString adresseDMX;

    GestionDimmer *monThreadDimmer;



public:
    explicit GestionDMX(QObject *parent = 0);
    ~GestionDMX();

    bool seConnecter();
    void setAdresse(QString nom);
    void seDeconnecter();
    bool estDisponible();

    QString getNomInterface();
    QString getSerialNumber();
    QString getPort();

    void resetDMX();

    void modifierValeurCanal(int canal, int valeur);

    void envoyerDMX();

    void faireDimmerCanal(int canal, int valeur = 255);

    
signals:

    void adaptateurNonPresent();

public slots:

private slots:
    void envoyerDimmerCanal(int canal, int valeur);

    
};

#endif // GESTIONDMX_H
