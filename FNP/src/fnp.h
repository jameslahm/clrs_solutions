#ifndef FNP_H
#define FNP_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <float.h>

class Point
{
public:
    int x;
    int y;
    Point(int m, int n)
    {
        x = m;
        y = n;
    }
    ~Point(){}
};

typedef std::pair<double, std::pair<Point *, Point *>> RES;

RES findNeaestPoints(std::vector<Point *> &vec);
std::vector<Point*> randomPoints(int n);

#endif // FNP_H
