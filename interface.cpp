#include "headers.h"
#include <iostream>
#include <string>
#include "interface.h"
#include "controller.h"
#include "save_bd.h"
#include "config.h"

void Interface::request_is_help_string()
{
    string line;
    fstream fout("HELP.txt");
    string message = "Requested help";

    if (fout.is_open())
    {
        while (!fout.eof())
        {
            getline(fout, line);
            cout << line << endl;
        }
        logger.info(message);
    }
    else
    {
        cout << "It seems the file HELP.TXT is not existed\n";
        logger.error(message);
    }
}

void Interface::request_is_create_string()
{
    CloudParameters parameters;
    cout << "To add cloud enter FID, N, x, y, gx, gy\n";
    parameters.load_index(cin);
    parameters.load_size(cin);
    parameters.load_center(cin);
    parameters.load_dispersion(cin);

    string message = "Requested create cloud with parameters " + to_string(parameters.size) + " " +   
                                                                to_string(parameters.center_x) + " " + 
                                                                to_string(parameters.center_y) + " " +
                                                                to_string(parameters.dispersion_x) + " " + 
                                                                to_string(parameters.dispersion_y) + " " +
                                                                to_string(parameters.field_index);
    
    logger.info(message);
    controller.create_cloud(parameters);
}

void Interface::request_is_print_active_fields()
{
    controller.printActiveFields();
    string message = "Requested print active fields";
    
    logger.info(message);
}

void Interface::request_is_print_cloud()
{
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter cloud index (starts with 0)\n";
    cin >> cloud_index;
    cout << "Cloud index = " << cloud_index << endl;

    string message = "Requested print cloud with parameters " + to_string(field_index) + " " + to_string(cloud_index);
    logger.info(message);
    controller.print_cloud(cloud_index, controller.fields[field_index]);
}

void Interface::request_is_print_field()
{
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested print field with parameters " + to_string(field_index);
    logger.info(message);
    controller.print_field(controller.fields[field_index]);
}

void Interface::request_is_wave_string()
{
    int field_index = 0;
    double mode = 1;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter wave mode (starts with 0)\n";
    cin >> mode;
    cout << "Wave mode = " << mode << endl;

    string message = "Requested wave algorithm with parameters " + to_string(field_index) + " " + to_string(mode);
    logger.info(message);
    controller.wave(mode, controller.fields[field_index]);
}

void Interface::request_is_dbscan_string()
{
    double step = 1;
    int neighbors_number = 1;
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter number of neighbors\n";
    cin >> neighbors_number;
    cout << "Neighbors number = " << neighbors_number << endl;
    cout << "Enter step\n";
    cin >> step;
    cout << "Step = " << step << endl;

    string message = "Requested dbscan algorithm with parameters " + to_string(field_index) + " " + to_string(neighbors_number) + " " + to_string(step);
    logger.info(message);
    controller.dbscan(neighbors_number, step, controller.fields[field_index]);
}

void Interface::request_is_kmeans_string()
{
    int cluster_number = 3;
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter number of clusters\n";
    cin >> cluster_number;
    cout << "Cluster number = " << cluster_number << endl;

    string message = "Requested k-means algorithm with parameters " + to_string(field_index) + " " + to_string(cluster_number);
    logger.info(message);
    controller.k_means(cluster_number, controller.fields[field_index]);
}

void Interface::request_is_expmax_string()
{
    int field_index = 0;
    int cluster_number = 3;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter number of clusters\n";
    cin >> cluster_number;
    cout << "Cluster number = " << cluster_number << endl;


    string message = "Requested expectation–maximization algorithm with parameters " + to_string(field_index) + " " + to_string(cluster_number);
    logger.info(message);
    controller.exp_max(cluster_number, controller.fields[field_index]);
}

