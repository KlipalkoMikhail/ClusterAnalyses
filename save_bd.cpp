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
    string HEADER_LINE = settings.getHEADER_LINE();
    int HEADER_LINE_SIZE = settings.getHEADER_LINE_SIZE();

    getline(data_base, ReadedLine);
    if (data_base.eof())
        data_base.clear();

    if (!data_base.tellp() && ReadedLine != HEADER_LINE)
    {
        data_base.seekp(0, ios::beg);
        data_base << HEADER_LINE;
    }

    data_base.clear();
    data_base.seekg(HEADER_LINE_SIZE, ios::beg);
}

void FieldLoader::printParametersInFieldFile(Field &field, fstream &data_base)
{
    string block;

    block = to_string(field.ID);
    settings.makeLine(block, settings.getIDblock_width());
    data_base << block;
    block = to_string(field.size());
    settings.makeLine(block, settings.getNblock_width());
    data_base << block;
    block = to_string(field.center.getx());
    settings.makeLine(block, settings.getCXblock_width());
    data_base << block;
    block = to_string(field.center.gety());
    settings.makeLine(block, settings.getCYblock_width());
    data_base << block;
    block = to_string(field.factors[2]) + " " + to_string(field.factors[3]);
    settings.makeLine(block, settings.getEV1block_width());
    data_base << block;
    block = to_string(field.factors[4]) + " " + to_string(field.factors[5]);
    settings.makeLine(block, settings.getEV2block_width());
    data_base << block;
    block = to_string(field.factors[6]) + " " + to_string(field.factors[7]);
    settings.makeLine(block, settings.getEVblock_width());
    data_base << block;
    block = "MyPoint_" + to_string(field.ID) + ".txt";
    settings.makeLine(block, settings.getPFblock_width());
    data_base << block << endl;
}

void FieldLoader::saveField(Field &field)
{
    fstream CardField("CardField.db", ios::binary | ios::app | ios::in | ios::out);

    field.PrintPointsInFile();
    printHeaderLineFieldFile(CardField);
    printParametersInFieldFile(field, CardField);

    CardField.close();
}

void FieldLoader::loadSize(Field &field, fstream &data_base)
{
    int size = 0;
    data_base >> size;
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
    cout << filename << endl;
}

void FieldLoader::setFlags(Field &field, int index)
{
    const int STATE = 1;
    field.ID = index;
    field.set_state_work(STATE);
    //cout << "IS EXEC: " << field.is_executed() << endl;
}

void FieldLoader::loadID(Field &field, fstream &data_base)
{
    int fID;
    int FieldID = field.ID;
    int Index_Line = 1;
    int HeaderLineSize = settings.getHEADER_LINE_SIZE();
    
    data_base.seekg(HeaderLineSize, ios::beg);
    data_base >> fID;

    while (fID != FieldID && !data_base.eof())
    {
        data_base.seekg(HeaderLineSize*(1 + Index_Line), ios::beg);
        data_base >> fID;
        if (data_base.fail())
            cout << "bad" << endl;
        Index_Line++;       
    }
}

void printFieldParam(Field &field)
{
    //vector <Point> &points = field.get_points_reference();
    cout << "param " << endl;
    cout << "FID = " << field.ID << endl;
    cout << "CENTER = " << field.center.getx() << " " << field.center.gety() << endl;
    //for (int i = 0; i < field.size(); i++)
     //   cout << setw(14) << points[i].getx() << " " << points[i].gety() << endl;
    cout << field.ID << endl;
}

void FieldLoader::loadField(Field &field, int id)
{
    fstream CardField("CardField.db", ios::binary | ios::in);
    if (!CardField.is_open())
    {
        cout << "File is not existed\n";
        throw MyException("file is not existed");
    }
    loadFileSize(CardField);

    if (id > SizeLines - 1)
    {
        cout << "Wrong ID" << endl;
        throw MyException("Field with this ID is not existed");
    }

    setFlags(field, id);
    loadID(field, CardField);
    loadSize(field, CardField);
    loadCenter(field, CardField);
    loadEigenVectors(field, CardField);    
    loadPointsFile(field, CardField);
    //printFieldParam(field);
    CardField.close();  
}

void FieldLoader::loadFileSize(fstream & data_base)
{
    char testAlpha;
    int HeaderLineSize = settings.getHEADER_LINE_SIZE();
    cout << HeaderLineSize << endl;
    int lineSize = 1;
    while (!data_base.eof())
    {
        data_base.seekg(HeaderLineSize*lineSize, ios::beg);
        data_base >> testAlpha;
        if (data_base.fail()) break;
        lineSize++;
    }
    SizeLines = lineSize;
    data_base.clear();
}

