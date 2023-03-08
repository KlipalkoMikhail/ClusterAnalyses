#include "cloud.h"
#include "point.h"
#include "headers.h"
#include "factors.h"
using namespace std;
#include <cmath>

vector <double> Factor::calculate_factors(vector <Point> arr)
{
	vector<double> x;
	vector<double> y;
	vector<double> factors;
	vector<double> center;
	vector<double> eigenvector_1;
	vector<double> eigenvector_2;
	double cx = 0.0, cy = 0.0;
	double a11 = 0.0, a12 = 0.0, a22 = 0.0;
	double l1, l2, norma1, norma2;
	int i, n;
	n = arr.size();

	x.resize(n);
	y.resize(n);

	for (i = 0; i < n; i++) {
		cx += arr[i].getx();
		cy += arr[i].gety();
	}
	cx /= n;
	cy /= n;

	for (i = 0; i < n; i++) {
		x[i] = arr[i].getx() - cx;
		y[i] = arr[i].gety() - cy;
	}

	for (i = 0; i < n; i++) {
		a11 += x[i] * x[i];
		a12 += x[i] * y[i];
		a22 += y[i] * y[i];
	}

	l1 = (a11 + a22 + sqrt((a11 - a22) * (a11 - a22) + 4 * a12 * a12)) / 2;
	l2 = (a11 + a22 - sqrt((a11 - a22) * (a11 - a22) + 4 * a12 * a12)) / 2;

	center.resize(2);
	eigenvector_1.resize(2);
	eigenvector_2.resize(2);
	center[0] = cx;
	center[1] = cy;
	eigenvector_1[0] = 1;
	eigenvector_1[1] = -(a11 - l1) / a12;
	eigenvector_2[0] = 1;
	eigenvector_2[1] = -(a11 - l2) / a12;
	norma1 = sqrt(eigenvector_1[0] * eigenvector_1[0] + eigenvector_1[1] * eigenvector_1[1]);
	norma2 = sqrt(eigenvector_2[0] * eigenvector_2[0] + eigenvector_2[1] * eigenvector_2[1]);
	eigenvector_1[0] /= norma1;
	eigenvector_1[1] /= norma1;
	eigenvector_2[0] /= norma2;
	eigenvector_2[1] /= norma2;

	eigenvector_1[0] *= l1 / n;
	eigenvector_1[1] *= l1 / n;
	eigenvector_2[0] *= l2 / n;
	eigenvector_2[1] *= l2 / n;

	factors.resize(8);
	factors[0] = center[0];
	factors[1] = center[1];
	factors[2] = eigenvector_1[0];
	factors[3] = eigenvector_1[1];
	factors[4] = eigenvector_2[0];
	factors[5] = eigenvector_2[1];
	factors[6] = l1;
	factors[7] = l2;

	return factors;

    //logfile_controller << "CALFACT cluster " << k << " success" << endl;
}