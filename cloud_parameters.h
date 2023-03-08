#ifndef CLOUD_PARAMETERS_H
#define CLOUD_PARAMETERS_H
#include <iostream>
using namespace std;

class Cloud_parameters
{
    public:
        int field_index;
        int size;
        double center_x;
        double center_y;
        double dispersion_x;
        double dispersion_y;

        Cloud_parameters()
        {
            field_index = 0;
            size = 100;
            center_x = 1;
            center_y = 1;
            dispersion_x = 1;
            dispersion_y = 1;
        }
        void load_index(istream & stream);
        void load_size(istream & stream);
        void load_center(istream & stream);
        void load_dispersion(istream & stream);
        void print_parameters(ostream & stream);
        ~Cloud_parameters(){}
};

#endif