#ifndef CLOUD_H
#define CLOUD_H
using namespace std;
#include "point.h"
#include <iostream>
#include <vector>
using namespace std;

class Cloud
{
    private:
        int N;                          
        int NP;                         
        vector <Point*> points;    

    public:
        bool state_work;              
        Point center;    
        vector <double> factors;
        Cloud();
        Cloud(const Cloud& cloud);
        int size() const;
        bool work() const;
        void set_par_to_p(Point *p, int k);
        void create_space(int n, int np);
        double getx_p(int k);
        double gety_p(int k);
        int getnp_p(int k);
        vector <Point> get_points() const;
        void set_cen(double x, double y);
        void set_x_in_p(double x, int k);
        void set_y_in_p(double y, int k);
        void resize(int n);
        const Cloud & operator=(const Cloud & cloud);
        int get_np() const;
        ~Cloud();                    
};

#endif
