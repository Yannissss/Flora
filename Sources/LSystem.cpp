#include "LSystem.h"

LSystem::LSystem(string fRule, string xRule, Position _startPos, 
    double _depth, double _angle) :
    F_RULE(fRule), X_RULE(xRule), startPos(_startPos), depth(_depth), angle(_angle)
{}

string LSystem::florish(string axiom, int gens)
{
    // Generating sequence using F & X Rules
    string sequence(axiom);
    for (int i = 0; i <= gens; ++i)
    {
        ostringstream cache;
        for (int j = 0; j < sequence.length(); ++j)
        {
            switch (sequence[j])
            {
                case 'F':
                    cache << F_RULE;
                    break;
                case 'X':
                    cache << X_RULE;
                    break;
                default:
                    cache << sequence[j];
                    break;
            }
        }
        sequence = cache.str();
    }  
    return sequence;
}

PointSet LSystem::grow(string axiom, int gens)
{

    // Interprating the sequece geometricly with a simple 2D-turtle
    string sequence(florish(axiom,gens));
    PointSet points;
    points.push_back(Point {startPos.x, startPos.y});
    stack<Position> posStack;
    posStack.push(startPos);
    for (int i = 0; i < sequence.length(); ++i)
    {
        Position pos = posStack.top();
        switch (sequence[i])
        {
            case 'F':
                posStack.pop();
                pos.x += depth*cos(pos.angle);
                pos.y += depth*sin(pos.angle);
                posStack.push(pos);
                points.push_back(Point {
                    pos.x, pos.y
                });
                break;
            case '+':
                posStack.pop();
                pos.angle += angle*PI/180;
                posStack.push(pos);
                break;
            case '-':
                posStack.pop();
                pos.angle -= angle*PI/180;
                posStack.push(pos);
                break;
            case '[':
                posStack.push(pos);
                break;
            case ']':
                posStack.pop();
                break;
        }
    }
    return points;
}

PointSet LSystem::shape(string axiom, int gens, int seed)
{
    string sequence(florish(axiom,gens));
    // Interprating the sequece geometricly with a simple 2D-turtle
    PointSet points;
    points.push_back(Point {startPos.x, startPos.y});
    stack<Position> posStack;
    posStack.push(startPos);
    for (int i = 0; i < sequence.length(); ++i)
    {
        Position pos = posStack.top();
        switch (sequence[i])
        {
            case 'F':
                posStack.pop();
                pos.x += depth*cos(pos.angle);
                pos.y += depth*sin(pos.angle);
                posStack.push(pos);
                points.push_back(Point {
                    pos.x, pos.y
                });
                break;
            case '+':
                posStack.pop();
                pos.angle += angle*PI/180;
                posStack.push(pos);
                break;
            case '-':
                posStack.pop();
                pos.angle -= angle*PI/180;
                posStack.push(pos);
                break;
            case '[':
                posStack.push(pos);
                break;
            case ']':
                posStack.pop();
                break;
        }
    }
    return points;
}


BranchSet LSystem::branches(string axiom, int gens)
{
    return BranchSet(Point {0,0}, Point {0,0});
}
