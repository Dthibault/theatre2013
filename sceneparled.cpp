#include "sceneparled.h"
#include "ui_sceneparled.h"

SceneParLED::SceneParLED(QString sceneParente, QString uuidPar, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneParLED)
{
    ui->setupUi(this);

    this->uuidDuPar = uuidPar;

    this->monColorWheel = new ColorWheel(this);

    ui->horizontalLayout_12->addWidget(this->monColorWheel);


    QStringList listeCanaux, typeCanaux;
    GestionXML::recupererCanaux(&listeCanaux, &typeCanaux, uuidPar);


    ui->spinBoxRED->setDisabled(true);
    ui->spinBoxGREEN->setDisabled(true);
    ui->spinBoxBLUE->setDisabled(true);

    ui->spinBoxRED->setValue(listeCanaux[0].toInt());
    ui->spinBoxGREEN->setValue(listeCanaux[1].toInt());
    ui->spinBoxBLUE->setValue(listeCanaux[2].toInt());

    if(listeCanaux.size() > 3)
    {
        for(int i = 3; i<listeCanaux.size(); i++)
        {
            QHBoxLayout *layout = new QHBoxLayout();
            this->labelSuppl.push_back(new QLabel(typeCanaux[i]));
            this->sliderSuppl.push_back(new QSlider(Qt::Horizontal));
            this->sliderSuppl[i-3]->setMinimum(0);
            this->sliderSuppl[i-3]->setMaximum(255);

            this->spinBoxSuppl.push_back(new QSpinBox());
            this->spinBoxSuppl[i-3]->setDisabled(true);
            this->spinBoxSuppl[i-3]->setMaximum(512);
            this->spinBoxSuppl[i-3]->setValue(listeCanaux[i].toInt());

            layout->addWidget(this->labelSuppl[i-3]);
            layout->addWidget(this->sliderSuppl[i-3]);
            layout->addWidget(this->spinBoxSuppl[i-3]);



            ui->verticalLayout_6->addLayout(layout);

            connect(this->sliderSuppl[i-3], SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
        }
    }





    connect(ui->verticalSliderRED, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
    connect(ui->verticalSliderGREEN, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
    connect(ui->verticalSliderBLUE, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));

    connect(this->monColorWheel, SIGNAL(colorChange(QColor)), this, SLOT(actionColorWheel(QColor)));


    QStringList listeCanauxEnregistrer, valeurCanauxEnregistrer;
    GestionXML::recupererValeursScenes(&listeCanauxEnregistrer, &valeurCanauxEnregistrer, sceneParente);


    if(listeCanauxEnregistrer.size() != 0)
    {

        for(int i =0; i<listeCanauxEnregistrer.size(); i++)
        {
            if(ui->spinBoxRED->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderRED->setValue(valeurCanauxEnregistrer[i].toInt());
            if(ui->spinBoxGREEN->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderGREEN->setValue(valeurCanauxEnregistrer[i].toInt());
            if(ui->spinBoxBLUE->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderBLUE->setValue(valeurCanauxEnregistrer[i].toInt());


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

SceneParLED::~SceneParLED()
{
    delete ui;
}

void SceneParLED::actionDMX()
{

    QStringList listeCanaux, typeCanaux;
    GestionXML::recupererCanaux(&listeCanaux, &typeCanaux, this->uuidDuPar);

    emit signalDMX(listeCanaux[0].toInt(), ui->verticalSliderRED->value());
    emit signalDMX(listeCanaux[1].toInt(), ui->verticalSliderGREEN->value());
    emit signalDMX(listeCanaux[2].toInt(), ui->verticalSliderBLUE->value());

    if(listeCanaux.size() > 3)
    {
        for(int i = 3; i<listeCanaux.size(); i++)
        {
            emit signalDMX(listeCanaux[i].toInt(), this->sliderSuppl[i-3]->value());
        }
    }

    disconnect(this->monColorWheel, 0, 0, 0);
    QColor couleur(ui->verticalSliderRED->value(), ui->verticalSliderGREEN->value(), ui->verticalSliderBLUE->value());
    this->monColorWheel->setColor(couleur);
    connect(this->monColorWheel, SIGNAL(colorChange(QColor)), this, SLOT(actionColorWheel(QColor)));
}

void SceneParLED::actionColorWheel(QColor mesCouleurs)
{
    ui->verticalSliderRED->setValue(mesCouleurs.red());
    ui->verticalSliderGREEN->setValue(mesCouleurs.green());
    ui->verticalSliderBLUE->setValue(mesCouleurs.blue());
}


void SceneParLED::recupererValeurs(QStringList *canal, QStringList *valeur)
{

    QStringList listeCanaux, typeCanaux;
    GestionXML::recupererCanaux(&listeCanaux, &typeCanaux, this->uuidDuPar);


    canal->push_back(QString::number(ui->spinBoxRED->value()));
    canal->push_back(QString::number(ui->spinBoxGREEN->value()));
    canal->push_back(QString::number(ui->spinBoxBLUE->value()));

    valeur->push_back(QString::number(ui->verticalSliderRED->value()));
    valeur->push_back(QString::number(ui->verticalSliderGREEN->value()));
    valeur->push_back(QString::number(ui->verticalSliderBLUE->value()));


    if(listeCanaux.size() > 3)
    {
        for(int i = 3; i<listeCanaux.size(); i++)
        {
            canal->push_back(QString::number(this->spinBoxSuppl[i-3]->value()));
            valeur->push_back(QString::number(this->sliderSuppl[i-3]->value()));
        }
    }
}
