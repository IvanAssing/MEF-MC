#include "graphicwindow.h"

#include <mesh.h>
#include <cmath>
#include <iomanip>

#include <QImage>
#include <QString>
#include <QImageWriter>
#include <QDateTime>

GraphicWindow::GraphicWindow(QWidget *parent) :
    QGLWidget(parent)
{

    xmin = -100.;
    ymin = -100.;
    xmax = +100.;
    ymax = +100.;


    // Teste 01 - Geometria complexa
    /*
    double h = 3.1/10;

    mesh = new MC::Mesh(-125.1, -125,  h, 250/h, 250/h);

    double points[128];

    double DtoR = M_PI/180.;

    double ri = 74.5;

    double r[10] = {76.0, 80.0, 90.0, 100.0, 100.0, 100.0, 90.0, 80.0, 76.0, ri};
    double b[10] = {3.7, 7.5, 7.5, 7.5, 22.5, 37.5, 37.5, 37.5, 41.3, 45.0};

    double alpha;
    int k=0;

    points[k++] = 0.0;
    points[k++] = 0.0;
    points[k++] = ri/2.0;
    points[k++] = 0.0;
    points[k++] = ri;
    points[k++] = 0.0;


    for(int i=0; i<6; i++){
        alpha = i*45.0*DtoR;
        for(int j=0; j<10; j++){
            points[k++] = r[j]*cos(alpha+b[j]*DtoR);
            points[k++] = r[j]*sin(alpha+b[j]*DtoR);
        }
    }

    points[k++] = 0.0;
    points[k++] = -ri/2.0;


    mesh->addBoundaryNodes(64, points);

      mesh->createMesh_2();
     // */


    // Teste 02 - Circulo
    /*

    double h = 3.1/200;

    mesh = new MC::Mesh(-125.1, -125,  h, 250/h, 250/h);

    double points[12800];

    double rx = 10.;
    double ry = 10.;

    int np = 400;

    double da = 2*M_PI/np;


    int k=0;

    for(int i=0; i<=np; i++)
    {
            points[k++] = rx*cos(i*da);
            points[k++] = ry*sin(i*da);
    }



    mesh->addBoundaryNodes((k-1)/2., points);

      mesh->createMesh_2();

      double areaN = mesh->evalArea();
              double areaA = M_PI*rx*rx;

      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nNE = "<<mesh->nElements;
      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nAreaN = "<<areaN;
      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nAreaA = "<<areaA;
      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nErro = "<<100*(areaN-areaA)/areaA<<" %\n\n";

           // */


    // Teste 03 - Retangulo
    /*

    double h = 1.3;

    mesh = new MC::Mesh(-125.1, -125,  h, 250/h, 250/h);

    double points[128];

    double a = 100.;
    double b = 100.;


    int k=0;

    points[k++] = -a/2;
    points[k++] = -b/2;
    points[k++] = 0.0;
    points[k++] = -b/2;
    points[k++] = a/2;
    points[k++] = -b/2;


    points[k++] = a/2;
    points[k++] = 0.0;
    points[k++] = a/2;
    points[k++] = b/2;

    points[k++] = 0.0;
    points[k++] = b/2;
    points[k++] = -a/2;
    points[k++] = b/2;

    points[k++] = -a/2;
    points[k++] = 0.0;



    mesh->addBoundaryNodes(8, points);

    mesh->createMesh_2();

    double areaN = mesh->evalArea();
    double areaA = a*b;

      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nNE = "<<mesh->nElements;
      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nAreaN = "<<areaN;
      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nAreaA = "<<areaA;
      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nErro = "<<100*(areaN-areaA)/areaA<<" %\n\n";


    // */

      // Teste 04 - Parabola
      ///*

      double h = 10;

      mesh = new MC::Mesh(-125.1, -125,  h, 250/h, 250/h);

      double points[128];

      double a = 100.0002;
      double b = 100.;


      int k=0;

      points[k++] = -a;
      points[k++] = 0.0;
      points[k++] = 0.0;
      points[k++] = 0.0;
      points[k++] = a;
      points[k++] = 0.0;


      points[k++] = 0.0;
      points[k++] = a;

      mesh->addBoundaryNodes(4, points);


//      points[k++] = 0.0;
//      points[k++] = 0.0;
//      points[k++] = a/2.;
//      points[k++] = 0.0;
//      points[k++] = a;
//      points[k++] = 0.0;


//      points[k++] = 0.0;
//      points[k++] = a;

//      points[k++] = -a;
//      points[k++] = 0.0;

//      points[k++] = -a/2.;
//      points[k++] = 0.0;

//      mesh->addBoundaryNodes(6, points);

      mesh->createMesh_2();

//      double areaN = mesh->evalArea();
//      double areaA = a*b;

//      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nNE = "<<mesh->nElements;
//      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nAreaN = "<<areaN;
//      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nAreaA = "<<areaA;
//      std::cout<<std::setprecision(10)<<std::setw(15)<<std::scientific<<"\nErro = "<<100*(areaN-areaA)/areaA<<" %\n\n";

      // */

}


