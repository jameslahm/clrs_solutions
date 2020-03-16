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
#include"fnp.h"
using namespace std;

ostream &operator<<(ostream &out, Point &a)
{
    out << "(" << a.x << "," << a.y << ")";
    return out;
}



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
 * @brief random generate Points
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
        int x = rand() % 16000 ;
        int y = rand() % 10000 ;
        vec.push_back(new Point(x, y));
    }
    return vec;
}

/**
 * @brief brute method
 * @param vec Points
 * @return RES
 */
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

/**
 * @brief find Neaest Points by divide and conquer
 * @param vec Points
 * @return RES
 */
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



//int main()
//{
//    vector<Point *> vec = randomPoints(10);
//    print(vec);
//    RES res1 = brute(vec);
//    RES res2 = findNeaestPoints(vec);

//    cout << res1.first << " " << (*res1.second.first) << " " << (*res1.second.second)<<endl;
//    cout << res2.first << " " << (*res2.second.first) << " " << (*res2.second.second)<<endl;
//}
//#endif // POINT_H