void Interface::request_is_print_factors()
{
    int field_index = 0;
    int code = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter code of object (0 - Field, 1 - Cloud, 2 - Cluster)\n";
    cin >> code;
    cout << "Code = " << code << endl;

    string message = "Requested print factors with parameters " + to_string(field_index) + " " + to_string(code);
    logger.info(message);
    controller.print_factors(code, controller.fields[field_index]);
}

void Interface::request_is_calculate_factors()
{
    int field_index = 0;
    int code = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter code of object (0 - Field, 1 - Cloud, 2 - Cluster)\n";
    cin >> code;
    cout << "Code = " << code << endl;

    string message = "Requested calculate factors with parameters " + to_string(field_index) + " " + to_string(code);
    logger.info(message);
    controller.calculate_factor(code, controller.fields[field_index]);
}

void Interface::request_is_calculate_center()
{
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested calculate center with parameters " + to_string(field_index);
    logger.info(message);
    controller.calculate_center(controller.fields[field_index]);
}

void Interface::request_is_find_cluster()
{
    int field_index = 0;
    int algorithm_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter algorithm index (starts with 0)\n";
    cin >> algorithm_index;
    cout << "Algorithm index = " << algorithm_index << endl;

    string message = "Requested find cluster with parameters " + to_string(field_index) + " " + to_string(algorithm_index);
    logger.info(message);
    controller.saveInFileFindCluster(controller.fields[field_index], algorithm_index);
}

void Interface::request_is_print_launches()
{
    controller.print_launches();
}

void Interface::request_is_print_center()
{
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested print center with parameters " + to_string(field_index);
    logger.info(message);
    controller.print_center(controller.fields[field_index]);
}

void Interface::request_is_buffer_copy()
{
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter cloud index (starts with 0)\n";
    cin >> cloud_index;
    cout << "Cloud index = " << cloud_index << endl;

    string message = "Requested buffer copy with parameters " + to_string(field_index) + " " + to_string(cloud_index);
    logger.info(message);
    controller.buffer.copy(controller.fields[field_index].getCloudReference(cloud_index));
}

void Interface::request_is_buffer_past()
{
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested buffer past with parameters " + to_string(field_index);
    logger.info(message);
    controller.buffer.past(controller.fields[field_index]);
}

void Interface::request_is_buffer_move()
{
    double x = 1, y = 1;
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter cloud index (starts with 0)\n";
    cin >> cloud_index;
    cout << "Cloud index = " << cloud_index << endl;
    cout << "Enter center: x and y (starts with 0)\n";
    cin >> x >> y;
    cout << "x = " <<  x << " y = " << y << endl;

    string message = "Requested buffer move with parameters " + to_string(field_index) + " " + to_string(cloud_index) + " " + to_string(x) + " " + to_string(y);
    logger.info(message);
    controller.buffer.shift(controller.fields[field_index].getCloudReference(cloud_index), x, y);
}

void Interface::request_is_buffer_rotate()
{
    double angle = 1;
    int field_index = 0;
    int cloud_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter cloud index (starts with 0)\n";
    cin >> cloud_index;
    cout << "Cloud index = " << cloud_index << endl;
    cout << "Enter angle in radians (starts with 0)\n";
    cin >> angle;
    cout << "Angle = " << angle << endl;

    string message = "Requested buffer rotate with parameters " + to_string(field_index) + " " + to_string(cloud_index) + " " + to_string(angle);
    logger.info(message);
    controller.buffer.rotate(controller.fields[field_index].getCloudReference(cloud_index), angle);
}

void Interface::request_is_buffer_print()
{
    string message = "Requested buffer print";
    controller.buffer.print();
}

void Interface::request_is_spanning_tree()
{
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested spanning tree algorithm with parameters " + to_string(field_index);
    logger.info(message);
    controller.span_tree(controller.fields[field_index]);
}

void Interface::request_is_save_field()
{
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested save field with parameters " + to_string(field_index);
    logger.info(message);
    controller.saveField(controller.fields[field_index]);
}

