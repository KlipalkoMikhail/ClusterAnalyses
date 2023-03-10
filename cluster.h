#ifndef CLUSTER_H
#define CLUSTER_H
#include "headers.h"
using namespace std;

class Cluster
{
    private:
        int ID;
        int FCID;
        int size;
        vector <short int> blong;
        Point center;
        int colour;
    public:
        Cluster();
        vector <double> factors;
        void setc(int col);
        int getID();
        int getFCID();
        int getSize();
        Point getCenter();
        void setID(int id);
        void setFCID(int fcid);
        void setSize(int sz);
        void setCenter(Point cen);
        void reserve(int N);
        void add_p(int k);
        void rem_p(int k);
        int getFieldSize();
        void ccenter(std::vector <Point> &points, int N);
        int getc();
        Point * getcen();
        vector <short int> p();
        short int tr(int k);
        ~Cluster();
};

#endif
