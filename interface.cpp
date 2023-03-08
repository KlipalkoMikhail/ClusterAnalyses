#include "headers.h"
#include <iostream>
#include <string>
#include "interface.h"
#include "controller.h"
#include "save_bd.h"
#include "config.h"

void Interface::request_is_help_string(string &message)
{
    string line;
    fstream fout("HELP.txt");
    message = "HELP";

    if (fout.is_open())
    {
        while (!fout.eof())
        {
            getline(fout, line);
            cout << line << endl;
        }
    }
    else
        cout << "It seems the file HELP.TXT is not existed\n";
}

void Interface::request_is_create_string(string &message)
{
    cout << "Enter the field index to add there a cloud and N, x, y, gx, gy: ";
    cloud_parameters.load_index(cin);
    cloud_parameters.load_size(cin);
    cloud_parameters.load_center(cin);
    cloud_parameters.load_dispersion(cin);

    message = "CRCLOUD" + to_string(cloud_parameters.size) +  
                        to_string(cloud_parameters.center_x) + 
                        to_string(cloud_parameters.center_y) +
                        to_string(cloud_parameters.dispersion_x) + 
                        to_string(cloud_parameters.dispersion_y) +
                        to_string(cloud_parameters.field_index);

    controller.create_cloud(cloud_parameters);
}

void Interface::request_is_print_cloud(string &message)
{
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter cloud index (starts with 0): ";
    cin >> cloud_index;

    message = "PRCLOUD" + to_string(field_index) + to_string(cloud_index);
    controller.print_cloud(cloud_index, controller.fields[field_index]);
}

void Interface::request_is_print_field(string &message)
{
    int field_index = 0;
    message = "PRFIELD";

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Let's print the field..." << endl;

    controller.print_field(controller.fields[field_index]);
}

void Interface::request_is_wave_string(string &message)
{
    int field_index = 0;
    double mode = 1;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter wave mode (starts with 0): ";
    cin >> mode;
    message = "WAVE" + to_string(field_index) + to_string(mode);

    controller.wave(mode, controller.fields[field_index]);
}

void Interface::request_is_dbscan_string(string &message)
{
    double step = 1;
    int neighbors_number = 1;
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter number of neighbors: ";
    cin >> neighbors_number;
    cout << "Enter step: ";
    cin >> step;

    message = "DBSCAN" + to_string(neighbors_number) + to_string(step);
    controller.dbscan(neighbors_number, step, controller.fields[field_index]);
}

void Interface::request_is_kmeans_string(string &message)
{
    int cluster_number = 3;
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter number of clusters: ";
    cin >> cluster_number;

    message = "KMEANS" + to_string(cluster_number);
    controller.k_means(cluster_number, controller.fields[field_index]);
}

void Interface::request_is_expmax_string(string &message)
{
    int field_index = 0;
    int cluster_number = 3;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter number of clusters: ";
    cin >> cluster_number;

    message = "EXPMAX" + to_string(field_index) + to_string(cluster_number);
    controller.exp_max(cluster_number, controller.fields[field_index]);
}

void Interface::request_is_print_factors(string &message)
{
    int field_index = 0;
    int code = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter code of object (0 - Field, 1 - Cloud, 2 - Cluster): ";
    cin >> code;

    message = "PRFACT" + to_string(field_index) + to_string(code);
    controller.print_factors(code, controller.fields[field_index]);
}

void Interface::request_is_calculate_factors(string &message)
{
    int field_index = 0;
    int code = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter code of object (0 - Field, 1 - Cloud, 2 - Cluster): ";
    cin >> code;

    message = "CALFACT" + to_string(field_index) + to_string(code);
    controller.calculate_factor(code, controller.fields[field_index]);
}

void Interface::request_is_calculate_center(string &message)
{
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;

    message = "CALCEN" + to_string(field_index);
    controller.calculate_center(controller.fields[field_index]);
}

void Interface::request_is_find_cluster(string &message)
{
    int field_index = 0;
    int algorithm_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter algorithm index (starts with 0): ";
    cin >> algorithm_index;

    message = "RESULT" + to_string(field_index) + to_string(algorithm_index);
    controller.find_cluster(algorithm_index, controller.fields[field_index]);
}

void Interface::request_is_print_center(string &message)
{
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;

    cout << "The printed center: ";
    message = "PRCEN" + to_string(field_index);
    controller.print_center(controller.fields[field_index]);
}

void Interface::request_is_buffer_copy(string &message)
{
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter cloud index (starts with 0): ";
    cin >> cloud_index;

    message = "BUFFCPY" + to_string(field_index) + to_string(cloud_index);
    controller.buffer.copy(controller.fields[field_index].get_cloud(cloud_index));
}

