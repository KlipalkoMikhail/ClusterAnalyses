#ifndef SAVE_BD_H
#define SAVE_BD_H
#include "field.h"
#include "Find_Cluster.h"

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
        void loadFindCluster(FindCluster &findCluster, int findClusterID, int FieldID);
        void saveFindCluster(FindCluster &findCluster);
};

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


class ClusterLoader
{
    private:
        int ClusterFileSizeLine;
    public:
    /*
        void loadFieldSize(Field &field, fstream &data_base);
        void loadCenter(Field &field, fstream &data_base);
        void loadEigenVectors(Field &field, fstream &data_base);
        void loadPointsFile(Field &field, fstream &data_base);
        void setFlags(Field &field, int index);
    */
};

class Loader
{
    private:
        FieldLoader fieldLoader;
        FindClusterLoader findClusterLoader;
        ClusterLoader clusterLoader;
    public:
        FieldLoader &getFieldLoader();
        FindClusterLoader &getFindClusterLoader();
        ClusterLoader &getClusterLoader();
};

#endif