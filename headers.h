#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include "point.h"
#include "cloud.h"
#include "field.h"
#include "cluster.h"
#include <random>
#include <string>
#include "MyException.h"
using namespace std;
double scalx(std::vector <Point> &x, std::vector <short int> &bl, int N);
double scaly(std::vector <Point> &x, std::vector <short int> &bl, int N);
void printvec(vector <int> a);
bool iscore(vector <vector<int>> &B, int k, int m);
double distance(const Point &x, const Point &y);




