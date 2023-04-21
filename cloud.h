#ifndef CLOUD_H
#define CLOUD_H
using namespace std;
#include "point.h"
#include <iostream>
#include <vector>

class Cloud
{
    private:                          
        int ID;
        int N;                         
        vector <Point*> points;    

    public:
        bool state_work;              
        Point center;    
        vector <double> factors;

        Cloud();
        Cloud(const Cloud& cloud);
        int getID() const;
        int getSize() const;
        int getNPofPoint(int k);
        double getXofPoint(int k);
        double getYofPoint(int k);
        vector <Point> getPoints() const;
        void setCenter(double x, double y);
        void setXinPointByID(double x, int k);
        void setYinPointByID(double y, int k);
        void setPointByID(Point *p, int k);
        void generate(int n, int np);
        void resize(int n);
        bool is_executed() const;
        const Cloud & operator=(const Cloud & cloud);
        ~Cloud();                    
};

#endif
