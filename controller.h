#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "field.h"
#include "Logger.h"
#include "saves.h"
#include "buffer.h"
#include "exec.h"
#include "save_bd.h"
#include "config.h"
#include "cloud_parameters.h"

class Controller
{
    int Status_Work;
    public:
        Buffer buffer;
        Exec exec;
        vector <Field> fields;
        Saves sv;
        Loader DataBaseLoader;
        Config config;
        Logger logger;
        int fields_size;

        Controller();
        void print_field(Field &field);
        void k_means(int k, Field &field);
        void create_cloud(CloudParameters cloud_parameters);
        void saveInFileFindCluster(Field &field, int launchIndex);
        void wave(double mode, Field &field);
        void dbscan(int m, double r, Field &field);
        void print_factors(int k, Field &field);
        void print_cloud(int k, Field &field);
        void print_clouds(Field &field);
        void print_center(Field &field);
        void exp_max(int k, Field &field);
        void calculate_factor(int k, Field &field);
        void calculate_center(Field &field);
        void span_tree(Field &field);
        void saveField(Field &field);
        void loadField(int id);
        void saveFindCluster(int FID, int FCID);
        void loadFindCluster(int fieldID, int findClusterID);
        void printActiveFields();
        Field & getFieldByFID(int FID);
        ~Controller();
};

#endif

