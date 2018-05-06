#include "Drawer.h"

Drawer::Drawer(Position _center, Config _config) : 
    center(_center), config(_config)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    updateViewDistance(config.viewDistance);
}

Drawer::~Drawer() {}

void Drawer::translate(double x, double y)
{
    center = Position {
        center.x + x,
        center.y + y,
        center.angle
    };
}

void Drawer::rotate(double angle)
{
    center = Position {
        center.x,
        center.y,
        center.angle + angle
    };
}

void Drawer::updateViewDistance(double _viewDistance)
{
    viewDistance = _viewDistance;
    double param = atan((double)config.height/(double)config.width);
    Xscaling = viewDistance*cos(param);
    Yscaling = viewDistance*sin(param);
}

double Drawer::pixelView()
{
    return viewDistance*viewDistance/((config.width*config.width)+(config.height*config.height));
}

void Drawer::moveUp(double r)
{
    translate(+r*sin(center.angle),
              +r*cos(center.angle));
}
void Drawer::moveDown(double r)
{
    translate(-+r*sin(center.angle),
              -r*cos(center.angle));
}
void Drawer::moveLeft(double r)
{
    translate(-r*cos(center.angle),
              +r*sin(center.angle));
}
void Drawer::moveRight(double r)
{
    translate(+r*cos(center.angle),
              -r*sin(center.angle));
}

void Drawer::zoomIn()
{
    updateViewDistance(viewDistance-config.scaleSens);
}

void Drawer::zoomOut()
{
    updateViewDistance(viewDistance+config.scaleSens);
}

Point Drawer::transform(Point point)
{
    double x = (point.x-center.x)*cos(center.angle)
              -(point.y-center.y)*sin(center.angle);
    double y = (point.x-center.x)*sin(center.angle)
                +(point.y-center.y)*cos(center.angle);
    x /= Xscaling;
    y /= Yscaling;
    return Point {x, y};
}

int Drawer::drawPoints(PointSet points) 
{   
    int pointsNumber(0); 
    glBegin(GL_POINTS);
    for (PointSet::iterator it = points.begin(); it != points.end(); ++it)
    {
        Point point = (*it);
        point = transform(point);
        double x = point.x;
        double y = point.y;
        if (x <= 1 && x >= -1
         && y <= 1 && y >= -1)
        {
            glVertex2d(x,y);
            ++pointsNumber;
        }
    }
    glEnd();
    return pointsNumber;
}

void Drawer::drawLines(PointSet points)
{
    glBegin(GL_LINES);
    for (int i = 0; i < (points.size()-1); ++i)
    {
        Point p1 = transform(points[i]);
        Point p2 = transform(points[i+1]);
        glVertex2d(p1.x,p1.y);
        glVertex2d(p2.x,p2.y);
    }
    glEnd();
}
