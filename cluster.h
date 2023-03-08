#ifndef CLUSTER_H
#define CLUSTER_H
#include "headers.h"
using namespace std;

class Cluster
{
private:
    vector <short int> blong;
    Point center;
    int colour;
public:
    vector <double> factors;
    Cluster();
    void setc(int col);
    void reserve(int N);
    void add_p(int k);
    void rem_p(int k);
    void ccenter(std::vector <Point> &points, int N);
    int getc();
    Point * getcen();
    vector <short int> p();
    short int tr(int k);
    ~Cluster();
};

#endif
