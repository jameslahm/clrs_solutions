/**
 * @file fnp.cpp
 * @author wangao
 * @brief Find nearest point pairs
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/**
 * @brief Point Class
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <float.h>
using namespace std;

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
    ~Point();
};

ostream &operator<<(ostream &out, Point &a)
{
    out << "(" << a.x << "," << a.y << ")";
    return out;
}

typedef pair<double, pair<Point *, Point *>> RES;

/**
 * @brief compare Point by x or y
 * 
 * @param a 
 * @param b 
 * @param type by x or y
 * @return true 
 * @return false 
 */
bool compare(Point *a, Point *b, int type)
{
    if (type == 0)
    {
        if (a->x < b->x)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (a->y < b->y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/**
 * @brief Compare Points by x
 * 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
bool compareX(Point *a, Point *b)
{
    return compare(a, b, 0);
}

/**
 * @brief Compare Points by y
 * 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
bool compareY(Point *a, Point *b)
{
    return compare(a, b, 1);
}

void print(vector<Point *> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << setw(7) << a[i]->x << " " << setw(7) << a[i]->y << endl;
    }
    cout << endl;
}

double distance(Point *a, Point *b)
{
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

/**
 * @brief random generate Points [-10000,10000]
 * 
 * @param n size
 * @return vector<Point>& 
 */
vector<Point *> randomPoints(int n)
{
    srand(unsigned(time(NULL)));
    vector<Point *> vec;
    for (int i = 0; i < n; i++)
    {
        int x = rand();
        int y = rand();
        vec.push_back(new Point(x, y));
    }
    return vec;
}

RES brute(vector<Point *> &vec)
{
    RES res = make_pair(DBL_MAX, pair<Point *, Point *>(new Point(0, 0), new Point(0, 0)));
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = i + 1; j < vec.size(); j++)
        {
            double temp = distance(vec[i], vec[j]);
            if (temp < res.first)
            {
                res.first = temp;
                res.second.first = vec[i];
                res.second.second = vec[j];
            }
        }
    }
    return res;
}

RES findNeaestPoints(vector<Point *> &vec)
{

    if (vec.size() < 10)
    {
        return brute(vec);
    }

    vector<Point *> XPoints = vec;
    vector<Point *> YPoints = vec;
    sort(XPoints.begin(), XPoints.end(), compareX);
    sort(YPoints.begin(), YPoints.end(), compareY);

    vector<Point *> leftPoints;
    leftPoints.assign(XPoints.begin(), XPoints.begin() + XPoints.size() / 2);
    vector<Point *> rightPoints;
    rightPoints.assign(XPoints.begin() + XPoints.size() / 2, XPoints.end());

    RES leftRes = findNeaestPoints(leftPoints);
    RES rightRes = findNeaestPoints(rightPoints);

    RES res = leftRes;
    if (leftRes.first > rightRes.first)
        res = rightRes;

    vector<Point *> IntervalPoints;
    for (int i = 0; i < YPoints.size(); i++)
    {
        if (YPoints[i]->x >= XPoints[XPoints.size() / 2]->x - res.first && YPoints[i]->x <= XPoints[XPoints.size() / 2]->x + res.first)
        {
            IntervalPoints.push_back(YPoints[i]);
        }
    }

    for (int i = 0; i < IntervalPoints.size(); i++)
    {
        for (int j = 0; j < 7 && (i + j + 1) < IntervalPoints.size(); j++)
        {
            double dis = distance(IntervalPoints[i], IntervalPoints[i + j + 1]);
            if (dis < res.first)
            {
                res.first = dis;
                res.second = make_pair(IntervalPoints[i], IntervalPoints[i + j + 1]);
            }
        }
    }

    return res;
}

int main()
{
    cout << "===================Begin Test(s)====================" << endl;
    cout << setw(16) << "N" << setw(16) << "Brute" << setw(16) << "Divide-Conquer" << endl;
    for (int i = 10; i < 10000000; i = i * 10)
    {
        vector<Point *> vec = randomPoints(i);
        clock_t start = clock();
        for (int j = 0; j < 3; j++)
        {
            findNeaestPoints(vec);
        }
        clock_t end = clock();
        double divideTime = double(end - start) / 3 / CLOCKS_PER_SEC;

        // start = clock();
        // for (int j = 0; j < 3; j++)
        // {
        //     brute(vec);
        // }
        // end = clock();
        // double bruteTime = double(end - start) / 3 / CLOCKS_PER_SEC;

        cout << setw(16) << i << setw(16) << setprecision(4) << fixed << " " << setw(16) << setprecision(4) << fixed << divideTime << endl;
    }
}