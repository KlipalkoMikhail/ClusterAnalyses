#include "headers.h"
#include <iostream>
#include <fstream>
#include <cfloat>
#include <random>
#include <iomanip>
#include "controller.h"
#include <iterator>
#include "factors.h"
#include "exec.h"
#include <list>
#include <cmath>
#define EPSILON 0.000001

double distance(const Point &x, const Point &y)
{
    return sqrt((x.getx() - y.getx())*(x.getx()- y.getx()) + (x.gety() - y.gety())*(x.gety() - y.gety()));
}

Controller::Controller()
{
    Status_Work = 1;
    fields_size = 0;
}

Controller::~Controller()
{
    logfile_controller.close();
}

void Controller::print_logs(const string &LOG_MESSAGE)
{
    if(LOG_MESSAGE.size())
        return;
    
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << LOG_MESSAGE << endl;
    logfile_controller.close();
}

void Controller::k_means(int k, Field &field)
{
    sv.save(exec.kmeans.k_means(k, field), 1);

    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "KMEANS with" << k << endl;
    logfile_controller.close();
    
    Status_Work = 2;
}

void Controller::dbscan(int m , double r, Field &field)
{
    sv.save(exec.dbscan.dbscan(m, r, field), 3);
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "DBSCAN " << m << " " << r << " success" << endl;
    logfile_controller.close();
    Status_Work = 2;
}

void Controller::wave(double mode, Field &field)
{
    sv.save(exec.wave.wave(mode, field), 2);
    //logfile_controller << "WAVE " << mode << " success" << endl;
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "WAVE " << mode << " success" << endl;
    logfile_controller.close();
    Status_Work = 2;
}

void Controller::exp_max(int k, Field &field)
{
    exec.em.turn_EM(k, field);
    sv.save((exec.em.get_storage()).clusters, 4);

    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "EXPMAX " << k << " success" << endl;
    logfile_controller.close();
    Status_Work = 2;
}


void Controller::print_field(Field &field)
{
    cout.setf(ios::left | ios::fixed | ios::showpos);
    // проверяем на состояние и печатаем, если поле создано
    if (!field.is_executed())
    {
        cout << "Field is not created\n" << endl;
        return;
    }
    else
    {
        cout << " X " << "\t\t\t" << " Y " << endl;
        for (int i = 0; i < field.size(); i++)
        {
            cout << field.getx_p(i) << "\t\t";
            cout << field.gety_p(i) << endl;
        }
    }

    // сохраняем поле в файл
    field.file_save();

    // сохраняем результаты в лог-файл контроллера
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "Field created PRFIELD " << endl;
    logfile_controller.close();
}

void Controller::create_cloud(Cloud_parameters cloud_parameters)
{
    if (cloud_parameters.field_index > fields_size)
    {
        cout << "Put the index that lower then " << fields_size << endl;
        return;
    }
    
    if (Status_Work == 2)
    {
        cout << "You have done some of algorithm. Add more cloud is not allowed!" << endl;
        return;
    }
    
    if (!fields[cloud_parameters.field_index].is_executed())
        fields_size++;

    fields[cloud_parameters.field_index].state_gen(cloud_parameters);
    fields[cloud_parameters.field_index].ID = cloud_parameters.field_index;

    std::cout << "Cloud has been created with parameters: ";
    cloud_parameters.print_parameters(cout);
}


// Распечатка облака, входные параметры - номер облака
void Controller::print_cloud(int i, Field &field)
{
    // объявление файла, имени файла
    ofstream fout;
    char filename[120];
    Cloud cloud = field.get_copy_cloud(i);

    // создаем имя для файла
    sprintf(filename, "cloud_%d.dat", i);

    // открываем файл
    fout.open(filename);

    // иницилизируем точки облака, points - точки облака
    vector <Point> points = cloud.get_points();

    // печатаем в файл точки
    for (int j = 0; j < (int)points.size(); j++)
                fout << points[j].getx() << "\t\t" << points[j].gety() << endl;
    
    // закрываем файл
    fout.close();

    // проверяем на состояние создания облака и печатаем его на экран в случае наличия с точностью до шести знаков
    if (cloud.work() != 1)
    {
        cout << "Cloud is not created\n" << endl;
        return;
    }
    else
    {
        cout << " X " << "\t\t\t" << " Y " << endl;

        for (int k = 0; k < (int)points.size(); k++)
        {
            cout << fixed << setprecision(6) << points[k].getx() << "\t\t";
            cout << fixed << setprecision(6) << points[k].gety() << "\t\t" << "\t Col " << points[k].getNP() << endl;
        }
    }

    // результаты отработки в лог-файл контроллера
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "Cloud printed PRCLOUD " << endl;
    logfile_controller.close();
}

