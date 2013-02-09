#include "scenescanner.h"
#include "ui_scenescanner.h"

SceneScanner::SceneScanner(QString sceneParente, QString uuidScanner, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneScanner)
{
    ui->setupUi(this);

    this->uuidDuScanner = uuidScanner;

    GestionXML monXML;
    QStringList listeCanaux, typeCanaux;
    monXML.recupererCanaux(&listeCanaux, &typeCanaux, uuidScanner);


    ui->spinBoxPAN->setDisabled(true);
    ui->spinBoxTILT->setDisabled(true);
    ui->spinBoxCOULEUR->setDisabled(true);

    ui->spinBoxPAN->setValue(listeCanaux[0].toInt());
    ui->spinBoxTILT->setValue(listeCanaux[1].toInt());
    ui->spinBoxCOULEUR->setValue(listeCanaux[2].toInt());

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





    connect(ui->verticalSliderPAN, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
    connect(ui->verticalSliderTILT, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
    connect(ui->verticalSliderCOULEUR, SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));


    QStringList listeCanauxEnregistrer, valeurCanauxEnregistrer;
    monXML.recupererValeursScenes(&listeCanauxEnregistrer, &valeurCanauxEnregistrer, sceneParente);


    if(listeCanauxEnregistrer.size() != 0)
    {

        for(int i =0; i<listeCanauxEnregistrer.size(); i++)
        {
            if(ui->spinBoxPAN->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderPAN->setValue(valeurCanauxEnregistrer[i].toInt());
            if(ui->spinBoxTILT->value() == listeCanauxEnregistrer[i].toInt()) ui->verticalSliderTILT->setValue(valeurCanauxEnregistrer[i].toInt());
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

}

SceneScanner::~SceneScanner()
{
    delete ui;
}


void SceneScanner::actionDMX()
{
    GestionXML monXML;
    QStringList listeCanaux, typeCanaux;
    monXML.recupererCanaux(&listeCanaux, &typeCanaux, this->uuidDuScanner);

    emit signalDMX(listeCanaux[0].toInt(), ui->verticalSliderPAN->value());
    emit signalDMX(listeCanaux[1].toInt(), ui->verticalSliderTILT->value());
    emit signalDMX(listeCanaux[2].toInt(), ui->verticalSliderCOULEUR->value());

    if(listeCanaux.size() > 3)
    {
        for(int i = 3; i<listeCanaux.size(); i++)
        {
            emit signalDMX(listeCanaux[i].toInt(), this->sliderSuppl[i-3]->value());
        }
    }


}


void SceneScanner::recupererValeurs(QStringList *canal, QStringList *valeur)
{
    GestionXML monXML;
    QStringList listeCanaux, typeCanaux;
    monXML.recupererCanaux(&listeCanaux, &typeCanaux, this->uuidDuScanner);


    canal->push_back(QString::number(ui->spinBoxPAN->value()));
    canal->push_back(QString::number(ui->spinBoxTILT->value()));
    canal->push_back(QString::number(ui->spinBoxCOULEUR->value()));

    valeur->push_back(QString::number(ui->verticalSliderPAN->value()));
    valeur->push_back(QString::number(ui->verticalSliderTILT->value()));
    valeur->push_back(QString::number(ui->verticalSliderCOULEUR->value()));


    if(listeCanaux.size() > 3)
    {
        for(int i = 3; i<listeCanaux.size(); i++)
        {
            canal->push_back(QString::number(this->spinBoxSuppl[i-3]->value()));
            valeur->push_back(QString::number(this->sliderSuppl[i-3]->value()));
        }
    }
}
