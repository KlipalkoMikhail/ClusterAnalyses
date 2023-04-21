#include "headers.h"
#include "field.h"
#include "cloud_parameters.h"

void Field::addCloud(Cloud &cld)
{
    clouds.resize(NCL + 1);
    clouds[NCL] = cld;
    vector <Point> auxillary_points = cld.getPoints();
    for (int i = 0; i < cld.getSize(); i++)
    {
        points[N + i] = auxillary_points[i];
    }
    NCL++;
    N += cld.getSize();
}

Field::Field()
{
    ID = 0;
    DBID = 0;
    state_work = 0;
    N = 0;
    NFC = 0;
    NCL = 0;
    isSaved = 0;
    clouds.resize(100);
    points.resize(10000);
    factors.resize(8);
    D.resize(0);
}

Cloud Field::getCloud(int k)
{
     return clouds[k];
}

int Field::getNFC()
{
    return NFC;
}

void Field::setNFC(int nfc)
{
    NFC = nfc;
}

bool Field::is_saved()
{
    return isSaved;
}

void Field::setIsSaved(bool work)
{
    isSaved = work;
}

void Field::generate(CloudParameters cloud_parameters)
{
    using namespace std;
    default_random_engine generator;
    normal_distribution<double> distributionx(cloud_parameters.center_x, cloud_parameters.dispersion_x);
    normal_distribution<double> distributiony(cloud_parameters.center_y, cloud_parameters.dispersion_y);
    int i = NCL;

    clouds[i].generate(cloud_parameters.size, i);
    clouds[i].center.setx(cloud_parameters.center_x);
    clouds[i].center.sety(cloud_parameters.center_x);
    NCL++;

    for (int k = 0; k < cloud_parameters.size; k++)
        clouds[i].setPointByID(&points[N + k], k);

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

int Field::saveInFile()
{
    string filename = "OutField_" + to_string(ID) + ".txt";
    std::ofstream fout(filename, ios::out);

    for (int i = 0; i < N; i++)
        fout << points[i].getx() << "\t\t" << points[i].gety() << endl;

    fout.close();

    return 0;
}

int Field::getSize()
{
    return N;
}
int Field::getCloudsSize()
{
    return NCL;
}
bool Field::is_executed()
{
    return state_work;
}

vector <Cloud> &Field::getCloudsReference()
{
    return clouds;
}
Point Field::getPoint(int k)
{
    return points[k];
}
vector <Point> Field::getPoints()
{
    return points;
}
Cloud & Field::getCloudReference(int k)
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

vector <Point> & Field::getPointsReference()
{
    return points;
}

Field::~Field()
{
    vector <Cloud> ().swap(clouds);
    vector <Point> ().swap(points);
    vector <vector <double>> ().swap(D);
    vector <double> ().swap(factors);
}

void Field::setState(int state)
{
    state_work = state;
}

int Field::getID()
{
    return ID;
}

int Field::getDBID()
{
    return DBID;
}

void Field::setID(int id)
{
    ID = id;
}

void Field::setDBID(int dbid)
{
    DBID = dbid;
}

