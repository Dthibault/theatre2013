#include "sceneautres.h"
#include "ui_sceneautres.h"

SceneAutres::SceneAutres(QString sceneParente, QString uuidAutre, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneAutres)
{
    ui->setupUi(this);

    this->uuidAutre = uuidAutre;


    GestionXML monXML;
    QStringList listeCanaux, typeCanaux;
    monXML.recupererCanaux(&listeCanaux, &typeCanaux, uuidAutre);

    if(listeCanaux.size() > 0)
    {
        for(int i = 0; i<listeCanaux.size(); i++)
        {
            QHBoxLayout *layout = new QHBoxLayout();
            this->labelSuppl.push_back(new QLabel(typeCanaux[i]));
            this->sliderSuppl.push_back(new QSlider(Qt::Horizontal));
            this->sliderSuppl[i]->setMinimum(0);
            this->sliderSuppl[i]->setMaximum(255);

            this->spinBoxSuppl.push_back(new QSpinBox());
            this->spinBoxSuppl[i]->setDisabled(true);
            this->spinBoxSuppl[i]->setMaximum(512);
            this->spinBoxSuppl[i]->setValue(listeCanaux[i].toInt());

            layout->addWidget(this->labelSuppl[i]);
            layout->addWidget(this->sliderSuppl[i]);
            layout->addWidget(this->spinBoxSuppl[i]);

            ui->verticalLayout_10->addLayout(layout);

            connect(this->sliderSuppl[i], SIGNAL(valueChanged(int)), this, SLOT(actionDMX()));
        }
    }

    QStringList listeCanauxEnregistrer, valeurCanauxEnregistrer;
    monXML.recupererValeursScenes(&listeCanauxEnregistrer, &valeurCanauxEnregistrer, sceneParente);


    if(listeCanauxEnregistrer.size() != 0)
    {

        for(int i =0; i<listeCanauxEnregistrer.size(); i++)
        {

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

SceneAutres::~SceneAutres()
{
    delete ui;
}


void SceneAutres::actionDMX()
{
    GestionXML monXML;
    QStringList listeCanaux, typeCanaux;
    monXML.recupererCanaux(&listeCanaux, &typeCanaux, this->uuidAutre);

    if(listeCanaux.size() > 0)
    {
        for(int i = 0; i<listeCanaux.size(); i++)
        {
            emit signalDMX(listeCanaux[i].toInt(), this->sliderSuppl[i]->value());
        }
    }


}


void SceneAutres::recupererValeurs(QStringList *canal, QStringList *valeur)
{
    GestionXML monXML;
    QStringList listeCanaux, typeCanaux;
    monXML.recupererCanaux(&listeCanaux, &typeCanaux, this->uuidAutre);


    if(listeCanaux.size() > 0)
    {
        for(int i = 0; i<listeCanaux.size(); i++)
        {
            canal->push_back(QString::number(this->spinBoxSuppl[i]->value()));
            valeur->push_back(QString::number(this->sliderSuppl[i]->value()));
        }
    }
}
