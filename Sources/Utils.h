#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <utility>

using namespace std;

#define INFO "\033[32m::\033[37m "
#define ERR  "\033[31m::\033[37m "
#define WARN "\033[33m::\033[37m "

#define PI  3.14159265358979323846

typedef struct 
{
    int width,height;
    int maxFramerate;
    double viewDistance;
    double travelSpeed, rotSpeed, scaleSens;
} Config;

typedef struct 
{
    double x,y,angle;
} Position;

typedef struct 
{
    double x,y;
} Point;

typedef vector<Point> PointSet;
typedef pair<Point,Point> BranchSet;

#endif
