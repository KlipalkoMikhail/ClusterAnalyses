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

void printFieldParam(Field &field);

double distance(const Point &x, const Point &y)
{
    return sqrt((x.getx() - y.getx())*(x.getx()- y.getx()) + (x.gety() - y.gety())*(x.gety() - y.gety()));
}

void Controller::printActiveFields()
{
    for (int i = 0; i < fields_size; i++)
        if (fields[i].is_executed())
            cout << "FID=" << fields[i].getID() << " DBID=" << fields[i].getDBID() << " is active" << endl; 
}

void calculate_clusters_center(vector <Cluster> &clusters, Field &field)
{
    Point center;
    vector <Point> & points = field.get_points_reference();
    double x = 0;
    double y = 0;
    int size = 0;
    int ClusterSize = clusters.size();
    int N = field.size();

    for (int j = 0; j < ClusterSize; j++)
    {
        Cluster & cluster = clusters[j];
        for (int i = 0; i < N; i++)
        {
            if (cluster.tr(i) == 1)
            {
                x += points[i].getx();
                y += points[i].gety();
                size++;
            }
        }
        if (size != 0)
        {
            x = x/size;
            y = y/size;
        }
        else x = y = 0;

        center.setx(x);
        center.sety(y);
        cout << "Calculated centers: " << x << " " << y << endl;
        cluster.setCenter(center);
        cluster.setSize(size);
        size = 0;
        x = 0;
        y = 0;
    }
}

Controller::Controller()
{
    Status_Work = 1;
    fields_size = 0;
    logger.basicConfig("logfile_controller.txt");
}

Controller::~Controller()
{
    vector <Field> ().swap(fields);
}

void Controller::k_means(int k, Field &field)
{
    string name = "K-means";
    try{
        vector <Cluster> findedClusters = exec.kmeans.k_means(k, field);
        sv.saveFindCluster(findedClusters, field, k, 0, name);
        string message = "Kmeans is executed with parameters " + to_string(k) + " " + to_string(field.getID());
        logger.info(message);
    }
    catch(std::exception& e)
    {
        string message = "Kmeans is executed with parameters " + to_string(k) + " " + to_string(field.getID());
        std::cerr << e.what() << '\n';
        logger.error(message);
        message = e.what();
        logger.error(message);
    }
    
    Status_Work = 2;
}

void Controller::dbscan(int m , double r, Field &field)
{
    string name = "DBscan";
    try
    {
        vector <Cluster> findedClusters = exec.dbscan.dbscan(m, r, field);
        sv.saveFindCluster(findedClusters, field, m, r, name);
        string message = "dbscan is executed with parameters " + to_string(m) + " " + to_string(r) + " " + to_string(field.getID());
        logger.info(message);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
        string message = "dbscan is executed with parameters " + to_string(m) + " " + to_string(r) + " " + to_string(field.getID());
        logger.error(message);
        message = e.what();
        logger.error(message);
    }

    Status_Work = 2;
}

void Controller::wave(double mode, Field &field)
{
    string name = "Wave";
    try{
        vector <Cluster> findedClusters = exec.wave.wave(mode, field);
        sv.saveFindCluster(findedClusters, field, 0, mode, name);
        string message = "wave is executed with parameters " + to_string(mode) + " " + to_string(field.getID());
        logger.info(message);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
        string message = "wave is executed with parameters " + to_string(mode) + " " + to_string(field.getID());
        logger.error(message);
        message = e.what();
        logger.error(message);
    }
    Status_Work = 2;
}

void Controller::exp_max(int k, Field &field)
{
    string name = "EM";
    try{
        vector <Cluster> findedClusters = exec.em.turn_EM(k, field);
        sv.saveFindCluster(findedClusters, field, k, 0, name);
        cout << "tut";
        string message = "expectation–maximization algorithm is executed with parameters " + to_string(k) + " " + to_string(field.getID());
        cout << "before";
        logger.info(message);
        cout << "fag";
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
        string message = "expectation–maximization algorithm is executed with parameters " + to_string(k) + " " + to_string(field.getID());
        logger.error(message);
        message = e.what();
        logger.error(message);
    }
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
    string message = "print field is executed with parameters " + to_string(field.getID());
    logger.info(message);
}

void Controller::create_cloud(CloudParameters parameters)
{
    
    if (parameters.field_index > fields_size)
    {
        cout << "Put the index that lower then " << fields_size << endl;
        return;
    }
    else if (parameters.field_index == fields_size)
    {
        fields.resize(fields_size + 1);
        fields_size += 1;
        fields[parameters.field_index].set_state_work(1);
    }


    fields[parameters.field_index].state_gen(parameters);
    fields[parameters.field_index].setID(parameters.field_index);
    fields[parameters.field_index].setDBID(parameters.field_index);
    //fields[parameters.field_index].PrintPointsInFile();

    std::cout << "Cloud has been created with parameters: ";
    parameters.print_parameters(cout);

    string message = "Requested create cloud with parameters " + to_string(parameters.size) + " " +   
                                                                to_string(parameters.center_x) + " " + 
                                                                to_string(parameters.center_y) + " " +
                                                                to_string(parameters.dispersion_x) + " " + 
                                                                to_string(parameters.dispersion_y) + " " +
                                                                to_string(parameters.field_index);
    
    logger.info(message);
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
    string message = "print cloud is executed with parameters " + to_string(i) + " " + to_string(field.getID());
    logger.info(message);
}