void FindClusterLoader::printHeaderLineInFile(fstream &data_base)
{
    string ReadedLine;
    string HEADER_LINE = settings.getHEADER_LINE();

    getline(data_base, ReadedLine);
    if (data_base.eof())
        data_base.clear();

    if (!data_base.tellp() && ReadedLine != HEADER_LINE)
    {
        data_base.seekp(0, ios::beg);
        data_base << HEADER_LINE;
    }
    data_base.clear();
}

void check_next(fstream &data_base)
{
    char c;
    while (!data_base.eof())
    {
        data_base >> c;
        cout << c;
    }
}

void FindClusterLoader::SeekAndSetAllID(FindCluster &findCluster, int ID, int FID, fstream &data_base)
{
    int fieldID = 0;
    int findClusterID = 0;
    int Index_Line = 1;
    int HeaderLineSize = settings.getHEADER_LINE_SIZE();
    int FIDblock_width = settings.getFIDblock_width();
    int IDblock_width = settings.getIDblock_width();

    data_base.clear();
    for (int i = 1; i < SizeLines; i++)
    {
        data_base.seekg(HeaderLineSize * Index_Line, ios::beg);
        data_base >> fieldID;
        //check_next(data_base);
        data_base >> findClusterID;
        if (fieldID != FID) 
        {
            Index_Line++;
            continue;
        }
        else if (findClusterID != ID)
        {
            Index_Line++;
            continue;
        }
        else break;
        //check_next(data_base);
    }
    if (data_base.eof())
    {
        cout << "findClusterID is wrong";
        throw MyException("findClusterID is wrong");
    }
    findCluster.setID(findClusterID);
    findCluster.setFieldID(fieldID);
    data_base.seekg(HeaderLineSize*Index_Line + IDblock_width + FIDblock_width, ios::beg);
}

void FindClusterLoader::loadName(FindCluster &findCluster, fstream &data_base)
{
    string name;

    data_base >> name;
    //cout << name << endl;
    findCluster.setName(name);
}

void FindClusterLoader::loadSize(FindCluster &findCluster, fstream &data_base)
{
    int size = 0;
    data_base >> size;
    //cout << size << endl;
    if (data_base.fail())
        cout << "bad size" << endl;
    findCluster.setSize(size);
}

void FindClusterLoader::loadKnumber(FindCluster &findCluster, fstream &data_base)
{
    int Knumber = 0;
    data_base >> Knumber;
    //cout << Knumber << endl;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    findCluster.setKnumber(Knumber);
}

void FindClusterLoader::loadRnumber(FindCluster &findCluster, fstream &data_base)
{
    double Rnumber = 0;
    data_base >> Rnumber;
    //cout << Rnumber << endl;
    if (data_base.fail())
        cout << "bad" << endl;
    findCluster.setRnumber(Rnumber);
}

void FindClusterLoader::printParametersInFindClusterFile(fstream &data_base, FindCluster &findCluster)
{
    string block;

    block = to_string(findCluster.getFieldID());
    settings.makeLine(block, settings.getFIDblock_width());
    data_base << block;
    block = to_string(findCluster.getID());
    settings.makeLine(block, settings.getIDblock_width());
    data_base << block;
    block = findCluster.getName();
    settings.makeLine(block, settings.getNMblock_width());
    data_base << block;
    block = to_string(findCluster.getSize());
    settings.makeLine(block, settings.getNblock_width());
    data_base << block;
    block = to_string(findCluster.getKnumber());
    settings.makeLine(block, settings.getKblock_width());
    data_base << block;
    block = to_string(findCluster.getRnumber());
    settings.makeLine(block, settings.getRblock_width());
    data_base << block << endl;
}

void FindClusterLoader::loadFileSize(fstream &data_base)
{
    int i = 0;
    string s;

    while (!data_base.eof())
    {
        getline(data_base, s);
        i++;
    }
    data_base.clear();
    SizeLines = i - 1;
}

void FindClusterLoader::saveFindCluster(FindCluster &findCluster)
{   
    fstream data_base("CardFindCluster.db", ios::binary | ios::app | ios::out | ios::in);

    printHeaderLineInFile(data_base);
    printParametersInFindClusterFile(data_base, findCluster);

    data_base.close();
}

