#ifndef SCENEPARLED_H
#define SCENEPARLED_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
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
    explicit SceneParLED(QString uuidPar, QWidget *parent = 0);
    ~SceneParLED();

private:
    Ui::SceneParLED *ui;
    QString uuidDuPar;

    ColorWheel *monColorWheel;

    std::vector<QLabel*> labelSuppl;
    std::vector<QSlider*> sliderSuppl;
    std::vector<QSpinBox*> spinBoxSuppl;

signals:

    void signalDMX(int, int);

private slots:
    void actionDMX();

    void actionColorWheel(QColor);

};

#endif // SCENEPARLED_H