void Interface::request_is_load_field()
{
    int field_index = 0;

    cout << "Enter field index in fields data base (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested load field with parameters " + to_string(field_index);
    logger.info(message);
    controller.loadField(field_index);
}

void Interface::request_is_load_find_cluster()
{
    int field_index = 0;
    int findcluster_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter findcluster index (starts with 0)\n";
    cin >> findcluster_index;
    cout << "findcluster index = " << findcluster_index << endl;

    string message = "Requested load find cluster with parameters " + to_string(field_index) + " " + to_string(findcluster_index);
    logger.info(message);
    controller.loadFindCluster(field_index, findcluster_index);
}

void Interface::request_is_save_find_cluster()
{
    int field_index = 0;
    int findClusterIndex = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;
    cout << "Enter findcluster index (starts with 0)\n";
    cin >> findClusterIndex;
    cout << "findcluster index = " << findClusterIndex << endl;

    string message = "Requested save find cluster with parameters " + to_string(field_index) + " " + to_string(findClusterIndex);
    logger.info(message);
    controller.saveFindCluster(field_index, findClusterIndex);
}

void Interface::request_is_turn_hier()
{
    int field_index = 0;

    cout << "Enter field index (starts with 0)\n";
    cin >> field_index;
    cout << "Field index = " << field_index << endl;

    string message = "Requested turn hierarhical algorithm with parameters " + to_string(field_index);
    logger.info(message);
    controller.hierarchical(field_index);
}

void Interface::request_is_exit_string()
{
    string message = "Requested exit";
    logger.info(message);
}

Interface::Interface()
{
    logger.basicConfig("logfile_interface.txt");
}

Interface::~Interface(){}

int Interface::Starts()
{
    Commands commands = settings.getCommands();
    string request;

    cin >> request;
    if (request == commands.HELP)
        request_is_help_string();
    else if (request == commands.CLOUD_CREATE)
        request_is_create_string();
    else if (request == commands.CLOUD_PRINT)
        request_is_print_cloud();
    else if (request == commands.FIELD_PRINT)
        request_is_print_field();
    else if (request == commands.WAVE)
        request_is_wave_string();
    else if (request == commands.DBSCAN)
        request_is_dbscan_string();
    else if (request == commands.K_MEANS)
        request_is_kmeans_string();
    else if (request == commands.EXP_MAX)
        request_is_expmax_string();
    else if (request == commands.FACT_PRINT)
        request_is_print_factors();
    else if (request == commands.FACT_CALC)
        request_is_calculate_factors();
    else if (request == commands.CENT_CALC)
        request_is_calculate_center();
    else if (request == commands.RESULT)
        request_is_find_cluster();
    else if (request == commands.CENT_PRINT)
        request_is_print_center();
    else if (request == commands.COPY_BUFF)
        request_is_buffer_copy();
    else if (request == commands.PAST_BUFF)
        request_is_buffer_past();
    else if (request == commands.MOVE_BUFF)
        request_is_buffer_move();
    else if (request == commands.ROTATE_BUFF)
        request_is_buffer_rotate();
    else if (request == commands.PRINT_BUFF)
        request_is_buffer_print();
    else if (request == commands.SPAN_TREE)
        request_is_spanning_tree();
    else if (request == commands.SAVE_FIELD)
        request_is_save_field();
    else if (request == commands.LOAD_FIELD)
        request_is_load_field();
    else if (request == commands.SAVE_FINDC)
        request_is_save_find_cluster();
    else if (request == commands.LOAD_FINDC)
        request_is_load_find_cluster();
    else if (request == commands.PRINT_ACTIVE_FIELDS)
        request_is_print_active_fields();
    else if (request == commands.PRINT_LAUNCHES)
        request_is_print_launches();
    else if (request == commands.turn_hier)
        request_is_turn_hier();
    else if (request == commands.EXIT)
    {
        request_is_exit_string();
        return 0;
    } 
    else {
        cout << "Request is |" << request << "|" << endl;
        cout << "Unknown command. Try again!\n";
        return -1;
    }

    return 1;
}
