#include <bits/stdc++.h>
#include "headers.h"
#include "Find_Cluster.h"
#include "save_bd.h"
#include <fstream>
#include <iostream> 
#include "config.h"
#include <iomanip>
#define EPSILON 0.0001
using namespace std;

void FieldLoader::printHeaderLineFieldFile(fstream &data_base)
{
    string ReadedLine;

    getline(data_base, ReadedLine);
    if (ReadedLine != PREHEADER_LINE)
    {
        data_base.seekp(0, ios::beg);
        data_base << PREHEADER_LINE;
        data_base << HEADER_LINE;
    }
    data_base.seekg(2*HeaderLineSize + 1, ios::beg);
}

void FieldLoader::printParametersInFieldFile(Field &field, fstream &data_base)
{
    data_base.seekg(HeaderLineSize*field.ID, ios::beg);
    data_base.setf(ios::fixed);

    data_base << "| " << setw(2) << field.ID << " ";
    data_base << " " << setw(8) << field.size() << " ";
    data_base << " " << setw(12) << setprecision(4) << showpos << field.center.getx() << " ";
    data_base << " " << setw(12) << setprecision(4) << showpos << field.center.gety() << " ";
    data_base << "    " << setw(8) << setprecision(2) << showpos << field.factors[2] << " " << setw(8) << setprecision(2) << showpos << field.factors[3] << "   ";
    data_base << " " << setw(8) << setprecision(2) << showpos << field.factors[4] << " " << setw(8) << setprecision(2) << showpos << field.factors[5] << "   ";
    data_base << "  " << setw(8) << setprecision(2) << showpos << field.factors[6] << " " << setw(8) << setprecision(2) << showpos << field.factors[7] << "   ";
    data_base << "  " << setw(15) << "MyPoint_" << field.ID << ".txt" << "  |" << endl;
}

void FieldLoader::saveField(Field &field)
{
    fstream CardField("CardField.db", ios::binary | ios::app | ios::out);

    printHeaderLineFieldFile(CardField);
    printParametersInFieldFile(field, CardField);

    CardField.close();
}

void FieldLoader::loadSize(Field &field, fstream &data_base)
{
    data_base.seekg(HeaderLineSize*(field.ID + 2) + 4);
    int size = 0;
    data_base >> size;
    //cout << size << endl;
    if (data_base.fail())
        cout << "bad" << endl;
    field.setSize(size);
}

void FieldLoader::loadCenter(Field &field, fstream &data_base)
{
    Point center;
    double x, y;

    data_base >> x >> y;
    center.setx(x);
    center.sety(y);

    field.factors[0] = x;
    field.factors[1] = y;
    //cout << x << endl << y << endl;

    field.setCenter(center);
}

void FieldLoader::loadEigenVectors(Field &field, fstream &data_base)
{
    data_base >> field.factors[2] >> field.factors[3] 
              >> field.factors[4] >> field.factors[5] 
              >> field.factors[6] >> field.factors[7];
    //cout << field.factors[2] << endl
    //        << field.factors[3] << endl
     //       << field.factors[4] << endl
       //     << field.factors[5] << endl
         //   << field.factors[6] << endl
           // << field.factors[7] << endl;
}

void FieldLoader::loadPointsFile(Field &field, fstream &data_base)
{
    string filename;
    ifstream points_file;
    vector <Point> & points = field.get_points_reference();
    Point point;
    double x, y;
    int NP;
    int i = 0;

    data_base >> filename;
    //cout << filename << endl;
    points_file.open(filename);
    if (!points_file)
    {
        cerr << "File cannot be open!" << endl;
        return;
    }

    while (!points_file.eof())
    {
        points_file >> NP >> x >> y;
        //cout << NP << '\t' << x << '\t' << y << endl;
        point.setnp(NP);
        point.setx(x);
        point.sety(y);
        point.setnp(i);
        points[i] = point;
        i++;
    }
    points_file.close();
}

void FieldLoader::setFlags(Field &field, int index)
{
    const int STATE = 1;
    field.ID = index;
    field.set_state_work(STATE);
    //cout << "IS EXEC: " << field.is_executed() << endl;
}

void FieldLoader::loadField(Field &field, int id)
{
    fstream CardField("CardField.db", ios::binary | ios::in);
    
    loadSize(field, CardField);
    loadCenter(field, CardField);
    loadEigenVectors(field, CardField);    
    loadPointsFile(field, CardField);
    setFlags(field, id);

    CardField.close();  
}