void Interface::request_is_buffer_past(string &message)
{
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;

    message = "BUFFPST" + to_string(field_index);
    controller.buffer.past(controller.fields[field_index]);
}

void Interface::request_is_buffer_move(string &message)
{
    double x = 1, y = 1;
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter cloud index (starts with 0): ";
    cin >> cloud_index;
    cout << "Enter center: x and y (starts with 0): ";
    cin >> x >> y;

    message = "BUFFMOV" + to_string(field_index) + to_string(cloud_index) + to_string(x) + to_string(y);
    controller.buffer.shift(controller.fields[field_index].get_cloud(cloud_index), x, y);
    cout << "Shifted in " << " (" << x << " " << y << ")" << endl;
}

void Interface::request_is_buffer_rotate(string &message)
{
    double angle = 1;
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;
    cout << "Enter cloud index (starts with 0): ";
    cin >> cloud_index;
    cout << "Enter angle in radians (starts with 0): ";
    cin >> angle;

    message = "BUFFROT" + to_string(field_index) + to_string(cloud_index) + to_string(angle);
    controller.buffer.rotate(controller.fields[field_index].get_cloud(cloud_index), angle);
    cout << "Rotate on " << angle << " radians\n";
}

void Interface::request_is_buffer_print(string &message)
{
    message = "BUFFPRC";
    controller.buffer.print();
}

void Interface::request_is_spanning_tree(string &message)
{
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;

    message = "SPANTRE" + to_string(field_index);
    controller.span_tree(controller.fields[field_index]);
}

void Interface::request_is_save_data(string &message)
{
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;

    message = "SAVEDB" + to_string(field_index);
    controller.save_data_base(controller.fields[field_index]);
}

void Interface::request_is_load_data(string &message)
{
    int field_index = 0;

    cout << "Enter field index (starts with 0): ";
    cin >> field_index;

    message = "LOADDB" + to_string(field_index);
    controller.load_data_base(controller.fields[field_index], field_index);
    cout << "Data is loaded" << endl;
}

void Interface::request_is_exit_string(string &message)
{
    message = "EXIT";
}

void Interface::print_logs(const string &LOG_MESSAGE)
{
    if (LOG_MESSAGE.size())
        return;
    logfile_interface.open("logfile_interface.txt", std::ios::app);
    logfile_interface << LOG_MESSAGE << endl;
    logfile_interface.close();
}


Interface::Interface()
{
    ofstream logfile_interface;
    Field field();
}

Interface::~Interface()
{
    logfile_interface.close();
}

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
    string SAVE_DB = "SAVEDB";
    string LOAD_DB = "LOADDB";
    string EXIT = "EXIT";
    string HELP = "HELP";
};


int Interface::Starts()
{
    Commands commands;
    string request;
    string message;

    cin >> request;
    if (request == commands.HELP)
        request_is_help_string(message);
    if (request == commands.CLOUD_CREATE)
        request_is_create_string(message);
    if (request == commands.CLOUD_PRINT)
        request_is_print_cloud(message);
    if (request == commands.FIELD_PRINT)
        request_is_print_field(message);
    if (request == commands.WAVE)
        request_is_wave_string(message);
    if (request == commands.DBSCAN)
        request_is_dbscan_string(message);
    if (request == commands.K_MEANS)
        request_is_kmeans_string(message);
    if (request == commands.EXP_MAX)
        request_is_expmax_string(message);
    if (request == commands.FACT_PRINT)
        request_is_print_factors(message);
    if (request == commands.FACT_CALC)
        request_is_calculate_factors(message);
    if (request == commands.CENT_CALC)
        request_is_calculate_center(message);
    if (request == commands.RESULT)
        request_is_find_cluster(message);
    if (request == commands.CENT_PRINT)
        request_is_print_center(message);
    if (request == commands.COPY_BUFF)
        request_is_buffer_copy(message);
    if (request == commands.PAST_BUFF)
        request_is_buffer_past(message);
    if (request == commands.MOVE_BUFF)
        request_is_buffer_move(message);
    if (request == commands.ROTATE_BUFF)
        request_is_buffer_rotate(message);
    if (request == commands.PRINT_BUFF)
        request_is_buffer_print(message);
    if (request == commands.SPAN_TREE)
        request_is_spanning_tree(message);
    if (request == commands.SAVE_DB)
        request_is_save_data(message);
    if (request == commands.LOAD_DB)
        request_is_load_data(message);
    if (request == commands.EXIT)
    {
        request_is_exit_string(message);
        return 0;
    } 
    else {
        cout << "Unknown command. Try again!\n";
        return -1;
    }
    print_logs(message);
    return 1;
}