void FindClusterLoader::loadFindCluster(FindCluster &findCluster, int findClusterID, int FieldID)
{
    fstream data_base("CardFindCluster.db", ios::binary | ios::in);
    if (!data_base.is_open())
    {
        cerr << "CardFindCluster is not existed!\n";
        throw MyException("FindClusters are not saved");
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

void ClusterLoader::printParametersInClusterFile(fstream &data_base, FindCluster &findCluster)
{
    string block;
    Cluster cluster;
    vector <Cluster> &findedClusters = findCluster.getFindedClusters();
    int ClustersSize = findCluster.getSize();

    for(int i = 0; i < ClustersSize; i++)
    {
        cluster = findedClusters[i];
        block = to_string(cluster.getFCID());
        settings.makeLine(block, settings.getFCIDblock_width());
        data_base << block;
        block = to_string(cluster.getID());
        settings.makeLine(block, settings.getIDblock_width());
        data_base << block;
        block = to_string(cluster.getSize());
        settings.makeLine(block, settings.getNblock_width());
        data_base << block;
        block = to_string(cluster.getCenter().getx());
        settings.makeLine(block, settings.getCXblock_width());
        data_base << block;
        block = to_string(cluster.getCenter().gety());
        settings.makeLine(block, settings.getCYblock_width());
        data_base << block;
        block = "ClusterPoints_" + to_string(cluster.getFCID()) + "_" + to_string(cluster.getID()) + ".txt";
        settings.makeLine(block, settings.getPFblock_width());
        data_base << block << endl;
    }
}

void ClusterLoader::loadFileSize(fstream &data_base)
{
    int i = 0;
    string s;

    while (!data_base.eof())
    {
        getline(data_base, s);
        i++;
    }
    data_base.clear();
    SizeLines = i - 1;
}

void ClusterLoader::printHeaderLineInFile(fstream &data_base)
{
    string ReadedLine;
    string HEADER_LINE = settings.getHEADER_LINE();

    getline(data_base, ReadedLine);
    if (data_base.eof())
        data_base.clear();

    if (!data_base.tellp() && ReadedLine != HEADER_LINE)
    {
        data_base.seekp(0, ios::beg);
        data_base << HEADER_LINE;
    }
    data_base.clear();
}

void ClusterLoader::saveClusters(FindCluster &findCluster)
{   
    fstream data_base("CardClusters.db", ios::binary | ios::app | ios::out | ios::in);

    printHeaderLineInFile(data_base);
    printParametersInClusterFile(data_base, findCluster);

    data_base.close();
}

void ClusterLoader::loadClusters(FindCluster &findCluster)
{
    fstream data_base("CardClusters.db", ios::binary | ios::in);
    vector <Cluster> &findedClusters = findCluster.getFindedClusters();
    
    loadFileSize(data_base);
    SeekAndSetAllID(findCluster, data_base);

    for (int i = 0; i < findCluster.getSize(); i++)
    {
        loadFCID(findedClusters[i], data_base);
        loadID(findedClusters[i], data_base);
        loadSize(findedClusters[i], data_base);
        loadCenter(findedClusters[i], data_base);
        loadPointsFile(findedClusters[i], data_base);
    }

    data_base.close();  
}

void ClusterLoader::loadID(Cluster &findedCluster, fstream &data_base)
{
    int ID = 0;
    data_base >> ID;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    findedCluster.setID(ID);
}

void ClusterLoader::loadSize(Cluster &findedCluster, fstream &data_base)
{
    int Size = 0;
    data_base >> Size;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    findedCluster.setSize(Size);
    findedCluster.reserve(Size);
}

void ClusterLoader::loadCenter(Cluster &findedCluster, fstream &data_base)
{
    Point center;
    double CX = 0;
    double CY = 0;

    data_base >> CX >> CY;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    center.setx(CX);
    center.sety(CY);
    findedCluster.setCenter(center);
}

void ClusterLoader::loadPointsFile(Cluster &findedCluster, fstream &data_base)
{
    ifstream fin;
    string filename;
    int OrderIndex;

    data_base >> filename;
    cout << filename << endl;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    int savePos = data_base.tellp();
    data_base.close();
    fin.open(filename, ios::in | ios::binary);
    if (!fin.is_open())
    {
        cerr << filename << " is not existed!\n";
        return;
    }
    while(!fin.eof())
    {
        fin >> OrderIndex;
        findedCluster.add_p(OrderIndex);
    }
    fin.clear();
    fin.close();
    data_base.open("CardClusters.db", ios::binary | ios::in | ios::out | ios::app);
    data_base.seekp(savePos, ios::beg);
}

void ClusterLoader::loadFCID(Cluster &findedCluster, fstream &data_base)
{
    int FCID = 0;
    data_base >> FCID;
    if (data_base.fail())
        cout << "bad knumber" << endl;
    findedCluster.setFCID(FCID);
}

void ClusterLoader::SeekAndSetAllID(FindCluster &findCluster, fstream &data_base)
{
    int FCID = findCluster.getID();
    int findClusterID = 0;
    int Index_Line = 1;
    int HeaderLineSize = settings.getHEADER_LINE_SIZE();

    data_base.clear();
    for (int i = 1; i < SizeLines; i++)
    {
        data_base.seekg(HeaderLineSize * Index_Line, ios::beg);
        data_base >> findClusterID;
        if (findClusterID != FCID) 
        {
            Index_Line++;
            continue;
        }
        else break;
    }
    if (data_base.eof())
    {
        cout << "findClusterID is wrong";
        throw MyException("findClusterID is wrong");
    }
    data_base.seekg(HeaderLineSize*Index_Line, ios::beg);
}

void FCLSettings::makeLine(string &name, int width)
{
    int nameSize = name.size();
    int spacesWidth = (width - nameSize)/2;
    for (int i = 0; i < spacesWidth; i++)
        name = " " + name + " ";
    if (2*spacesWidth + nameSize != width)
        name = name + " ";
    //cout  << name;
}

void FCLSettings::makeHeaderLine()
{
    HEADER_LINE = FIDblock + IDblock + NMblock + Nblock + Kblock + Rblock + "\n";
    HEADER_LINE_SIZE = HEADER_LINE.size();
}

string FCLSettings::getHEADER_LINE()
{
    return HEADER_LINE;
}

int FCLSettings::getHEADER_LINE_SIZE()
{
    return HEADER_LINE_SIZE;
}

int FCLSettings::getIDblock_width()
{
    return IDblock_width;
}

int FCLSettings::getNMblock_width()
{
    return NMblock_width;
}

int FCLSettings::getNblock_width()
{
    return Nblock_width;
}

int FCLSettings::getKblock_width()
{
    return Kblock_width;
}

int FCLSettings::getRblock_width()
{
    return Rblock_width;
}

int FCLSettings::getFIDblock_width()
{
    return FIDblock_width;
}

void CLSettings::makeLine(string &name, int width)
{
    int nameSize = name.size();
    int spacesWidth = (width - nameSize)/2;
    for (int i = 0; i < spacesWidth; i++)
        name = " " + name + " ";
    if (2*spacesWidth + nameSize != width)
        name = name + " ";
    //cout  << name;
}

void CLSettings::makeHeaderLine()
{
    HEADER_LINE = FCIDblock + IDblock + Nblock + CXblock + CYblock + PFblock + "\n";
    HEADER_LINE_SIZE = HEADER_LINE.size();
}

string CLSettings::getHEADER_LINE()
{
    return HEADER_LINE;
}

int CLSettings::getHEADER_LINE_SIZE()
{
    return HEADER_LINE_SIZE;
}

int CLSettings::getIDblock_width()
{
    return IDblock_width;
}

int CLSettings::getNblock_width()
{
    return Nblock_width;
}

int CLSettings::getCXblock_width()
{
    return CXblock_width;
}

int CLSettings::getCYblock_width()
{
    return CYblock_width;
}

int CLSettings::getPFblock_width()
{
    return PFblock_width;
}

int CLSettings::getFCIDblock_width()
{
    return FCIDblock_width;
}

void FLSettings::makeLine(string &name, int width)
{
    int nameSize = name.size();
    int spacesWidth = (width - nameSize)/2;
    for (int i = 0; i < spacesWidth; i++)
        name = " " + name + " ";
    if (2*spacesWidth + nameSize != width)
        name = name + " ";
    //cout  << name;
}

void FLSettings::makeHeaderLine()
{
    HEADER_LINE = IDblock + Nblock + CXblock + CYblock + EV1block + EV2block + EVblock + PFblock + "\n";
    HEADER_LINE_SIZE = HEADER_LINE.size();
}

string FLSettings::getHEADER_LINE()
{
    return HEADER_LINE;
}

int FLSettings::getHEADER_LINE_SIZE()
{
    return HEADER_LINE_SIZE;
}

int FLSettings::getIDblock_width()
{
    return IDblock_width;
}

int FLSettings::getNblock_width()
{
    return Nblock_width;
}

int FLSettings::getCXblock_width()
{
    return CXblock_width;
}

int FLSettings::getCYblock_width()
{
    return CYblock_width;
}

int FLSettings::getPFblock_width()
{
    return PFblock_width;
}

int FLSettings::getEV1block_width()
{
    return EV1block_width;
}

int FLSettings::getEV2block_width()
{
    return EV2block_width;
}

int FLSettings::getEVblock_width()
{
    return EVblock_width;
}