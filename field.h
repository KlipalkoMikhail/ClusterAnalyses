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
    int getSize();
    Point getPoint(int k);
    vector <Point> getPoints();
    vector <Point>& getPointsReference();
    vector <Cloud>& getCloudsReference();
    Cloud& getCloudReference(int k);
    Cloud getCloud(int k);
    void setID(int id);
    void setDBID(int dbid);
    void setSize(int number);
    void setCenter(Point cen);
    void setNFC(int nfc);
    void setIsSaved(bool work);
    void setState(int state);
    void generate(CloudParameters parameters);
    void addCloud(Cloud &cld);
    bool is_executed();
    bool is_saved();
    int saveInFile();
    ~Field();
};
#endif
