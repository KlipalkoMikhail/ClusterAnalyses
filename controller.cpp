#include "headers.h"
#include <iostream>
#include <fstream>
#include <cfloat>
#include <random>
#include <iomanip>
#include "controller.h"
#include <random>
#include <iterator>
#include <utility>
#include "factors.h"
#include "exec.h"
#include <list>
#include <cmath>
#include <stack>
#include <ctime>
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
    vector <Point> & points = field.getPointsReference();
    double x = 0;
    double y = 0;
    int size = 0;
    int ClusterSize = clusters.size();
    int N = field.getSize();

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
        //sv.resizeFindClusters(field.getID() + 1);
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

void Controller::print_launches()
{
    sv.printLaunches();
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

    // сохраняем поле в файл
    field.saveInFile();

    // сохраняем результаты в лог-файл контроллера
    string message = "print field is executed with parameters " + to_string(field.getID());
    cout << message;
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
        fields[parameters.field_index].setState(1);
    }


    fields[parameters.field_index].generate(parameters);
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
    Cloud cloud = field.getCloud(i);

    // создаем имя для файла
    sprintf(filename, "cloud_%d.dat", i);

    // открываем файл
    fout.open(filename);

    // иницилизируем точки облака, points - точки облака
    vector <Point> points = cloud.getPoints();

    // печатаем в файл точки
    for (int j = 0; j < (int)points.size(); j++)
                fout << points[j].getx() << "\t\t" << points[j].gety() << endl;
    
    // закрываем файл
    fout.close();

    // проверяем на состояние создания облака и печатаем его на экран в случае наличия с точностью до шести знаков
    if (cloud.is_executed() != 1)
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

    sv.saveResult(findCluster, field);

    string message = "save find cluster result is executed with parameters " + to_string(launchIndex) + " " +   
                                                                               to_string(field.getID());
    logger.info(message);
    message = "find clusted result saved with parameters " + to_string(launchIndex) + " " + name + " " + to_string(Knumber) + " " + to_string(Rnumber) + " " + to_string(size) + " " + to_string(field.getID());
    logger.debug(message);
    cout << name << "done as " << launchIndex << "th algorithm with parameters k = " << Knumber << ", r = " << Rnumber << ", size = " << size << endl;
}

void Controller::print_clouds(Field &field)
{
    vector <Cloud> &clouds = field.getCloudsReference();

    int k = field.getCloudsSize();
    cout << k << endl;

    ofstream *fout = new ofstream[k];

    for (int i = 0; i < k; i++)
    {
        char filename[120];
        sprintf(filename, "%d.dat", i + 1);
        fout[i].open(filename);
        vector <Point> points = clouds[k].getPoints();
        for (int j = 0; j < clouds[k].getSize(); j++)
                fout[i] << points[j].getx() << "\t\t" << points[j].gety() << endl;
    }
    string message = "print cloud is executed with parameters " + to_string(field.getID());
    logger.info(message);
}

