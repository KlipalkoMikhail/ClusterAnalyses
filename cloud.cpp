#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include "headers.h"
#include "point.h"
#include <cfloat>
#define EPSILON 0.000001
#include "controller.h"

int Cloud::getID() const
{
    return ID;
}

Cloud::Cloud(const Cloud &cloud)
{
    try
    {
        N = cloud.getSize();
        ID = cloud.getID();
        points.clear();
        points.resize(N);
        vector<Point> points_of_cloud = cloud.getPoints();
        for (size_t i; i < points.size(); i++)
        {
            points[i] = new Point;
            (*points[i]).setx(points_of_cloud[i].getx());
            (*points[i]).sety(points_of_cloud[i].gety());
            (*points[i]).setnp(points_of_cloud[i].getNP());
            (*points[i]).setc(points_of_cloud[i].getColour());
        }
    }
    catch (std::bad_alloc &e)
    {
        throw new MyException(EC_MEMORY, "Cannot get memory\n");
    }
}

const Cloud &Cloud::operator=(const Cloud &cloud)
{
    try
    {
        N = cloud.getSize();
        ID = cloud.getID();
        points.clear();
        points.resize(N);
        vector<Point> points_of_cloud = cloud.getPoints();
        state_work = cloud.state_work;
        center = cloud.center;
        factors = cloud.factors;
        for (int i = 0; i < N; i++)
        {
            *(points[i]) = points_of_cloud[i];
        }
        cout << 1;
    }
    catch (std::bad_alloc &e)
    {
        throw new MyException(EC_MEMORY, "Cannot get memory\n");
    }

    return *this;
}

void Cloud::resize(int n)
{
    points.resize(n);
    for (int i = 0; i < n; i++)
    {
        points[i] = new Point;
    }
}

void Cluster::ccenter(std::vector<Point> &points, int N)
{
    double xmean = 0;
    double ymean = 0;

    int ln = 0;
    for (int i = 0; i < N; i++)
    {
        ln += blong[i];
    }
    xmean = scalx(points, blong, N) / ln;
    ymean = scaly(points, blong, N) / ln;

    center.setx(xmean);
    center.sety(ymean);
    center.setc(colour);
}

void Cloud::setCenter(double x, double y)
{
    center.setx(x);
    center.sety(y);
}

void Cloud::setPointByID(Point *p, int k)
{
    points[k] = p;
}

void Cloud::setXinPointByID(double x, int k)
{
    (*points[k]).setx(x);
}
void Cloud::setYinPointByID(double y, int k)
{
    (*points[k]).sety(y);
}

double Cloud::getXofPoint(int k)
{
    return (*(points[k])).getx();
}

double Cloud::getYofPoint(int k)
{
    return (*(points[k])).gety();
}

int Cloud::getNPofPoint(int k)
{
    return (*(points[k])).getNP();
}

Cloud::Cloud()
{
    center.setx(0);
    center.sety(0);
    state_work = 0;
    N = 0;
    factors.resize(6);
}

int Cloud::getSize() const
{
    return N;
}

bool Cloud::is_executed() const
{
    return state_work;
}

void Cloud::generate(int n, int np) // ������������
{
    N = n;
    state_work = 1;
    ID = np;
    points.resize(N);
}

vector<Point> Cloud::getPoints() const
{
    vector<Point> p(N);
    for (int i = 0; i < N; i++)
        p[i] = *points[i];
    return p;
}

Cloud::~Cloud()
{
    points.clear();
    factors.clear();
}
