#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "field.h"
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
        Save_BD data_base;
        Config config;
        ofstream logfile_controller;
        int fields_size;

        Controller();
        void print_field(Field &field);
        void k_means(int k, Field &field);
        void create_cloud(Cloud_parameters cloud_parameters);
        void find_cluster(int k, Field &field);
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
        void save_data_base(Field &field);
        void load_data_base(Field &field, int index);
        void print_logs(const string &LOG_MESSAGE);
        ~Controller();
};

#endif