void Controller::calculate_factor(int k, Field &field)
{
    vector <Point> &arr = field.getPointsReference();
    if (k == 0)
    {
        arr = field.getPointsReference();
        field.factors = exec.factors.calculate_factors(arr);
    }
    if (k == 1)
    {
        for (int i = 0; i < field.getCloudsSize(); i++)
            (field.getCloudReference(i)).factors = exec.factors.calculate_factors((field.getCloudReference(i)).getPoints());
    }
    if (k == 2)
    {
        int LaunchIndex;
        FindCluster &findCluster = sv.getFindCluster(field.getID(), LaunchIndex);
        vector <Cluster> & clusters = findCluster.getFindedClusters();
        int ClusterSize = clusters.size();
        int FieldSize = field.getSize();
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
        vector <Cloud> cloud(field.getCloudsSize());
        for (int j = 0 ; j < field.getCloudsSize(); j++)
        {
            Cloud & cld = field.getCloudReference(j);
            cloud[j].factors = cld.factors;
        }
        ofstream cloudo;
        cloudo.open("cloud_factors.dat");
        for (int i = 0; i < field.getCloudsSize(); i++)
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
    cout << "Size is " << field.getSize() << endl;
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
   vector <Point> & points = field.getPointsReference();

   for (int i = 0; i < field.getSize(); i++)
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
    cout.unsetf(ios::showpos);
    cout << "Loading find clusters DBFID=" << DBFID << " FCID=" << findClusterID << endl;
    try{
        Field & field = getFieldByFID(DBFID);
        int FID = field.getID();
        if (!field.is_executed())
            throw MyException("Field is not loaded");
        sv.resizeFindClusters(FID + 1); 

        FindCluster & findCluster = sv.getFindCluster(FID, findClusterID);

        FindClusterLoader &Loader = DataBaseLoader.getFindClusterLoader();
        Loader.loadFindCluster(findCluster, findClusterID, DBFID);
        //FindCluster testfindCluster = sv.getFindCluster(0);

        //findCluster.printParameters();
        //testfindCluster.printParameters();

        ClusterLoader &CLoader = DataBaseLoader.getClusterLoader();
        vector <Cluster> &findedClusters = findCluster.getFindedClusters();
        int ClusterSize = findCluster.getSize();
        findedClusters.resize(ClusterSize);
        for (int i = 0; i < ClusterSize; i++)
            findedClusters[i].reserve(field.getSize());
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
    int field_size = field.getSize();
    vector <Point> points = field.getPointsReference();
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

double dist_center(Cluster &x, Cluster &y)
{
    return distance(x.getCenter(), y.getCenter());
}

double dist_min(Cluster &x, Cluster &y, Field &field)
{
    vector <Point> &points = field.getPointsReference();
    double min = -1;
    for (int i = 0; i < field.getSize(); i++)
    {
        if (x.tr(i) == 0) continue;
        for (int j = 0; j < field.getSize(); j++)
        {
            if (y.tr(j) == 1)
            {
                double temp = distance(points[i], points[j]);
                //cout << temp << endl;
                if (min == - 1) min = temp;
                else if (min > temp) min = temp;
                else continue;
            } 
            else continue;
        }
    }
    return min;
}

double dist_max(Cluster &x, Cluster &y, Field &field)
{
    vector <Point> &points = field.getPointsReference();
    double max = 0;
    for (int i = 0; i < field.getSize(); i++)
    {
        if (x.tr(i) == 0) continue;
        for (int j = i + 1; j < field.getSize(); j++)
        {
            if (y.tr(j) == 1)
            {
                double temp = distance(points[i], points[j]);
                //cout << temp << endl;
                if (max < temp) max = temp;
            } 
            else continue;
        }
    }
    return max;
}

void print_cluster(Cluster &cluster)
{
    for (int k = 0 ; k < cluster.getFieldSize(); k++)
        cout << cluster.tr(k) << ' ';
    cout << endl;
}

void initAndFillClusters(vector <Cluster> &clusters, Field &field)
{
    int N = field.getSize();
    for (int i = 0; i < static_cast <int> (clusters.size()); i++)
    {
        Cluster & cluster = clusters[i];
        cluster.reserve(N);
        cluster.add_p(i);
        cluster.setCenter((field.getPointsReference())[i]);
    }
}

void initMatrix(vector <vector <double>> &A, vector <Cluster> &clusters)
{
    int N = static_cast <int> (clusters.size());
    A.resize(N);
    for(int i = 0; i < N; i++)
        A[i].resize(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = dist_center(clusters[i], clusters[j]);
            // A[i][j] = d(clusters[i], clusters[j]);
            // A[i][j] = d(clusters[i], clusters[j]);

}

Cluster uniteClusters(Cluster x, Cluster &y)
{
    int sizeRemnant = 0;
    Point newCenter, oldCenter_x = x.getCenter(), oldCenter_y = y.getCenter();
    newCenter.setx((oldCenter_x.getx() + oldCenter_y.getx())/2);
    newCenter.sety((oldCenter_x.gety() + oldCenter_y.gety())/2);

    for (int i = 0; i < x.getFieldSize(); i++)
    {
        if (y.tr(i))
        {
            if (x.tr(i) == 0)
            {
                x.add_p(i);
                sizeRemnant++;
            }
        }
    }
    x.setCenter(newCenter);
    x.setSize(x.getSize() + sizeRemnant);
    //cout << "======" << endl;
    return x;
}

pair <int, int> findMinimalClusters(vector <vector <double>> &A)
{
    pair <int, int> minimals = {0, 0};
    int N = static_cast <int> (A.size());
    //cout << fixed << setprecision(3);
    if (N == 1) return minimals;
    else
    {
        double min = A[0][1];
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                //cout << A[i][j] << ' ';
                if (min >= A[i][j])
                {
                    min = A[i][j];
                    minimals.first = i;
                    minimals.second = j;
                }
            }
            //cout << endl;
        }
    }
    //cout << endl;
    return minimals;
}

void eraseColumn(vector <vector <double>> &A, int j)
{
    for (size_t i = 0; i < A.size(); i++)
        A[i].erase(A[i].begin() + j);
}

void printInGNU(vector <pair <Cluster, Cluster>> &Stack)
{   
    ofstream gnufile("edges.dat", ios::binary);
    pair <Cluster, Cluster> topItem;
    size_t size = Stack.size();
    for (size_t i = 0; i < size; i++)
    {
        topItem = Stack[size - i - 1];
        pair <Point, Point> pair_centers = {topItem.first.getCenter(), topItem.second.getCenter()};
        gnufile << pair_centers.first.getx() << ' ' << pair_centers.first.gety() << endl;
        gnufile << pair_centers.second.getx() << ' ' << pair_centers.second.gety() << endl << endl;
    }
    gnufile.close();
}

void recalculateMatrix(vector <vector <double>> &A, vector <Cluster> &clusters, Field &field)
{
    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = i + 1; j < A[i].size(); j++)
        {
            //cout << i << ' ' << j << endl;
            A[i][j] = dist_center(clusters[i], clusters[j]);
            //A[i][j] = dist_min(clusters[i], clusters[j], field);
            //A[i][j] = dist_max(clusters[i], clusters[j], field);
        }
            
}

void printGNUclusters(vector <Cluster> &clusters, Field &field)
{
    ofstream gnufile;
    string filename;
    size_t clustersSize = clusters.size();
    vector <Point> &points = field.getPointsReference();
    for (size_t i = 0; i < clustersSize; i++)
    {
        filename = "ClusterPoints_" + to_string(i) + ".dat";
        gnufile.open(filename);
        for (size_t j = 0; j < static_cast <size_t> (field.getSize()); j++)
        {
            if (clusters[i].tr(j) == 1)
                gnufile << points[j].getx() << ' ' << points[j].gety() << endl;
        }
        gnufile.close();
    }
} 


void findMode(vector <pair <Cluster, Cluster>> hierarchicalStack, Field &field)
{
    size_t size = hierarchicalStack.size();
    vector <pair <int, double>> amount(size + 1);
    vector <double> distances(size);
    if (size == 0) throw MyException("size is zero");

    for (size_t i = 0; i < size; i++)
    {
        pair<Cluster, Cluster> clusterPair = hierarchicalStack[size - i - 1];
        distances[i] = dist_center(clusterPair.first, clusterPair.second);
        //distances[i] = dist_min(clusterPair.first, clusterPair.second, field);
        //distances[i] = dist_max(clusterPair.first, clusterPair.second, field);
    }

    double min = distances[0];
    double max = distances[0];
    for (size_t i = 0; i < size; i++)
    {
        if (min >= distances[i])
            min = distances[i];
        if (max <= distances[i])
            max = distances[i];
    }

    double length = max - min;
    double h = (max - min)/size;

    for (size_t i = 0; i <= size; i++)
    {
        amount[i].first = 0;
        amount[i].second = min + i*h;
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (amount[i].second <= distances[j] && distances[j] <= amount[i + 1].second)
                amount[i].first += 1;
        }
    }

    pair <size_t, size_t> max_space = {0, 0};
    size_t max_space_temp = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (amount[i].first == 0)
        {
            max_space_temp++;
            if (amount[i + 1].first != 0 && max_space_temp >= max_space.first)
            {
                max_space.first = max_space_temp;
                max_space.second = i;
                max_space_temp = 0; 
            }
        }
    }


    //cout << max_space.first << endl;
    //cout << size - max_space.second << endl;
    //cout << amount[max_space.second].second << endl;
    //cout << amount[max_space.second - max_space.first].second << endl;

    vector <Cluster> clusters;

    for (size_t i = 0; i < size; i++)
    {
        pair<Cluster, Cluster> clusterPair = hierarchicalStack[size - i - 1];
        if (distances[i] > amount[max_space.second].second)
        {
            clusters.push_back(clusterPair.first);
            clusters.push_back(clusterPair.second);
        }
    }
    printGNUclusters(clusters, field);
}