void Controller::saveInFileFindCluster(Field &field, int launchIndex)
{
    FindCluster &findCluster = sv.getFindCluster(field.getID(), launchIndex);
    string name = findCluster.getName();
    int Knumber = findCluster.getKnumber();
    double Rnumber = findCluster.getRnumber();
    int size = findCluster.getSize();
    cout << size << endl;
    cout << field.getID() << ' ' << launchIndex << endl;
    cout << "get it 283" << endl;

    sv.saveResult(findCluster, field);
    cout << "catch " << endl;

    string message = "save find cluster result is executed with parameters " + to_string(launchIndex) + " " +   
                                                                               to_string(field.getID());
    logger.info(message);
    message = "find clusted result saved with parameters " + to_string(launchIndex) + " " + name + " " + to_string(Knumber) + " " + to_string(Rnumber) + " " + to_string(size) + " " + to_string(field.getID());
    logger.debug(message);
    cout << name << "done as " << launchIndex << "th algorithm with parameters k = " << Knumber << ", r = " << Rnumber << ", size = " << size << endl;
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
    string message = "print cloud is executed with parameters " + to_string(field.getID());
    logger.info(message);
}

void Controller::calculate_factor(int k, Field &field)
{
    vector <Point> &arr = field.get_points_reference();
    if (k == 0)
    {
        arr = field.get_points_reference();
        field.factors = exec.factors.calculate_factors(arr);
    }
    if (k == 1)
    {
        for (int i = 0; i < field.nclouds(); i++)
            (field.get_cloud(i)).factors = exec.factors.calculate_factors((field.get_cloud(i)).get_points());
    }
    if (k == 2)
    {
        int LaunchIndex;
        FindCluster &findCluster = sv.getFindCluster(field.getID(), LaunchIndex);
        vector <Cluster> & clusters = findCluster.getFindedClusters();
        int ClusterSize = clusters.size();
        int FieldSize = field.size();
        vector <vector <Point>> cluster_points(FieldSize);

        cout << "Enter the launch index ";
        cin >> LaunchIndex;
        for (int i = 0; i < ClusterSize; i++)
        {
            for (int j = 0; j < FieldSize; j++)
                {
                    if (clusters[i].tr(j))
                        cluster_points[i].push_back(arr[j]);
                }
            clusters[i].factors = exec.factors.calculate_factors(cluster_points[i]);
        }
    }
    string message = "calculate factors is executed with parameters " + to_string(k) + " " +   
                                                                        to_string(field.getID());
    logger.info(message);
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
        ofstream fout;
        int LaunchIndex;
        FindCluster &findCluster = sv.getFindCluster(field.getID(), LaunchIndex);
        vector <Cluster> & clusters = findCluster.getFindedClusters();
        int ClusterSize = clusters.size();

        cout << "Enter the launch index ";
        cin >> LaunchIndex;

        string filename = "gnu_" + to_string(LaunchIndex) + ".dat";
        fout.open(filename, ios::app);

        for (int i = 0; i < ClusterSize; i++)
        {
            fout << "set arrow " << i + 1 << " from " << clusters[i].factors[0] << " , " << clusters[i].factors[1] << " to ";
            fout << clusters[i].factors[0] + clusters[i].factors[2] << " , " << clusters[i].factors[1] + clusters[i].factors[3] << " front lw 4" << endl;
            fout << "set arrow 1111" << i + 1 << " from " << clusters[i].factors[0] << " , " << clusters[i].factors[1] << " to ";
            fout << clusters[i].factors[0] + clusters[i].factors[4] << " , " << clusters[i].factors[1] + clusters[i].factors[5] << " front lw 4" << endl; 
        }
        fout << "load \"field_factors.dat\" " << endl;
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
    string message = "print factors is executed with parameters " + to_string(m) + " " +   
                                                                    to_string(field.getID());
    logger.info(message);
}

void Controller::span_tree(Field &field)
{
    exec.spanning_tree.span_the_tree(field);
    //sv.saveFindCluster(findedClusters, 0, 0, "SpanningTree");
    
    Status_Work = 2;
    string message = "spanning tree is executed with parameters " + to_string(field.getID());
    logger.info(message);

}

void Controller::saveField(Field &field)
{
    FieldLoader &Loader = DataBaseLoader.getFieldLoader();
    Loader.saveField(field);
    string message = "save field is executed with parameters " + to_string(field.getID());
    logger.info(message);
}

