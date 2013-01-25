#ifndef WIDGETCANALSUPPL_H
#define WIDGETCANALSUPPL_H

#include <QWidget>

namespace Ui {
    class WidgetCanalSuppl;
}

class WidgetCanalSuppl : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetCanalSuppl(QWidget *parent = 0);
    ~WidgetCanalSuppl();

private:
    Ui::WidgetCanalSuppl *ui;
};

#endif // WIDGETCANALSUPPL_H
