#include <iostream>
#include "VolSlice.h"
using namespace std;
using namespace Eigen;

VolSlice::VolSlice(string modelName_, double T, VectorXd params_)
    : modelName(modelName_), maturity(T), params(params_)
    {}