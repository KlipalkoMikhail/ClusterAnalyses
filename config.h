#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <string>
using namespace std;

class Config
{
    public:
        string common_filename_of_points;
        int common_field_size;
        double common_gx;
        double common_gy;
        double common_center_x;
        double common_center_y;
        string common_file_of_points(int id);
        
        Config();
        ~Config();
};

#endif