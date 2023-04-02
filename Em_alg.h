#ifndef EM_H
#define EM_H
using namespace std;
#include "field.h"
#include "cluster.h"

class Em_alg
{
    private:
    public:
        Em_alg(){}
        double P(const vector <double> &a);
        double cov_matrix_xy(const vector <double> &x,const vector <double> &y, const vector <double> &ux, const vector <double> &uy, const vector <double> &a, const double &p, const int &j);
        double det(const vector <vector <double>> &cov_mat);
        double probability_to_j(const vector <vector <double>> &cov_mat, const vector <double> &x, const vector <double> &y, const vector <double> &ux, const vector <double> &uy, const int &i, const int &j);
        vector <Cluster> turn_EM(int k, Field &field);
        void printEllipsesForGNU(vector <vector <vector <double>>> &covm, vector <double> &ux, vector <double> &uy, const int &k);
        double norma(const vector <double> & x, const vector <double> &y);
        ~Em_alg(){};
};

#endif