#include "scenelyre.h"
#include "ui_scenelyre.h"

SceneLyre::SceneLyre(QString sceneParente, QString uuidLyre, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneLyre)
{
    ui->setupUi(this);


    this->uuidDuLyre = uuidLyre;



    QStringList listeCanaux, typeCanaux;
    GestionXML::recupererCanaux(&listeCanaux, &typeCanaux, uuidLyre);

    ui->spinBoxPAN->setDisabled(true);
    ui->spinBoxTILT->setDisabled(true);
    ui->spinBoxGLOBOS->setDisabled(true);
    ui->spinBoxCOULEUR->setDisabled(true);

    ui->spinBoxPAN->setValue(listeCanaux[0].toInt());
    ui->spinBoxTILT->setValue(listeCanaux[1].toInt());
    ui->spinBoxGLOBOS->setValue(listeCanaux[2].toInt());
    ui->spinBoxCOULEUR->setValue(listeCanaux[3].toInt());

    if(listeCanaux.size() > 4)
    {
        for(int i = 4; i<listeCanaux.size(); i++)
        {
            QHBoxLayout *layout = new QHBoxLayout();
            this->labelSuppl.push_back(new QLabel(typeCanaux[i]));
            this->sliderSuppl.push_back(new QSlider(Qt::Horizontal));
            this->sliderSuppl[i-4]->setMinimum(0);
            this->sliderSuppl[i-4]->setMaximum(255);

            this->spinBoxSuppl.push_back(new QSpinBox());
            this->spinBoxSuppl[i-4]->setDisabled(true);
            this->spinBoxSuppl[i-4]->setMaximum(512);
            this->spinBoxSuppl[i-4]->setValue(listeCanaux[i].toInt());

            layout->addWidget(this->labelSuppl[i-4]);
            layout->addWidget(this->sliderSuppl[i-4]);
            layout->addWidget(this->spinBoxSuppl[i-4]);

            ui->verticalLayout_6->addLayout(layout);

            connect(this->sliderSuppl[i-4], SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
        }
    }


    connect(ui->verticalSliderPAN, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
    connect(ui->verticalSliderTILT, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
    connect(ui->verticalSliderGLOBOS, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
    connect(ui->verticalSliderCOULEUR, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));

    QStringList listeCanauxEnregistrer, valeurCanauxEnregistrer;
    GestionXML::recupererValeursScenes(&listeCanauxEnregistrer, &valeurCanauxEnregistrer, sceneParente);


    if(listeCanauxEnregistrer.size() != 0)
    {

        for(int i =0; i<listeCanauxEnregistrer.size(); i++)
        {
            if(ui->spinBoxPAN->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderPAN->setValue(valeurCanauxEnregistrer[i].toInt());
            if(ui->spinBoxTILT->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderTILT->setValue(valeurCanauxEnregistrer[i].toInt());
            if(ui->spinBoxGLOBOS->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderGLOBOS->setValue(valeurCanauxEnregistrer[i].toInt());
            if(ui->spinBoxCOULEUR->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderCOULEUR->setValue(valeurCanauxEnregistrer[i].toInt());

            if(this->sliderSuppl.size() > 0)
            {
                for(int j = 0; j<this->sliderSuppl.size(); j++)
                {

                    if(this->spinBoxSuppl[j]->value() == listeCanauxEnregistrer[i].toInt())
                    {
                        this->sliderSuppl[j]->setValue(valeurCanauxEnregistrer[i].toInt());;
                    }
                }
            }


        }
    }

this->actionDMX();


}

SceneLyre::~SceneLyre()
{
    delete ui;
}


void SceneLyre::actionDMX()
{

    QStringList listeCanaux, typeCanaux;
    GestionXML::recupererCanaux(&listeCanaux, &typeCanaux, this->uuidDuLyre);

    emit signalDMX(listeCanaux[0].toInt(), ui->verticalSliderPAN->value());
    emit signalDMX(listeCanaux[1].toInt(), ui->verticalSliderTILT->value());
    emit signalDMX(listeCanaux[2].toInt(), ui->verticalSliderGLOBOS->value());
    emit signalDMX(listeCanaux[3].toInt(), ui->verticalSliderCOULEUR->value());

    if(listeCanaux.size() > 4)
    {
        for(int i = 4; i<listeCanaux.size(); i++)
        {
            emit signalDMX(listeCanaux[i].toInt(), this->sliderSuppl[i-4]->value());
        }
    }


}


void SceneLyre::recupererValeurs(QStringList *canal, QStringList *valeur)
{

    QStringList listeCanaux, typeCanaux;
    GestionXML::recupererCanaux(&listeCanaux, &typeCanaux, this->uuidDuLyre);


    canal->push_back(QString::number(ui->spinBoxPAN->value()));
    canal->push_back(QString::number(ui->spinBoxTILT->value()));
    canal->push_back(QString::number(ui->spinBoxGLOBOS->value()));
    canal->push_back(QString::number(ui->spinBoxCOULEUR->value()));

    valeur->push_back(QString::number(ui->verticalSliderPAN->value()));
    valeur->push_back(QString::number(ui->verticalSliderTILT->value()));
    valeur->push_back(QString::number(ui->verticalSliderGLOBOS->value()));
    valeur->push_back(QString::number(ui->verticalSliderCOULEUR->value()));


    if(listeCanaux.size() > 4)
    {
        for(int i = 4; i<listeCanaux.size(); i++)
        {
            canal->push_back(QString::number(this->spinBoxSuppl[i-4]->value()));
            valeur->push_back(QString::number(this->sliderSuppl[i-4]->value()));
        }
    }
}
