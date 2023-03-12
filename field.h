#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "cloud.h"
#include "headers.h"
#include "cloud_parameters.h"
#pragma once
using namespace std;
class Field
{
    private:
        
    bool state_work;
    int N;
    int NCL;
    vector <Cloud> clouds;
    vector <Point> points;
    vector <vector <double>> D;             // матрица расстояний
    Cloud cloud_fictive_ptr;                // фиктивный указатель на облако
    Point point_fictive_ptr;                // фиктивный указатель
    
    public:
    Point center;                           // центр поля
    vector <double> factors;
    int ID;

    Field();
    int file_save();
    int size();
    void setSize(int number);
    void setCenter(Point cen);
    void set_state_work(int state);
    int nclouds();
    bool is_executed();
    vector <Cloud> *get_cl();
    double getx_p(int k);
    double gety_p(int k);
    Point p(int k);
    vector <Point> p();
    vector <Point> & get_points_reference();
    void state_gen(CloudParameters parameters);
    void add_cloud(Cloud &cld);
    void PrintPointsInFile();
    Cloud & get_cloud(int k);
    Cloud get_copy_cloud(int k);
    ~Field();
};
#endif
