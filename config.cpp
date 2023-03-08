#include <iostream>
#include "config.h"
#include <string>
#include <fstream>
using namespace std;

Config::Config()
{       /*
        ifstream configuration("config.txt", ios::binary | ios::in);
        if(!configuration.is_open())
        {
            cout << "Config is not existed\n";
            return;
        }
        */
        common_filename_of_points = "MyPoint_";
        common_field_size = 250;
        common_gx = 1.0;
        common_gy = 1.0;
        common_center_x = 1.0;
        common_center_y = 1.0;
        // configuration.close();
}

Config::~Config(){}

string Config::common_file_of_points(int id)
{
    string filename;
    filename = common_filename_of_points + to_string(id) + ".txt";
    return filename;
}
