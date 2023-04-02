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
    
    int ID;
    int DBID;
    int N;
    int NCL;
    int NFC;

    bool state_work;
    bool isSaved;

    vector <Cloud> clouds;
    vector <Point> points;
    vector <vector <double>> D;             // матрица расстояний
    Cloud cloud_fictive_ptr;                // фиктивный указатель на облако
    Point point_fictive_ptr;                // фиктивный указатель
    
    public:

    Point center;                           // центр поля
    vector <double> factors;

    Field();
    int getID();
    int getDBID();
    void setID(int id);
    void setDBID(int dbid);
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
    int getNFC();
    void setNFC(int nfc);
    Point p(int k);
    vector <Point> p();
    vector <Point> & get_points_reference();
    void state_gen(CloudParameters parameters);
    void add_cloud(Cloud &cld);
    bool is_saved();
    void setIsSaved(bool work);
    
    Cloud & get_cloud(int k);
    Cloud get_copy_cloud(int k);
    ~Field();
};
#endif
