#ifndef SAVE_BD_H
#define SAVE_BD_H
#include "field.h"
#include "Find_Cluster.h"

class FLSettings
{
    private:
        string IDblock = "ID";
        string Nblock = "N";
        string NFCblock = "NFC";
        string CXblock = "CX";
        string CYblock = "CY";
        string EV1block = "EV1";
        string EV2block = "EV2";
        string EVblock = "EV";
        string PFblock = "PF";
        string HEADER_LINE;
        int HEADER_LINE_SIZE;
        int IDblock_width;
        int Nblock_width;
        int NFCblock_width;
        int CXblock_width;
        int CYblock_width;
        int EV1block_width;
        int EV2block_width;
        int EVblock_width;
        int PFblock_width;

        void makeHeaderLine();
    public:
        FLSettings()
        {
            IDblock_width = 5;
            Nblock_width = 9;
            NFCblock_width = 9;
            CXblock_width = 17;
            CYblock_width = 17;
            EV1block_width = 31;
            EV2block_width = 31;
            EVblock_width = 31;
            PFblock_width = 21;

            makeLine(IDblock, IDblock_width);
            makeLine(Nblock, Nblock_width);
            makeLine(CXblock, CXblock_width);
            makeLine(CYblock, CYblock_width);
            makeLine(EV1block, EV1block_width);
            makeLine(EV2block, EV2block_width);
            makeLine(EVblock, EV1block_width);
            makeLine(PFblock, PFblock_width);
            makeLine(NFCblock, NFCblock_width);
            makeHeaderLine();
        }
        void makeLine(string &name, int width);
        string getHEADER_LINE();
        int getHEADER_LINE_SIZE();
        int getIDblock_width();
        int getPFblock_width();
        int getNblock_width();
        int getNFCblock_width();
        int getCXblock_width();
        int getCYblock_width();
        int getEV1block_width();
        int getEV2block_width();
        int getEVblock_width();
};
class FCLSettings
{
    private:
        string FIDblock = "FID";
        string IDblock = "ID";
        string NMblock = "Name";
        string Nblock = "N";
        string Kblock = "K";
        string Rblock = "R";
        string HEADER_LINE;
        int HEADER_LINE_SIZE;
        int IDblock_width;
        int NMblock_width;
        int Nblock_width;
        int Kblock_width;
        int Rblock_width;
        int FIDblock_width;

        void makeHeaderLine();
    public:
        FCLSettings()
        {
            IDblock_width = 7;
            NMblock_width = 14;
            Nblock_width = 5;
            Kblock_width = 5;
            Rblock_width = 15;
            FIDblock_width = 7;
            makeLine(IDblock, IDblock_width);
            makeLine(NMblock, NMblock_width);
            makeLine(Nblock, Nblock_width);
            makeLine(Kblock, Kblock_width);
            makeLine(Rblock, Rblock_width);
            makeLine(FIDblock, FIDblock_width);
            makeHeaderLine();
        }
        void makeLine(string &name, int width);
        string getHEADER_LINE();
        int getHEADER_LINE_SIZE();
        int getIDblock_width();
        int getNMblock_width();
        int getNblock_width();
        int getKblock_width();
        int getRblock_width();
        int getFIDblock_width();
};

class FindClusterLoader
{
    private:
        FCLSettings settings;
        int SizeLines;
    public:
        FindClusterLoader()
        {
            SizeLines = 0;
        }
        void loadFileSize(fstream &data_base);
        void loadName(FindCluster &findCluster, fstream &data_base);
        void loadKnumber(FindCluster &findCluster, fstream &data_base);
        void loadRnumber(FindCluster &findCluster, fstream &data_base);
        void loadSize(FindCluster &findCluster, fstream &data_base);
        void SeekAndSetAllID(FindCluster &findCluster, int FindClusterID, int FieldID, fstream &data_base);
        void printParametersInFindClusterFile(fstream &data_base, FindCluster &findCluster);
        void printHeaderLineInFile(fstream &data_base);
        void loadFindCluster(FindCluster &findCluster, int findClusterID, int FieldID);
        void saveFindCluster(FindCluster &findCluster);
};

class FieldLoader
{
    private:
        FLSettings settings;
        int rowSize;
    public:
        FieldLoader(){rowSize = 0;}
        void printRowSize(fstream & data_base);
        void printParametersInFieldFile(Field &field, fstream &data_base);
        void printHeaderLineFieldFile(fstream &data_base);
        void resetKeysAndSaveRowSize(Field &field);
        void readRowSizeFromFile();
        void loadFileSize(fstream &data_base);
        void loadID(Field &field, int ID, fstream &data_base);
        void loadSize(Field &field, fstream &data_base);
        void loadNFC(Field &field, fstream & data_base);
        void loadCenter(Field &field, fstream &data_base);
        void loadEigenVectors(Field &field, fstream &data_base);
        void loadPointsFile(Field &field, fstream &data_base);
        void setFlags(Field &field, int index);
        void loadField(Field &field, int id); 
        void saveField(Field &field);
};

class CLSettings
{
    private:
        string FIDblock = "FID";
        string FCIDblock = "FCID";
        string IDblock = "ID";
        string Nblock = "N";
        string CXblock = "CX";
        string CYblock = "CY";
        string PFblock = "PF";
        string HEADER_LINE;
        int HEADER_LINE_SIZE;
        int FIDblock_width;
        int IDblock_width;
        int Nblock_width;
        int CXblock_width;
        int CYblock_width;
        int FCIDblock_width;
        int PFblock_width;

        void makeHeaderLine();
    public:
        CLSettings()
        {
            FIDblock_width = 7;
            IDblock_width = 7;
            Nblock_width = 7;
            CXblock_width = 15;
            CYblock_width = 15;
            PFblock_width = 29;
            FCIDblock_width = 7;

            makeLine(FIDblock, FIDblock_width);
            makeLine(IDblock, IDblock_width);
            makeLine(Nblock, Nblock_width);
            makeLine(CXblock, CXblock_width);
            makeLine(CYblock, CYblock_width);
            makeLine(PFblock, PFblock_width);
            makeLine(FCIDblock, FCIDblock_width);
            makeHeaderLine();
        }
        void makeLine(string &name, int width);
        string getHEADER_LINE();
        int getHEADER_LINE_SIZE();
        int getIDblock_width();
        int getPFblock_width();
        int getNblock_width();
        int getCXblock_width();
        int getCYblock_width();
        int getFCIDblock_width();
        int getFIDblock_width();
};

class ClusterLoader
{
    private:
        CLSettings settings;
        int SizeLines;
    public:
        void printParametersInClusterFile(fstream &data_base, FindCluster &findCluster);
        void loadFID(FindCluster & findCluster, fstream &data_base);
        void SeekAndSetAllID(FindCluster &findCluster, fstream &data_base);
        void printHeaderLineInFile(fstream &data_base);
        void loadFileSize(fstream &data_base);
        void loadID(Cluster &findedCluster, fstream &data_base);
        void loadSize(Cluster &findedCluster, fstream &data_base);
        void loadCenter(Cluster &findedCluster, fstream &data_base);
        void loadPointsFile(Cluster &findedCluster, fstream &data_base);
        void loadFCID(Cluster &findedCluster, fstream &data_base);
        void loadClusters(FindCluster &findCluster); 
        void saveClusters(FindCluster &findCluster);
        //void SeekAndSetAllID(FindCluster &findCluster, int FindClusterID, int FieldID, fstream &data_base);
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