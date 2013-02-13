#ifndef SCENESCANNER_H
#define SCENESCANNER_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <vector>
#include "gestionxml.h"

namespace Ui {
class SceneScanner;
}

class SceneScanner : public QWidget
{
    Q_OBJECT
    
public:
    explicit SceneScanner(QString sceneParente, QString uuidScanner, QWidget *parent = 0);
    ~SceneScanner();

    void recupererValeurs(QStringList *canal, QStringList *valeur);
    
private:
    Ui::SceneScanner *ui;
    QString uuidDuScanner;



    std::vector<QLabel*> labelSuppl;
    std::vector<QSlider*> sliderSuppl;
    std::vector<QSpinBox*> spinBoxSuppl;

signals:

    void signalDMX(int, int);



public slots:
    void actionDMX();

};

#endif // SCENESCANNER_H
