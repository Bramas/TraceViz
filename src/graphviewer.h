#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QWidget>
#include <QList>
#include <QElapsedTimer>
class Agent;
class QSlider;

class GraphViewer : public QWidget
{
    Q_OBJECT
public:
    explicit GraphViewer(QWidget *parent = 0);

    QList<Agent*> agents;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
signals:

public slots:
    void oneStep();

private:
    QSlider *slider;
    QElapsedTimer _elapsedTimer;

};

#endif // GRAPHVIEWER_H
