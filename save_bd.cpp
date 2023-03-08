#include <bits/stdc++.h>
#include "headers.h"
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
        void loadSize(Field &field, fstream &data_base);
        void loadCenter(Field &field, fstream &data_base);
        void loadEigenVectors(Field &field, fstream &data_base);
        void loadPointsFile(Field &field, fstream &data_base);
        void setFlags(Field &field, int index);
};

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

void FieldLoader::LoadFindCluster(int id)
{
    ifstream data_base("data_base.db", ios::binary | ios::in);
    data_base.seekg(132*(id + 2) + 4,  ios::beg);
    
    load(field, data_base);
    load_center(field, data_base);
    load_eigen_vector(field, data_base);    
    load_points_file(field, data_base);
    set_executed_flags(field, id);
    data_base.close();  
}

class FindClusterLoader
{
    private:
        int size;
    public:
        void loadName(FindCluster findCluster, fstream &data_base);
        void loadK(FindCluster findCluster, fstream &data_base);
        void loadR(FindCluster findCluster, fstream &data_base);
        void loadSize(FindCluster findCluster, fstream &data_base);
        void loadPointsFile(FindCluster findCluster, fstream &data_base);
        void setFlags(FindCluster findCluster, int index);
};

class ClusterLoader
{
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
        int ClusterFileSizeLine;
    public:
        FieldLoader getFieldLoader()
        FindClusterLoader getFindClusterLoader()
        ClusterLoader getClusterLoader()
        void loadFieldSize(Field &field, fstream &data_base);
        void loadCenter(Field &field, fstream &data_base);
        void loadEigenVectors(Field &field, fstream &data_base);
        void loadPointsFile(Field &field, fstream &data_base);
        void setFlags(Field &field, int index);
};

void Loader::loadFieldSize(Field &field, fstream &data_base)
{
    const string HEADER_LINE =    "| ID    Size       Center_x        Center_y         Eigen_vec_1         Eigen_vec_2           Eigen_value        Points_file     |\n";
    int HeaderLineSize = HEADER_LINE.size();
    data_base.seekg(HeaderLineSize*(field.ID + 2) + 4);
    int size = 0;
    data_base >> size;
    //cout << size << endl;
    if (data_base.fail())
        cout << "bad" << endl;
    field.setSize(size);
}

void Loader::loadCenter(Field &field, fstream &data_base)
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

void Loader::loadEigenVectors(Field &field, fstream &data_base)
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

void Loader::loadPointsFile(Field &field, fstream &data_base)
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

void Loader::setFlags(Field &field, int index)
{
    const int STATE = 1;
    field.ID = index;
    field.setState(STATE);
    //cout << "IS EXEC: " << field.is_executed() << endl;
}

void Loader::loadField(Field &field, int id)
{
    fstream CardField("CardField.db", ios::binary | ios::in);
    
    loadSize(field, CardField);
    loadSenter(field, CardField);
    loadEigenVectors(field, CardField);    
    loadPointsFile(field, CardField);
    setFlags(field, id);

    CardField.close();  
}

void Loader::LoadFindCluster(int id)
{
    ifstream data_base("data_base.db", ios::binary | ios::in);
    data_base.seekg(132*(id + 2) + 4,  ios::beg);
    
    load(field, data_base);
    load_center(field, data_base);
    load_eigen_vector(field, data_base);    
    load_points_file(field, data_base);
    set_executed_flags(field, id);
    data_base.close();  
}

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

void Saver::printHeaderLineFieldFile(fstream &data_base)
{
    const string PREHEADER_LINE = "__________________________________________________________________________________________________________________________________\n";
    const string HEADER_LINE =    "| ID    Size       Center_x        Center_y         Eigen_vec_1         Eigen_vec_2           Eigen_value        Points_file     |\n";
    int HeaderLineSize = PREHEADER_LINE.size();
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

void Saver::printParametersInFieldFile(fstream &data_base, Field &field)
{
    const string HEADER_LINE =    "| ID    Size       Center_x        Center_y         Eigen_vec_1         Eigen_vec_2           Eigen_value        Points_file     |\n";
    int HeaderLineSize = PREHEADER_LINE.size();
    
    data_base.seekg(HeaderLineSize*field.ID, ios::beg);
    data_base.setf(ios::fixed);

    data_base << "| " << setw(2) << field.ID << " ";
    data_base << " " << setw(8) << field.size() << " ";
    data_base << " " << setw(12) << setprecision(4) << showpos << field.center.getx() << " ";
    data_base << " " << setw(12) << setprecision(4) << showpos << field.center.gety() << " ";
    data_base << "    " << setw(8) << setprecision(2) << showpos << field.factors[2] << " " << setw(8) << setprecision(2) << showpos << field.factors[3] << "   ";
    data_base << " " << setw(8) << setprecision(2) << showpos << field.factors[4] << " " << setw(8) << setprecision(2) << showpos << field.factors[5] << "   ";
    data_base << "  " << setw(8) << setprecision(2) << showpos << field.factors[6] << " " << setw(8) << setprecision(2) << showpos << field.factors[7] << "   ";
    data_base << "  " << setw(15) << config.common_file_of_points(id) << "  |" << endl;
}

void Saver::SaveField(Field &field)
{
    fstream CardField("CardField.db", ios::binary | ios::app | ios::out);

    printHeaderLineFieldFile(CardField);
    printParametersInFieldFile(CardField, field);

    CardField.close();
}

class FindClusterParameters
{
    public:
        int ID;
        string name;
        int NumberOfClusters;
        int K;
        double R;
        int FieldID;   
};

void Saver::printHeaderLineFindCluster(fstream &data_base)
{
    const string PREHEADER_LINE = "________________________________________________________________________________\n";
    const string HEADER_LINE =    "| ID       Name           Number of Clusters       K       R       ID_FIELD    |\n";
    int HeaderLineSize = PREHEADER_LINE.size();
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

void Saver::printParametersInFindClusterFile(fstream &data_base, FindClusterParameters parameters)
{
    data_base.setf(ios::fixed);

    data_base << "| " << setw(2) << parameters.ID << " ";
    data_base << " " << setw(15) << parameters.name << " ";
    data_base << " " << setw(24) << parameters.NumberOfClusters << " ";
    data_base << " " << setw(3) << parameters.K << " ";
    data_base << " " << setw(9) << parameters.R << " ";
    data_base << " " << setw(10) << parameters.FieldID << "   |" << endl;
}

void Saver::SaveFindCluster(FindClusterParameters parameters)
{   
    fstream data_base("data_base.db", ios::binary | ios::app | ios::out | ios::in);

    printHeaderLineFindCluster(data_base);
    printParametersInFindClusterFile(data_base);

    data_base.close();
}

