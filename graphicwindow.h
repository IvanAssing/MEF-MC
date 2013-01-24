#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QCursor>

class GraphicWindow : public QGLWidget
{
        Q_OBJECT
    public:
        explicit GraphicWindow(QWidget *parent = 0);

        double xmax, xmin, ymax, ymin, panX, panY;
        bool isMousePress;
        
    signals:
        
    public slots:

        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();

        void wheelEvent(QWheelEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        
};

#endif // GRAPHICWINDOW_H
