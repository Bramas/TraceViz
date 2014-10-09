#include "agent.h"
#include <QTimer>
#include <QDebug>
#include "graphviewer.h"

Agent::Agent(QVector2D startPosition)
{
    positions.insert(0,destination = QVector2D(600.0* qrand()/RAND_MAX, 600.0*qrand()/RAND_MAX));
    if(!startPosition.isNull())
    {
        positions[0] = startPosition;
    }
    speed = 100;
}
void Agent::tick(quint64 elapsed)
{
    if((positions[0] - destination).length() < 2)
    {
        destination = QVector2D(600.0* qrand()/RAND_MAX, 600.0*qrand()/RAND_MAX);
    }

    positions[0] += (destination - positions[0]).normalized()*speed*elapsed/1000.0;
}
