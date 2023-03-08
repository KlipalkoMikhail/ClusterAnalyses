#ifndef INTERFACE_H
#define INTERFACE_H
#include "controller.h"
#include <iostream>
#include <string>
#include "cloud_parameters.h"
using namespace std;

class Interface
{
    public:
    Cloud_parameters cloud_parameters;
    ofstream logfile_interface;
    Controller controller;

    Interface();
    int Starts();
    void request_is_help_string(string &message);
    void request_is_create_string(string &message);
    void request_is_print_cloud(string &message);
    void request_is_print_field(string &message);
    void request_is_print_factors(string &message);
    void request_is_print_center(string &message);
    void request_is_dbscan_string(string &message);
    void request_is_kmeans_string(string &message);
    void request_is_expmax_string(string &message);
    void request_is_wave_string(string &message);
    void request_is_calculate_factors(string &message);
    void request_is_calculate_center(string &message);
    void request_is_find_cluster(string &message);
    void request_is_buffer_copy(string &message);
    void request_is_buffer_past(string &message);
    void request_is_buffer_move(string &message);
    void request_is_buffer_rotate(string &message);
    void request_is_buffer_print(string &message);
    void request_is_spanning_tree(string &message);
    void request_is_save_data(string &message);
    void request_is_load_data(string &message);
    void request_is_exit_string(string &message);
    
    void print_logs(const string &LOG_MESSAGE);
    ~Interface();

};

#endif