void GraphicWindow::initializeGL()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void GraphicWindow::resizeGL(int width, int height)
{

    double width_ = static_cast<double>(this->width());
    double height_ = static_cast<double>(this->height());

    if (width_ > height_)
    {
        height_ = height_?height_:1;
        double correction = 0.5 * ( width_/ height_ * (ymax-ymin) - (xmax-xmin) );
        xmin   -= correction;
        xmax +=correction;
    }
    else
    {
        width_ = width_?width_:1;
        double correction = 0.5 * ( height_ / width_ * (xmax-xmin) - (ymax-ymin) );
        ymin   -= correction;
        ymax  += correction;
    }

    glViewport( 0, 0, (GLint)width, (GLint)height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xmin, xmax, ymin, ymax, 1.0, -1.0);
    //gluPerspective(60, (float)width/height, 0.1, 50000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void GraphicWindow::wheelEvent(QWheelEvent *event)
{
    double zoom_factor = -event->delta()/120*0.2;


    double X_opengl = event->x()/static_cast<double>(this->width())*(xmax - xmin)+xmin;
    double Y_opengl  = (this->height()-event->y())/static_cast<double>(this->height())*(ymax - ymin)+ymin;

    xmin -= (X_opengl-xmin)*zoom_factor;
    xmax += (xmax-X_opengl)*zoom_factor;

    ymin -= (Y_opengl-ymin)*zoom_factor;
    ymax += (ymax-Y_opengl)*zoom_factor;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(xmin, xmax, ymin, ymax, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    this->repaint();

}

void GraphicWindow::mousePressEvent(QMouseEvent *event)
{
    isMousePress = true;
    panX = event->x();
    panY = event->y();



}


void GraphicWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePress = false;
}

void GraphicWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QDateTime now = QDateTime::currentDateTime();

    QString filename = QString("mef-mc-snapshot-")
            + now.toString("yyyyMMddhhmmsszzz") + QString(".png");

    this->updateGL();

    this->grabFrameBuffer(true).save(filename, "PNG", 100);

}


void GraphicWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        double X_opengl = (-event->x()+panX)/static_cast<double>(this->width())*(xmax - xmin);
        double Y_opengl  = (event->y()-panY)/static_cast<double>(this->height())*(ymax - ymin);

        xmax += X_opengl;
        xmin += X_opengl;

        ymax += Y_opengl;
        ymin += Y_opengl;

        panX = event->x();
        panY = event->y();


        glOrtho(xmin, xmax, ymin, ymax, 1.0, -1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        this->repaint();

    }



    updateGL();

}



void GraphicWindow::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glLoadIdentity();
    //double ddx = 1.75 * (max_.x() - min_.x()) * d_x;
    //double ddy = 1.75 * (max_.y() - min_.y()) * d_y;

    mesh->draw();



}
