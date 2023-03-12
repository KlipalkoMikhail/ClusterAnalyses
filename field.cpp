#include "headers.h"
#include "field.h"
#include "cloud_parameters.h"

void Field::add_cloud(Cloud &cld)
{
    clouds.resize(NCL + 1);
    clouds[NCL] = cld;
    vector <Point> auxillary_points = cld.get_points();
    for (int i = 0; i < cld.size(); i++)
    {
        points[N + i] = auxillary_points[i];
    }
    NCL++;
    N += cld.size();
}

Field::Field()
{
    state_work = 0;
    N = 0;
    NCL = 0;
    clouds.resize(100);
    points.resize(10000);
    factors.resize(6);
    D.resize(0);
}

Cloud Field::get_copy_cloud(int k)
{
     return clouds[k];
}

void Field::state_gen(CloudParameters cloud_parameters)
{
    using namespace std;
    default_random_engine generator;
    normal_distribution<double> distributionx(cloud_parameters.center_x, cloud_parameters.dispersion_x);
    normal_distribution<double> distributiony(cloud_parameters.center_y, cloud_parameters.dispersion_y);
    int i = NCL;

    clouds[i].create_space(cloud_parameters.size, i);
    clouds[i].center.setx(cloud_parameters.center_x);
    clouds[i].center.sety(cloud_parameters.center_x);
    NCL++;

    for (int k = 0; k < cloud_parameters.size; k++)
        clouds[i].set_par_to_p(&points[N + k], k);

    for (int k = 0; k < cloud_parameters.size; k++)
    {
        points[N + k].setx(distributionx(generator));
        points[N + k].sety(distributiony(generator));
        points[N + k].setnp(N + k);
    }

    N += cloud_parameters.size;
    D.resize(N);
    for (i = 0; i < N; i++)
        D[i].resize(0);
    state_work = 1;
}

void Field::PrintPointsInFile()
{
    string filename = "MyPoint_" + to_string(ID) + ".txt";
    ofstream PointFile(filename, ios::out | ios:: binary);

    for (int i = 0; i < N; i++)
        PointFile << points[i].getNP() << " " << points[i].getx() << " " << points[i].gety() << " ";
    PointFile.close();
}

int Field::file_save()
{
    std::ofstream fout("outfield.dat", ios::out);

    for (int i = 0; i < N; i++)
        fout << points[i].getx() << "\t\t" << points[i].gety() << endl;

    fout.close();

    return 0;
}

int Field::size()
{
    return N;
}
int Field::nclouds()
{
    return NCL;
}
bool Field::is_executed()
{
    return state_work;
}
vector <Cloud> *Field::get_cl()
{
    return &clouds;
}
double Field::getx_p(int k)
{
    return points[k].getx();
}
double Field::gety_p(int k)
{
    return points[k].gety();
}
Point Field::p(int k)
{
    return points[k];
}
vector <Point> Field::p()
{
    return points;
}
Cloud & Field::get_cloud(int k)
{   
    Cloud & cld = clouds[k];
    return cld;
}

void Field::setSize(int number)
{
    N = number;
}

void Field::setCenter(Point cen)
{
    center = cen;
}

vector <Point> & Field::get_points_reference()
{
    return points;
}

Field::~Field()
{
    //clouds.clear();
    points.clear();
    factors.clear();
}

void Field::set_state_work(int state)
{
    state_work = state;
}
