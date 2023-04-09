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
    int getNFC();
    int getCloudsSize();
    void setID(int id);
    void setDBID(int dbid);
    void setSize(int number);
    void setCenter(Point cen);
    void setNFC(int nfc);
    void setIsSaved(bool work);
    void set_state_work(int state);
    int size();
    bool is_executed();
    bool is_saved();
    vector <Cloud> *get_cl();
    double getx_p(int k);
    double gety_p(int k);
    Point p(int k);
    vector <Point> p();
    vector <Point> & get_points_reference();
    void state_gen(CloudParameters parameters);
    void add_cloud(Cloud &cld);
    int file_save();
    
    Cloud & get_cloud(int k);
    Cloud get_copy_cloud(int k);
    ~Field();
};
#endif