void Controller::hierarchical(int FID)
{
    Field &field = fields[FID];
    int N = field.getSize();
    vector <vector <double>> DistanceMatrix;
    vector <Cluster> clusters(N);
    pair <int, int> minimalDistanceClustersIndex;
    pair <Cluster, Cluster> minimalDistanceClusters;
    vector <pair <Cluster, Cluster>> hierarchicalStack;

    initAndFillClusters(clusters, field);
    initMatrix(DistanceMatrix, clusters);

    while (N != 1)
    {
        minimalDistanceClustersIndex = findMinimalClusters(DistanceMatrix);
        minimalDistanceClusters.first = clusters[minimalDistanceClustersIndex.first];
        minimalDistanceClusters.second = clusters[minimalDistanceClustersIndex.second];
        //cout << minimalDistanceClustersIndex.first << ' ' << minimalDistanceClustersIndex.second << endl;
        hierarchicalStack.push_back(minimalDistanceClusters);

        Cluster clust = uniteClusters(minimalDistanceClusters.first, minimalDistanceClusters.second);
        clusters[minimalDistanceClustersIndex.first] = clust;

        DistanceMatrix.erase(DistanceMatrix.begin() + minimalDistanceClustersIndex.second);
        eraseColumn(DistanceMatrix, minimalDistanceClustersIndex.second);
        clusters.erase(clusters.begin() + minimalDistanceClustersIndex.second);
        N--;
        recalculateMatrix(DistanceMatrix, clusters, field);
        //cout << "N " << N << " done" << endl;
    }

    findMode(hierarchicalStack, field);
    printInGNU(hierarchicalStack);


    string message = "turn hier is executed with parameters " + to_string(FID);
    cout << message << endl;
    logger.info(message);
}

double regression_function(double x)
{
    return cos(2 * x) + sin(x) - x*x*x;
}

void Controller::regression(int FID)
{
    size_t size = 250;
    double first = 0;
    double last = 5;
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(first, last);
    vector <Point> initial_data;
    for (size_t i = 0; i < size; i++)
    {
        double x = distribution(generator);
        initial_data.push_back(Point(x, regression_function(x)));
    }

}


