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
        Field fields[10];
        Saves sv;
        Loader DataBaseLoader;
        Config config;
        Logger logger;
        int fields_size;

        Controller();
        void print_field(Field &field);
        void k_means(int k, Field &field);
        void create_cloud(CloudParameters cloud_parameters);
        void saveInFileFindCluster(int launchIndex, Field &field);
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
        void print_logs(const string &LOG_MESSAGE);
        void saveField(Field &field);
        void loadField(Field &field, int id);
        void saveFindCluster(FindCluster &findCluster);
        void loadFindCluster(FindCluster &findCluster, int findClusterID, int fieldID);
        ~Controller();
};

#endif