void printFieldPa(Field & field)
{
    cout << "ID is " << field.getID() << endl;
    cout << "Size is " << field.size() << endl;
    cout << "Center is " << field.center.getx() << ' ' << field.center.gety() << endl;
    cout << "factors ";
    cout << field.factors[0] << endl;
    cout << field.factors[1] << endl;
    cout << field.factors[2] << endl
         << field.factors[3] << endl
        << field.factors[4] << endl
        << field.factors[5] << endl
        << field.factors[6] << endl
         << field.factors[7] << endl;
   //cout << "Points X\tY" << endl;
   cout << "Is executed is " << field.is_executed() << endl;
   vector <Point> & points = field.get_points_reference();

   for (int i = 0; i < field.size(); i++)
   {
       //cout << points[i].getx() << " " << points[i].gety() << endl;
   }
}

void Controller::loadField(int id)
{
    try{
        fields.resize(fields_size + 1);
        Field &field = fields[fields_size];
        field.setID(fields_size);
        fields_size++;
        FieldLoader &Loader = DataBaseLoader.getFieldLoader();
        Loader.loadField(field, id);
        //printFieldPa(field);
        string message = "load field is executed with parameters " + to_string(id);
        logger.info(message);
    }
    catch(MyException &ex)
    {
        string message = ex.getMessage();
        logger.error(message);
    }
}

void createClusterFiles(FindCluster &findCluster)
{
    string filename;
    ofstream fout;
    vector <Cluster> &findedClusters = findCluster.getFindedClusters();
    int ClustersSize = findCluster.getSize();

    for(int i = 0; i < ClustersSize; i++)
    {
        Cluster & cluster = findedClusters[i];
        filename = "ClusterPoints_" + to_string(findCluster.getDBFID()) + "_" + to_string(cluster.getFCID()) + "_" + to_string(cluster.getID()) + ".txt";
        fout.open(filename, ios::out | ios::binary);
        for (int j = 0; j < cluster.getFieldSize(); j++)
        {
            if (cluster.tr(j) == 1)
                fout << j << " ";
        }
        fout.close();
    }
}

Field & Controller::getFieldByFID(int DBFID)
{
    //cout << FID << ' ' << fields_size << endl;
    int checkedID = -1;
    for (int i = 0; i < fields_size; i++)
    {
        int DataBaseFieldIndex = fields[i].getDBID();
        cout << DataBaseFieldIndex << ' ' << endl;
        if (DataBaseFieldIndex == DBFID)
        {
            checkedID = i;
            break;
        }
    }

    if (checkedID == -1)
        throw new MyException("field is not existed");
    return fields[checkedID];
}

void Controller::saveFindCluster(int FID, int FCID)
{
    FindCluster &findCluster = sv.getFindCluster(FID, FCID);
    try{
        FindClusterLoader &Loader = DataBaseLoader.getFindClusterLoader();
        Field & field = fields[FID];
        if(!field.is_saved())
            throw MyException("Field " + to_string(FID) + " is not saved");
        findCluster.setDBFID(field.getDBID());
        Loader.saveFindCluster(findCluster);
        ClusterLoader &CLoader = DataBaseLoader.getClusterLoader();
        calculate_clusters_center(findCluster.getFindedClusters(), fields[FID]);
        CLoader.saveClusters(findCluster);
        createClusterFiles(findCluster);
        string message = "save find cluster is executed with parameters " + to_string(FID);
        logger.info(message);
    }
    catch(MyException &ex)
    {
        string message = ex.getMessage();
        logger.error(message);
    }
}

void Controller::loadFindCluster(int DBFID, int findClusterID)
{
    try{
        Field & field = getFieldByFID(DBFID);
        if (field.is_executed())
            throw MyException("Field is not loaded");
        sv.resizeFindClusters(field.getID() + 1);

        FindCluster & findCluster = sv.getFindCluster(DBFID, findClusterID);

        FindClusterLoader &Loader = DataBaseLoader.getFindClusterLoader();
        Loader.loadFindCluster(findCluster, findClusterID, DBFID);
        //FindCluster testfindCluster = sv.getFindCluster(0);
        //findCluster.printParameters();
        //testfindCluster.printParameters();

        ClusterLoader &CLoader = DataBaseLoader.getClusterLoader();
        vector <Cluster> &findedClusters = findCluster.getFindedClusters();
        int ClusterSize = findCluster.getSize();
        for (int i = 0; i < ClusterSize; i++)
            findedClusters[i].reserve(field.size());
        CLoader.loadClusters(findCluster);

        string message = "load find cluster is executed with parameters " + to_string(findClusterID) + " " +   
                                                                        to_string(DBFID);
        logger.info(message);
    }
    catch(MyException& ex)
    {
        string message = ex.getMessage();
        logger.error(message);
    }
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

    string message = "calculated center with parameters " + to_string(field.getID());
    logger.info(message);
}

void Controller::print_center(Field &field)
{
    cout.setf(ios::left | ios::showpos);
    //FindCluster findCluster = sv.getFindCluster(0);
    //calculate_clusters_center(findCluster.getFindedClusters(), fields[findCluster.getFieldID()]);
    cout << "Center is (" << setprecision(6) << field.center.getx() << " " << field.center.gety() << ")" << endl;
    string message = "print center is executed with parameters " + to_string(field.getID());
    logger.info(message);
}
