#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

Plotter::Plotter(QWidget *parent)
    : QWidget{parent}
{}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(QColor(0, 0, 0));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0, 0, width(), height());

    if (valores.size() < 2) {
        return;
    }

    pen.setColor(QColor(0, 170, 255));
    pen.setWidth(2);
    painter.setPen(pen);

    double valMin = valores[0];
    double valMax = valores[0];
    for(size_t i = 0; i < valores.size(); i++){
        if(valores[i] < valMin) valMin = valores[i];
        if(valores[i] > valMax) valMax = valores[i];
    }

    if(valMax == valMin) valMax = valMin + 1;

    double x1, y1, x2, y2;

    x1 = 0;
    y1 = height() - ((valores[0] - valMin) / (valMax - valMin)) * height();

    for (size_t i = 1; i < valores.size(); ++i) {

        x2 = (double)i / (valores.size() - 1) * width();

        y2 = height() - ((valores[i] - valMin) / (valMax - valMin)) * height();

        painter.drawLine(x1, y1, x2, y2);

        x1 = x2;
        y1 = y2;
    }
}

void Plotter::setDados(std::vector<double> t, std::vector<double> v)
{
    tempos = t;
    valores = v;
    update();
}
