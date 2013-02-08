#ifndef SCENELYRE_H
#define SCENELYRE_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <vector>
#include "gestionxml.h"

namespace Ui {
    class SceneLyre;
}

class SceneLyre : public QWidget
{
    Q_OBJECT

public:
    explicit SceneLyre(QString sceneParente, QString uuidLyre, QWidget *parent = 0);
    ~SceneLyre();

    void recupererValeurs(QStringList *canal, QStringList *valeur);

private:
    Ui::SceneLyre *ui;


    QString uuidDuLyre;

    std::vector<QLabel*> labelSuppl;
    std::vector<QSlider*> sliderSuppl;
    std::vector<QSpinBox*> spinBoxSuppl;

signals:

    void signalDMX(int, int);

private slots:
    void actionDMX();
};

#endif // SCENELYRE_H
