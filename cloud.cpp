#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include "headers.h"
#include "point.h"
#include <cfloat>
#define EPSILON 0.000001
#include "controller.h"

int Cloud::get_np() const
{
    return NP;
}

const Cloud & Cloud::operator=(const Cloud & cloud)
{
    try{
        N = cloud.size();
        NP = cloud.get_np();
        points.clear();
        resize(N);
        vector <Point> points_of_cloud = cloud.get_points();
        state_work = cloud.state_work;
        center = cloud.center;
        factors = cloud.factors;
        for (int i = 0; i < N; i++)
        {
            *(points[i]) = points_of_cloud[i];
        }
        cout << 1;
    } catch (std::bad_alloc &e) {
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

void Cluster::ccenter(std::vector <Point> &points, int N)
{
    double xmean = 0;
    double ymean = 0;

    int ln = 0;
    for (int i = 0; i < N; i++)
    {
        ln += blong[i];
    }
    xmean = scalx(points, blong, N)/ln;
    ymean = scaly(points, blong, N)/ln;

    center.setx(xmean);
    center.sety(ymean);
    center.setc(colour);
}

void Cloud::set_cen(double x, double y)
{
    center.setx(x);
    center.sety(y);
}

void Cloud::set_par_to_p(Point *p, int k)
{
    points[k] = p;
}
void Cloud::set_x_in_p(double x, int k)
{
    (*points[k]).setx(x);
}
void Cloud::set_y_in_p(double y, int k)
{
    (*points[k]).sety(y);
}

double Cloud::getx_p(int k)
{
    return (*(points[k])).getx();
}

double Cloud::gety_p(int k)
{
    return (*(points[k])).gety();
}

int Cloud::getnp_p(int k)
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

int Cloud::size() const
{
    return N;
}

bool Cloud::work() const
{
    return state_work;
}

void Cloud::create_space(int n, int np) // ������������
{
    N = n;
    state_work = 1;
    NP = np;
    points.resize(N);
}

vector <Point> Cloud::get_points() const
{
    vector <Point> p(N);
    for (int i = 0; i < N; i++)
        p[i] = *points[i];
    return p;
}
Cloud::~Cloud()
{
    points.clear();
    factors.clear();
}                      // ����������
