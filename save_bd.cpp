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

class FieldLoader
{
    private:
        string PREHEADER_LINE;
        string HEADER_LINE;
        int HeaderLineSize;
        int SizeLines;
    public:
        FieldLoader()
        {
            string PREHEADER_LINE = "__________________________________________________________________________________________________________________________________\n";
            string HEADER_LINE =    "| ID    Size       Center_x        Center_y         Eigen_vec_1         Eigen_vec_2           Eigen_value        Points_file     |\n";
            HeaderLineSize = HEADER_LINE.size();
            SizeLines = 0;
        }
        void printParametersInFieldFile(Field &field, fstream &data_base);
        void printHeaderLineFieldFile(fstream &data_base);
        void loadSize(Field &field, fstream &data_base);
        void loadCenter(Field &field, fstream &data_base);
        void loadEigenVectors(Field &field, fstream &data_base);
        void loadPointsFile(Field &field, fstream &data_base);
        void setFlags(Field &field, int index);
        void loadField(Field &field, int id); 
        void saveField(Field &field);
};

void FieldLoader::printHeaderLineFieldFile(fstream &data_base)
{
    string ReadedLine;

    data_base.getline(ReadedLine, HeaderLineSize);
    if (ReadedLine != PREHEADER_LINE)
    {
        data_base.seekp(0, ios::beg);
        data_base.write(PREHEADER_LINE, HeaderLineSize);
        data_base.write(HEADER_LINE, HeaderLineSize);
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
    data_base << "  " << setw(15) << "MyPoint_" << id << ".txt" << "  |" << endl;
}

void FieldLoader::saveField(Field &field)
{
    fstream CardField("CardField.db", ios::binary | ios::app | ios::out);

    printHeaderLineFieldFile(CardField);
    printParametersInFieldFile(CardField, field);

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
    field.setState(STATE);
    //cout << "IS EXEC: " << field.is_executed() << endl;
}

void FieldLoader::loadField(Field &field, int id)
{
    fstream CardField("CardField.db", ios::binary | ios::in);
    
    loadSize(field, CardField);
    loadSenter(field, CardField);
    loadEigenVectors(field, CardField);    
    loadPointsFile(field, CardField);
    setFlags(field, id);

    CardField.close();  
}

class FindClusterLoader
{
    private:
        string PREHEADER_LINE;
        string HEADER_LINE;
        int HeaderLineSize;
        int SizeLines;
    public:
        FindClusterLoader()
        {
            PREHEADER_LINE = "_________________________________________________________________________________\n";
            HEADER_LINE =    "| ID         Name          Number of Clusters       K       R       ID_FIELD    |\n";
            HeaderLineSize = PREHEADER_LINE.size();
            SizeLines = 0;
        }
        void loadFileSize(fstream &data_base);
        void loadName(FindCluster &findCluster, fstream &data_base);
        void loadKnumber(FindCluster &findCluster, fstream &data_base);
        void loadRnumber(FindCluster &findCluster, fstream &data_base);
        void loadSize(FindCluster &findCluster, fstream &data_base);
        void SeekAndSetAllID(FindCluster &findCluster, int FindClusterID, int FieldID, fstream &data_base);
        void printParametersInFindClusterFile(fstream &data_base, FindCluster &findCluster)
        void isFalseIndex(int FindClusterID);
        void printHeaderLineInFile(fstream &data_base);
};

void FindClusterLoader::printHeaderLineInFile(fstream &data_base)
{
    string ReadedLine;

    data_base.getline(ReadedLine, HeaderLineSize);
    if (ReadedLine != PREHEADER_LINE)
    {
        data_base.seekp(0, ios::beg);
        data_base.write(PREHEADER_LINE, HeaderLineSize);
        data_base.write(HEADER_LINE, HeaderLineSize);
    }
    data_base.seekg(2*HeaderLineSize + 1, ios::beg);
}

void FindClusterLoader::isFalseIndex(int FindClusterID)
{
    if (FindClusterID >= SizeLines)
    {
        cout << "Index out of range\n";
        return;
    }
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
    findCluster.name = name;
}

void FindClusterLoader::loadSize(FindCluster &findCluster, fstream &data_base)
{
    int size = 0;
    data_base >> size;
    if (data_base.fail())
        cout << "bad size" << endl;
    findCluster.size = size;
}

void FindClusterLoader::loadKnumber(FindCluster &findCluster, fstream &data_base)
{
    int Knumber = 0;
    data_base >> Knumber;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    findCluster.Knumber = Knumber;
}

void FindClusterLoader::loadRnumber(FindCluster &findCluster, fstream &data_base)
{
    double Rnumber = 0;
    data_base >> Rnumber;
    if (data_base.fail())
        cout << "bad" << endl;
    findCluster.Rnumber = Rnumber;
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

void FindClusterLoader::SaveFindCluster(FindCluster &findCluster)
{   
    fstream data_base("data_base.db", ios::binary | ios::app | ios::out | ios::in);

    SeekAndSetAllID();
    printHeaderLineFindCluster(data_base);
    printParametersInFindClusterFile(data_base);

    data_base.close();
}

void FindClusterLoader::LoadFindCluster(FindCluster &findCluster, int findClusterID, int FieldID)
{
    ifstream data_base("data_base.db", ios::binary | ios::in);
    if (!isFalseIndex(findClusterID))
    {
        printf("Index out of range\n");
        return;
    }
    SeekAnd
    S(field, data_base);
    load_center(field, data_base);
    load_eigen_vector(field, data_base);    
    load_points_file(field, data_base);
    set_executed_flags(field, id);
    data_base.close();  
}

class ClusterLoader
{
    private:
        int ClusterFileSizeLine;
    public:
        void loadFieldSize(Field &field, fstream &data_base);
        void loadCenter(Field &field, fstream &data_base);
        void loadEigenVectors(Field &field, fstream &data_base);
        void loadPointsFile(Field &field, fstream &data_base);
        void setFlags(Field &field, int index);
};

class Loader
{
    private:
        FieldLoader fieldLoader;
        FindClusterLoader findClusterLoader;
        ClusterLoader clusterLoader;
    public:
        FieldLoader getFieldLoader();
        FindClusterLoader getFindClusterLoader();
        ClusterLoader getClusterLoader();
};

class Saver
{
    private:
    public:
        void printParametersInFieldFile(fstream &data_base, Field &field);
        void printHeaderLineFieldFile(fstream &data_base);
        void printHeaderLineFindCluster(fstream &data_base);
        void printParametersInFindClusterFile(fstream &data_base, FindClusterParameters parameters);
        void SaveField(Field &field);
        void SaveFindCluster(FindClusterParameters parameters);
        
};
