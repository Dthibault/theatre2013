#ifndef SCENEAUTRES_H
#define SCENEAUTRES_H

#include <QWidget>
#include <QtGui>
#include <QString>
#include <QDebug>
#include <vector>
#include "gestionxml.h"

namespace Ui {
class SceneAutres;
}

class SceneAutres : public QWidget
{
    Q_OBJECT
    
public:
    explicit SceneAutres(QString sceneParente, QString uuidAutre, QWidget *parent = 0);
    ~SceneAutres();

    void recupererValeurs(QStringList *canal, QStringList *valeur);
    
private:
    Ui::SceneAutres *ui;

    QString uuidAutre;

    std::vector<QLabel*> labelSuppl;
    std::vector<QSlider*> sliderSuppl;
    std::vector<QSpinBox*> spinBoxSuppl;

signals:

    void signalDMX(int, int);

private slots:
    void actionDMX();
};

#endif // SCENEAUTRES_H