void FindClusterLoader::printHeaderLineInFile(fstream &data_base)
{
    string ReadedLine;

    getline(data_base, ReadedLine);
    if (ReadedLine != PREHEADER_LINE)
    {
        data_base.seekp(0, ios::beg);
        data_base << PREHEADER_LINE;
        data_base << HEADER_LINE;
    }
    data_base.seekg(2*HeaderLineSize + 1, ios::beg);
}

bool FindClusterLoader::isFalseIndex(int FindClusterID)
{
    if (FindClusterID >= SizeLines)
    {
        cout << "Index out of range\n";
        return 0;
    }
    else return 1;
}

void FindClusterLoader::SeekAndSetAllID(FindCluster &findCluster, int FindClusterID, int FieldID, fstream &data_base)
{
    int fID;
    int fcID;
    int Index_Line = 2;
    const int fID_position = 17 + 26 + 5 + 11 + 1;

    data_base.seekg(HeaderLineSize*2 + 1);
    data_base >> fcID;
    data_base.seekg(fID_position, ios::cur);
    data_base >> fID;

    while (fcID != FindClusterID && fID != FieldID && Index_Line <= SizeLines)
    {
        data_base.seekg(HeaderLineSize*(3 + Index_Line)  + 1, ios::beg);
        data_base >> fcID;
        data_base.seekg(fID_position, ios::cur);
        data_base >> fID;
        if (data_base.fail())
            cout << "bad" << endl;
        Index_Line++;
    }

    findCluster.setID(fcID);
    findCluster.setFieldID(fID);
    data_base.seekg(HeaderLineSize*(2 + Index_Line)  + 4, ios::beg);
}

void FindClusterLoader::loadName(FindCluster &findCluster, fstream &data_base)
{
    string name;

    data_base >> name;
    //cout << filename << endl;
    findCluster.setName(name);
}

void FindClusterLoader::loadSize(FindCluster &findCluster, fstream &data_base)
{
    int size = 0;
    data_base >> size;
    if (data_base.fail())
        cout << "bad size" << endl;
    findCluster.setSize(size);
}

void FindClusterLoader::loadKnumber(FindCluster &findCluster, fstream &data_base)
{
    int Knumber = 0;
    data_base >> Knumber;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    findCluster.setKnumber(Knumber);
}

void FindClusterLoader::loadRnumber(FindCluster &findCluster, fstream &data_base)
{
    double Rnumber = 0;
    data_base >> Rnumber;
    if (data_base.fail())
        cout << "bad" << endl;
    findCluster.setRnumber(Rnumber);
}

void FindClusterLoader::printParametersInFindClusterFile(fstream &data_base, FindCluster &findCluster)
{
    data_base.setf(ios::fixed);

    data_base << "| " << setw(2) << findCluster.getID() << " ";
    data_base << " " << setw(15) << findCluster.getName() << " ";
    data_base << " " << setw(24) << findCluster.getSize() << " ";
    data_base << " " << setw(3) << findCluster.getKnumber() << " ";
    data_base << " " << setw(9) << findCluster.getRnumber() << " ";
    data_base << " " << setw(10) << findCluster.getFieldID() << "   |" << endl;
}

void FindClusterLoader::loadFileSize(fstream &data_base)
{
    int i = 0;
    while (data_base.tellg())
        data_base.seekg(HeaderLineSize*(i++), ios::beg);
    SizeLines = i;    
}

void FindClusterLoader::saveFindCluster(FindCluster &findCluster)
{   
    fstream data_base("data_base.db", ios::binary | ios::app | ios::out | ios::in);

    printHeaderLineInFile(data_base);
    printParametersInFindClusterFile(data_base, findCluster);

    data_base.close();
}

void FindClusterLoader::loadFindCluster(FindCluster &findCluster, int findClusterID, int FieldID)
{
    fstream data_base("data_base.db", ios::binary | ios::in | ios::out | ios::app);
    if (!isFalseIndex(findClusterID))
    {
        printf("Index out of range\n");
        return;
    }

    loadFileSize(data_base);
    SeekAndSetAllID(findCluster, findClusterID, FieldID, data_base);
    loadName(findCluster, data_base);
    loadSize(findCluster, data_base);
    loadKnumber(findCluster, data_base);
    loadRnumber(findCluster, data_base);

    data_base.close();  
}

FieldLoader &Loader::getFieldLoader()
{
    return fieldLoader;
}

FindClusterLoader &Loader::getFindClusterLoader()
{
    return findClusterLoader;
}

ClusterLoader &Loader::getClusterLoader()
{
    return clusterLoader;
}
