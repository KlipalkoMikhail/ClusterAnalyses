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
    string CLOUD_CREATE = "create_cloud";
    string CLOUD_PRINT = "print_cloud";
    string FIELD_PRINT = "print_field";
    string WAVE = "turn_wave";
    string DBSCAN = "turn_dbscan";
    string K_MEANS = "turn_kmeans";
    string EXP_MAX = "turn_expmax";
    string FACT_PRINT = "print_factors";
    string FACT_CALC = "find_factors";
    string CENT_CALC = "find_center";
    string RESULT = "print_result";
    string CENT_PRINT = "print_center";
    string COPY_BUFF = "copy_buffer";
    string PAST_BUFF = "past_buffer";
    string MOVE_BUFF = "move_buffer";
    string ROTATE_BUFF = "rotate_buffer";
    string PRINT_BUFF = "print_buffer";
    string SPAN_TREE = "turn_spantree";
    string SAVE_FIELD = "save_field";
    string LOAD_FIELD = "load_field";
    string SAVE_FINDC = "save_find_cluster";
    string LOAD_FINDC = "load_find_cluster";
    string EXIT = "exit";
    string HELP = "help";
    string PRINT_ACTIVE_FIELDS = "print_active_fields";
    string PRINT_LAUNCHES = "print_launches";
    string turn_hier = "turn_hier";
    string regression = "regression";
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
        void request_is_turn_hier();
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
        void request_is_print_launches();
        void request_is_regression();
        ~Interface();

};

#endif