void Controller::find_cluster(int k, Field &field)
{
    vector <Point> points = field.p();
    sv.cluster_save(k, field.size(), points);

    int n = sv.get_k_code(k);

    cout << "Check the folder. The result are saved." << endl;
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "Saved result RESULT " << k << endl;
    cout << "Saved result RESULT " << k << endl;
    if (n == 1) 
    {
        logfile_controller << "It is K means algorithm\n" << "It was done as " << k << "th algorithm\n";
        cout << "It is K means algorithm\n" << "It was done as " << k << "th algorithm\n";
    }
    if (n == 2)
    {
        logfile_controller << "It is Wave algorithm\n" << "It was done as " << k << "th algorithm\n";
        cout << "It is Wave algorithm\n" << "It was done as " << k << "th algorithm\n";
    }
    if (n == 3)
    { 
        logfile_controller << "It is DBscan algorithm\n" << "It was done as " << k << "th algorithm\n";
        cout << "It is DBscan algorithm\n" << "It was done as " << k << "th algorithm\n";
    }
    if (n == 4) 
    {
        logfile_controller << "It is EXPMAX algorithm\n" << "It was done as " << k << "th algorithm\n";
        cout << "It is EXPMAX algorithm\n" << "It was done as " << k << "th algorithm\n";
    }
    if (n == 5) 
    {
        logfile_controller << "It is SPANTREE algorithm\n" << "It was done as " << k << "th algorithm\n";
        cout << "It is SPANTREE algorithm\n" << "It was done as " << k << "th algorithm\n";
    }
    logfile_controller << "This algrotihm found " << (sv.get_clusters(k)).size() << " clusters" << endl;
    cout << "This algrotihm found " << (sv.get_clusters(k)).size() << " clusters" << endl;
    logfile_controller.close();
}

void Controller::print_clouds(Field &field)
{
    vector <Cloud> clouds = *(field.get_cl());

    int k = field.nclouds();
    cout << k << endl;

    ofstream *fout = new ofstream[k];

    for (int i = 0; i < k; i++)
    {
        char filename[120];
        sprintf(filename, "%d.dat", i + 1);
        fout[i].open(filename);
        vector <Point> points = clouds[k].get_points();
        for (int j = 0; j < clouds[k].size(); j++)
                fout[i] << points[j].getx() << "\t\t" << points[j].gety() << endl;
    }
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "Clouds printed PRCLOUD " << endl;
    logfile_controller.close();
}

void Controller::calculate_factor(int k, Field &field)
{
    vector <Point> arr;
    if (k == 0)
    {
        arr = field.p();
        field.factors = exec.factors.calculate_factors(arr);
    }
    if (k == 1)
    {
        for (int i = 0; i < field.nclouds(); i++)
            (field.get_cloud(i)).factors = exec.factors.calculate_factors((field.get_cloud(i)).get_points());
    }
    if (k == 2)
    {
        int s;
        cout << "Enter the result index ";
        cin >> s;
        vector <Point> arr = field.p();
        vector <Cluster> & clusters = sv.get_clusters(s);
        int n = clusters.size();
        vector <vector <Point>> cluster_points(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < field.size(); j++)
                {
                    if (clusters[i].tr(j))
                        cluster_points[i].push_back(arr[j]);
                }
            clusters[i].factors = exec.factors.calculate_factors(cluster_points[i]);
        }
    }
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "Factors calculated CALFACT " << k << endl;
    logfile_controller.close();
}

