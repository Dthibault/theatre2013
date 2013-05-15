#ifndef SCENEPARLED_H
#define SCENEPARLED_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <vector>
#include "colorwheel.h"
#include "gestionxml.h"

namespace Ui {
    class SceneParLED;
}

class SceneParLED : public QWidget
{
    Q_OBJECT

public:
    explicit SceneParLED(QString sceneParente, QString uuidPar, QWidget *parent = 0);
    ~SceneParLED();

    void recupererValeurs(QStringList *canal, QStringList *valeur);

private:
    Ui::SceneParLED *ui;
    QString uuidDuPar;

    ColorWheel *monColorWheel;

    std::vector<QLabel*> labelSuppl;
    std::vector<QSlider*> sliderSuppl;
    std::vector<QSpinBox*> spinBoxSuppl;

signals:

    void signalDMX(int, int);

public slots:
    void actionDMX();

private slots:


    void actionColorWheel(QColor);

};

#endif // SCENEPARLED_H
