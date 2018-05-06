#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>
#include <cstdlib>

#include "Utils.h"

using namespace std;

class LSystem
{
    public:
    LSystem(string fRule, string xRule, Position _startPos, double _depth, double _angle);
    string florish(string axiom, int gens);
    PointSet grow(string axiom, int gens);
    PointSet shape(string axiom, int gens, int seed);
    BranchSet branches(string axiom, int gens);

    private:
    string F_RULE;
    string X_RULE;
    Position startPos;
    double depth,angle;
};

#endif // L_SYSTEM_H