void Controller::print_factors(int m, Field &field)
{
    if (m == 1)
    {
        vector <Cloud> cloud(field.nclouds());
        for (int j = 0 ; j < field.nclouds(); j++)
        {
            Cloud & cld = field.get_cloud(j);
            cloud[j].factors = cld.factors;
        }
        ofstream cloudo;
        cloudo.open("cloud_factors.dat");
        for (int i = 0; i < field.nclouds(); i++)
        {
            cloudo << "set arrow 1 from " << cloud[i].factors[0] << " to " << cloud[i].factors[1] << endl;
            cloudo << "set arrow 1 from " << cloud[i].factors[0] + cloud[i].factors[2] << "\t" << cloud[i].factors[1] + cloud[i].factors[3] << endl;
            cloudo << endl;
            cloudo << "set arrow 1 from " << cloud[i].factors[0] << "\t" << cloud[i].factors[1] << endl;
            cloudo << "set arrow 1 from " << cloud[i].factors[0] + cloud[i].factors[4] << "\t" << cloud[i].factors[1] + cloud[i].factors[5] << endl;
            cloudo << endl;
        }
        cloudo.close();
    }
    if (m == 2)
    {
        cout << "Enter the result code ";
        int k;
        cin >> k;
        vector <Cluster> clusters = sv.get_clusters(k);
        ofstream fout;
        cout << "fout " << endl;
        char filename[120];
        sprintf(filename, "gnu_%d.dat", k);
        fout.open(filename, ios::app);

        for (int i = 0; i < (int)clusters.size(); i++)
        {
            fout << "set arrow " << i + 1 << " from " << clusters[i].factors[0] << " , " << clusters[i].factors[1] << " to ";
            fout << clusters[i].factors[0] + clusters[i].factors[2] << " , " << clusters[i].factors[1] + clusters[i].factors[3] << " front lw 4" << endl;
            fout << "set arrow 1111" << i + 1 << " from " << clusters[i].factors[0] << " , " << clusters[i].factors[1] << " to ";
            fout << clusters[i].factors[0] + clusters[i].factors[4] << " , " << clusters[i].factors[1] + clusters[i].factors[5] << " front lw 4" << endl; 
        }
        fout << "load \"field_factors.dat\" " << endl;
        cout << "fout close " << endl;

        fout.close();
    }
    else
    {
        ofstream fieldo;
        fieldo.open("field_factors.dat");
        fieldo << "set arrow 1000 from " << field.factors[0] << " , " << field.factors[1] << " to ";
        fieldo << field.factors[0] + field.factors[2] << " , " << field.factors[1] + field.factors[3] << " front lw 4" << endl;
        fieldo << "set arrow 1001 from " << field.factors[0] << " , " << field.factors[1] << " to ";
        fieldo << field.factors[0] + field.factors[4] << " , " << field.factors[1] + field.factors[5] << " front lw 4" << endl;
        fieldo.close();
    }
    cout << "It is done" << endl;
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "Factors printed PRFACT " << endl;
    logfile_controller.close();
}

void Controller::span_tree(Field &field)
{
    exec.spanning_tree.span_the_tree(field);
    Status_Work = 2;
    logfile_controller.open("logfile_controller.txt", ios::app);
    logfile_controller << "Span tree SPANTREE " << endl;
    logfile_controller.close();
}

void Controller::save_data_base(Field &field)
{
    data_base.save_bd(field, field.ID, config);
}

void Controller::load_data_base(Field &field, int index)
{
    data_base.load_db(field, index, config);
}

void Controller::calculate_center(Field &field)
{
    double sum_x = 0;
    double sum_y = 0;
    int field_size = field.size();
    vector <Point> points = field.get_points_reference();
    for (int i = 0; i < field_size; i++)
    {
        //cout << points[i].getx() << '\t' << points[i].gety() << endl;
        sum_x += points[i].getx();
        sum_y += points[i].gety();
    }
    sum_x = sum_x / field_size;
    sum_y = sum_y / field_size;
    field.center.setx(sum_x);
    field.center.sety(sum_y);
}

void Controller::print_center(Field &field)
{
    cout.setf(ios::left | ios::showpos);
    cout << "Center is (" << setprecision(6) << field.center.getx() << " " << field.center.gety() << ")" << endl;
}