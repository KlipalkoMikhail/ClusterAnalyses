#ifndef INTERFACE_H
#define INTERFACE_H
#include "controller.h"
#include <iostream>
#include <string>
#include "cloud_parameters.h"
#include "Logger.h"
using namespace std;

class Commands
{
public:
    string CLOUD_CREATE = "CRCLOUD";
    string CLOUD_PRINT = "PRCLOUD";
    string FIELD_PRINT = "PRFIELD";
    string WAVE = "WAVE";
    string DBSCAN = "DBSCAN";
    string K_MEANS = "KMEANS";
    string EXP_MAX = "EXPMAX";
    string FACT_PRINT = "PRFACT";
    string FACT_CALC = "CALFACT";
    string CENT_CALC = "CALCEN";
    string RESULT = "RESULT";
    string CENT_PRINT = "PRCEN";
    string COPY_BUFF = "BUFFCPY";
    string PAST_BUFF = "BUFFPST";
    string MOVE_BUFF = "BUFFMOV";
    string ROTATE_BUFF = "BUFFROT";
    string PRINT_BUFF = "BUFFPRC";
    string SPAN_TREE = "SPANTRE";
    string SAVE_FIELD = "SAVE_FIELD";
    string LOAD_FIELD = "LOAD_FIELD";
    string SAVE_FINDC = "SAVE_FINDC";
    string LOAD_FINDC = "LOAD_FINDC";
    string EXIT = "EXIT";
    string HELP = "HELP";
    string PRINT_ACTIVE_FIELDS = "PRINT_ACTIVE_FIELDS";
};

class InterfaceSettings
{
    private:
        CloudParameters cloudParameters;
        Commands commands;
    public:
        CloudParameters getCloudParameters()
        {
            return cloudParameters;
        }
        Commands getCommands()
        {
            return commands;
        }
};

class Interface
{
    private:
        InterfaceSettings settings;
        Logger logger;
        Controller controller;

    public:
        Interface();
        int Starts();
        void request_is_help_string();
        void request_is_create_string();
        void request_is_print_cloud();
        void request_is_print_field();
        void request_is_print_factors();
        void request_is_print_center();
        void request_is_dbscan_string();
        void request_is_kmeans_string();
        void request_is_expmax_string();
        void request_is_wave_string();
        void request_is_calculate_factors();
        void request_is_calculate_center();
        void request_is_find_cluster();
        void request_is_buffer_copy();
        void request_is_buffer_past();
        void request_is_buffer_move();
        void request_is_buffer_rotate();
        void request_is_buffer_print();
        void request_is_spanning_tree();
        void request_is_save_field();
        void request_is_load_field();
        void request_is_load_find_cluster();
        void request_is_save_find_cluster();
        void request_is_exit_string();
        void request_is_print_active_fields();
        ~Interface();

};

#endif
