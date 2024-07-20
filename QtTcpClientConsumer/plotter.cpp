#include "plotter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <cmath>

Plotter::Plotter(QWidget *parent)
    : QWidget{parent}
{

}

void Plotter::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(QColor(255, 220, 0));
    brush.setStyle(Qt::SolidPattern);
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawRect(0,0,width(), height());
    pen.setColor(QColor(200,200,0));

    painter.setPen(pen);
    painter.drawLine(0,height()/2, width(), height()/2);

    pen.setColor(Qt::blue);
    painter.setPen(pen);

    float x0, x1, y0, y1;

    x0 = 0;
    y0 = sin(2*M_PI*x0);
    for(int i=1; i<width(); i++){
        x1 = 2*M_PI*i/(float)width();
        y1 = sin(2*M_PI*x1);
        painter.drawLine(x0*width(),
                         height()/2 - y0*height()/2,
                         x1*width(),
                         height()/2 - y1*height()/2);
        x0 = x1;
        y0 = y1;
    }
}
