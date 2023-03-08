#ifndef EM_H
#define EM_H
using namespace std;
#include "field.h"
#include "cluster.h"
#include "storage.h"

class Em_alg
{
    private:
        Storage storage;
    public:
        Em_alg(){}
        double P(const vector <double> &a);
        double cov_matrix_xy(const vector <double> &x,const vector <double> &y, const vector <double> &ux, const vector <double> &uy, const vector <double> &a, const double &p, const int &j);
        double det(const vector <vector <double>> &cov_mat);
        double probability_to_j(const vector <vector <double>> &cov_mat, const vector <double> &x, const vector <double> &y, const vector <double> &ux, const vector <double> &uy, const int &i, const int &j);
        void turn_EM(int k, Field &field);
        double norma(const vector <double> & x, const vector <double> &y);
        Storage get_storage();
        ~Em_alg(){};
};

#endif