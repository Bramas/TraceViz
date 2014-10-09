#include "graphviewer.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QSlider>
#include "agent.h"

GraphViewer::GraphViewer(QWidget *parent) :
    QWidget(parent)
{
    QTimer *timer = new QTimer();
    timer->setInterval(1000);
    slider = new QSlider(Qt::Horizontal, this);
    connect(timer, SIGNAL(timeout()), this, SLOT(oneStep()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(update()));
    timer->start();
    _elapsedTimer.start();
}

void GraphViewer::oneStep()
{
    slider->setValue(slider->value()+1);
}

void GraphViewer::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    quint64 elapsed = _elapsedTimer.elapsed();
    _elapsedTimer.start();
    //painter.setRenderHint(QPainter::Antialiasing);

    foreach(Agent* agent, agents)
    {
        agent->tick(elapsed);
    }
    painter.setPen(QPen(QColor(0,0,0,255)));
    painter.setBrush(QBrush(QColor(200,200,200,255)));
    foreach(Agent* agent, agents)
    {
        painter.drawEllipse(agent->positions[0].toPoint(), 2,2);
    }
    painter.setPen(QPen(QColor(0,0,0,80)));
    foreach(Agent* agent, agents)
    {
        foreach(Agent* neig, agents)
        {
            if(agent->positions[0] != neig->positions[0] && agent->positions[0].distanceToPoint(neig->positions[0]) < 25)
            {
                painter.drawLine(agent->positions[0].toPoint(), neig->positions[0].toPoint());
            }
        }
    }
    painter.drawText(0, 30, QString::number(1000.0/elapsed));
}

void GraphViewer::mousePressEvent(QMouseEvent * event)
{
    Agent * a = new Agent(QVector2D(event->pos()));
    agents.append(a);
    update();
}
