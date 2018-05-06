#ifndef DRAWER_H
#define DRAWER_H

#include <iostream>
#include <cmath>
#include <GL/gl.h>

#include "Utils.h"

using namespace std;

class Drawer
{
    public:

    Drawer(Position _center, Config _config);
    ~Drawer();
    void translate(double x, double y);
    void moveUp(double r);
    void moveDown(double r);
    void moveLeft(double r);
    void moveRight(double r);
    void rotate(double angle);
    void zoomIn();
    void zoomOut();
    Point transform(Point point);
    void updateViewDistance(double _viewDistance);
    double pixelView();
    int drawPoints(PointSet points);
    void drawLines(PointSet points);

    private:

    Position center;
    Config config;
    double viewDistance,Xscaling,Yscaling;
};

#endif // DRAWER_H
